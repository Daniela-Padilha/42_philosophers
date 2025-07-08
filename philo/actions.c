/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 23:12:02 by ddo-carm         ###   ########.fr       */
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
	grab_forks(philos);
	pthread_mutex_lock(philos->eating_lock);
	philos->eating = true;
	pthread_mutex_unlock(philos->eating_lock);
	speak("is eating", philos, philos->id);
	pthread_mutex_lock(philos->meal);
	philos->last_meal = get_time();
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->meal);
	my_usleep(philos->time_to_eat);
	pthread_mutex_lock(philos->eating_lock);
	philos->eating = false;
	pthread_mutex_unlock(philos->eating_lock);
	release_forks(philos);
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	speak("is sleeping", philos, philos->id);
	my_usleep(philos->time_to_sleep);
}
