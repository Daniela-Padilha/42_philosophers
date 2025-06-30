/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/30 18:48:29 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//the routine the philos will follow

void	*routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	sync_threads(philos, 1);
	if (philos->id % 2 == 0)
		my_usleep(100);
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
	pthread_mutex_lock(philos->right_fork);
	speak("has taken a fork", philos, philos->id);
	if (philos->total_philos == 1)
	{
		my_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->right_fork);
		return ;
	}
	pthread_mutex_lock(philos->left_fork);
	speak("has taken a fork", philos, philos->id);
}

//mutexes to unlock the forks when released by a philo

void	release_forks(t_philos *philos)
{
	if (philos->total_philos == 1)
		return ;
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

//Create threads

void	start_meal(t_meal *meal, pthread_mutex_t *forks)
{
	pthread_t	waiter_thread;
	int			i;

	if (pthread_create(&waiter_thread, NULL, waiter, meal->philos) != 0)
		free_and_destroy("Error: thread creation failed\n", meal, forks);
	i = 0;
	while (i < meal->philos[0].total_philos)
	{
		if (pthread_create(&meal->philos[i].thread, NULL, routine,
				(void *)&meal->philos[i]) != 0)
			free_and_destroy("Error: thread creation failed\n", meal, forks);
		i++;
	}
	sync_threads(meal->philos, 0);
	i = 0;
	if (pthread_join(waiter_thread, NULL) != 0)
		free_and_destroy("Error: thread join failed\n", meal, forks);
	while (i < meal->philos[0].total_philos)
	{
		if (pthread_join(meal->philos[i].thread, NULL) != 0)
			free_and_destroy("Error: thread join failed\n", meal, forks);
		i++;
	}
	return ;
}
