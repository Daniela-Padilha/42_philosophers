/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/12 17:59:05 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	think(t_philos *philos)
{
	while (philos->alive)
		usleep(100);
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
