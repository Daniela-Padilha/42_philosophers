/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/16 18:50:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	think(t_philos *philos)
{
	pthread_mutex_lock(philos->print);
	while (philos->philo_nbr)
	printf("%s is thinking\n");
	pthread_mutex_unlock(philos->print);
}

void	eat(t_philos *philos)
{
	usleep(philos->time_to_eat);
	printf("i am eating");
}

void	sleeping(t_philos *philos)
{
	usleep(philos->time_to_sleep);
}
