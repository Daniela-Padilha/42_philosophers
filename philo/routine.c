/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 01:19:19 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//the routine the philos will follow

void	*routine(void *arg)
{
	t_meal	*meal;

	meal = (t_meal *)arg;
	sync_threads(meal->philos, 1);
	if (meal->total_philos > 1 && meal->philos->id % 2 == 0)
		my_usleep(100, meal->philos);
	while (!dead_check(meal->philos, meal))
	{
		eat(meal->philos);
		sleeping(meal->philos);
		think(meal->philos);
	}
	return (arg);
}

//Check if a philo died

bool	dead_check(t_philos *philos, t_meal *meal)
{
	pthread_mutex_lock(&meal->death_lock);
	if (*philos->dead_flag == true)
	{
		pthread_mutex_unlock(&meal->death_lock);
		return (true);
	}
	pthread_mutex_unlock(&meal->death_lock);
	return (false);
}

//mutexes to lock the forks when grabed by a philo

void	grab_forks(t_philos *philos, t_meal *meal)
{
	if (meal->total_philos == 1)
	{
		pthread_mutex_lock(philos->right_fork);
		speak("has taken a fork", philos, philos->id);
		pthread_mutex_unlock(philos->right_fork);
		my_usleep(meal->time_to_die, philos);
		return ;
	}
	else if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork);
		speak("has taken a fork", philos, philos->id);
		pthread_mutex_lock(philos->right_fork);
		speak("has taken a fork", philos, philos->id);
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		speak("has taken a fork", philos, philos->id);
		pthread_mutex_lock(philos->left_fork);
		speak("has taken a fork", philos, philos->id);
	}
}

//mutexes to unlock the forks when released by a philo

void	release_forks(t_philos *philos, t_meal *meal)
{
	if (meal->total_philos == 1)
		return ;
	else if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
	}
}

//Create threads

void	start_meal(t_meal *meal, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < meal->total_philos)
	{
		if (pthread_create(&meal->philos[i].thread, NULL, routine,
				(void *)&meal->philos[i]) != 0)
			destroy("Error: thread creation failed\n", meal, forks);
		i++;
	}
	if (meal->total_philos > 1)
	{
		if (pthread_create(&meal->waiter_thread, NULL, waiter, meal->philos) != 0)
			destroy("Error: thread creation failed\n", meal, forks);
	}
	return ;
}
