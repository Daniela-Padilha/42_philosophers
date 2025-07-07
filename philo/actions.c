/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/07 17:43:28 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//makes philos think while waiting

void	think(t_philos *philos)
{
	speak("is thinking", philos, philos->id);
}

//makes philos grab forks, eat and release forks

void	eat(t_philos *philos)
{
	pthread_mutex_lock(philos->right_fork);
	speak("has taken a fork", philos, philos->id);
	if (philos->total_meals == 1)
	{
		my_usleep(philos->time_to_die);
		pthread_mutex_unlock(philos->right_fork);
		return ;
	}
	pthread_mutex_lock(philos->left_fork);
	speak("has taken a fork", philos, philos->id);
	philos->eating = 1;
	speak("is eating", philos, philos->id);
	pthread_mutex_lock(philos->meal);
	philos->last_meal = get_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal);
	my_usleep(philos->time_to_eat);
	philos->eating = 0;
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	speak("is sleeping", philos, philos->id);
	my_usleep(philos->time_to_sleep);
}
