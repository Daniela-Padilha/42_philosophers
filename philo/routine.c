/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/11 12:33:15 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//the routine the philos will follow

void	*routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(philos->start_lock);
		if (*philos->start_bool)
		{
			pthread_mutex_unlock(philos->start_lock);
			break ;
		}
		pthread_mutex_unlock(philos->start_lock);
		my_usleep(100, philos);
	}
	if (philos->id % 2 == 0)
		my_usleep(philos->time_to_eat / 2, philos);
	if (philos->total_philos == 1)
		grab_forks(philos);
	while (!dead_check(philos))
	{
		eat(philos);
		sleeping(philos);
		think(philos);
	}
	return (arg);
}

//Check if a philo died

bool	dead_check(t_philos *philos)
{
	pthread_mutex_lock(philos->death);
	if (*philos->dead_flag == true)
	{
		pthread_mutex_unlock(philos->death);
		return (true);
	}
	pthread_mutex_unlock(philos->death);
	return (false);
}

//mutexes to lock the forks when grabed by a philo

void	grab_forks(t_philos *philos)
{
	if (philos->total_philos == 1)
	{
		lonely_philo(philos);
		return ;
	}
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		philos->has_right = true;
		speak("has taken a fork", philos, philos->id);
		pthread_mutex_lock(philos->left_fork);
		philos->has_left = true;
		speak("has taken a fork", philos, philos->id);
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		philos->has_left = true;
		speak("has taken a fork", philos, philos->id);
		pthread_mutex_lock(philos->right_fork);
		philos->has_right = true;
		speak("has taken a fork", philos, philos->id);
	}
}

//mutexes to unlock the forks when released by a philo

void	release_forks(t_philos *philos)
{
	if (philos->has_left)
	{
		pthread_mutex_unlock(philos->left_fork);
		philos->has_left = false;
	}
	if (philos->has_right)
	{
		pthread_mutex_unlock(philos->right_fork);
		philos->has_right = false;
	}
}

//Create threads

void	start_meal(t_meal *meal, pthread_mutex_t *forks)
{
	pthread_t	waiter_thread;
	int			i;

	if (pthread_create(&waiter_thread, NULL, waiter, meal->philos) != 0)
		free_and_destroy("Error: thread creation failed\n", meal, forks);
	i = -1;
	while (++i < meal->philos[0].total_philos)
	{
		if (pthread_create(&meal->philos[i].thread, NULL, routine,
				(void *)&meal->philos[i]) != 0)
			free_and_destroy("Error: thread creation failed\n", meal, forks);
	}
	pthread_mutex_lock(&meal->start_lock);
	meal->start_bool = true;
	pthread_mutex_unlock(&meal->start_lock);
	i = -1;
	while (++i < meal->philos[0].total_philos)
	{
		if (pthread_join(meal->philos[i].thread, NULL) != 0)
			free_and_destroy("Error: thread join failed\n", meal, forks);
	}
	if (pthread_join(waiter_thread, NULL) != 0)
		free_and_destroy("Error: thread join failed\n", meal, forks);
	return ;
}
