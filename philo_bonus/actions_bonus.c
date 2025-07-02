/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/01 18:51:35 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

//makes philos think while waiting

void	think(t_philos *philos)
{
	speak("is thinking", philos, philos->id);
}

//makes philos grab forks, eat and release forks

void	eat(t_philos *philos)
{
	grab_forks(philos);
	philos->eating = true;
	speak("is eating", philos, philos->id);
	philos->last_meal = get_time();
	philos->meals_eaten++;
	my_usleep(philos->time_to_eat);
	philos->eating = false;
	release_forks(philos);
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	speak("is sleeping", philos, philos->id);
	my_usleep(philos->time_to_sleep);
}
