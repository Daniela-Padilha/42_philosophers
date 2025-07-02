/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 16:40:05 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

//makes philos think while waiting

void	think(t_philos *philos)
{
	speak("is thinking", philos, philos->id);
}

//makes philos grab forks, eat and release forks

void	eat(t_meal *meal)
{
	grab_forks(meal);
	meal->philos->eating = true;
	speak("is eating", meal->philos, meal->philos->id);
	meal->philos->last_meal = get_time();
	meal->philos->meals_eaten++;
	my_usleep(meal->philos->time_to_eat);
	meal->philos->eating = false;
	release_forks(meal);
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	speak("is sleeping", philos, philos->id);
	my_usleep(philos->time_to_sleep);
}
