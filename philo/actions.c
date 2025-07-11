/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/11 12:33:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//makes philos think while waiting

void	think(t_philos *philos)
{
	time_t	time_to_think;

	if (!dead_check(philos))
	{
		speak("is thinking", philos, philos->id);
		if (philos->total_philos % 2 == 0)
			return ;
		time_to_think = (philos->time_to_eat * 2) - philos->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		my_usleep(time_to_think * 0.5, philos);
	}
}

//makes philos grab forks, eat and release forks

void	eat(t_philos *philos)
{
	if (!dead_check(philos))
	{
		if (philos->total_philos == 1)
		{
			grab_forks(philos);
			return ;
		}
		pthread_mutex_lock(philos->eating_lock);
		philos->eating = true;
		pthread_mutex_unlock(philos->eating_lock);
		speak("is eating", philos, philos->id);
		pthread_mutex_lock(philos->meal);
		philos->last_meal = get_time();
		philos->meals_eaten++;
		pthread_mutex_unlock(philos->meal);
		my_usleep(philos->time_to_eat, philos);
		pthread_mutex_lock(philos->eating_lock);
		philos->eating = false;
		pthread_mutex_unlock(philos->eating_lock);
		release_forks(philos);
		my_usleep(100, philos);
	}
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	if (!dead_check(philos))
	{
		speak("is sleeping", philos, philos->id);
		my_usleep(philos->time_to_sleep, philos);
	}
}

//1 philo case

void	lonely_philo(t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	philos->has_right = true;
	speak("has taken a fork", philos, philos->id);
	my_usleep(philos->time_to_die, philos);
	pthread_mutex_unlock(philos->right_fork);
	philos->has_right = false;
	return ;
}
