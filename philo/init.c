/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/16 18:30:31 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	init_philos(t_philos *philos, int ac, char **av)
{
	philos->philo_nbr = ft_atoi(av[1]);
	philos->time_to_die = ft_atol(av[2]);
	philos->time_to_eat = ft_atol(av[3]);
	philos->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		philos->eat_times = ft_atol(av[5]);
	else
		philos->eat_times = 0;
	philos->eaten = false;
	philos->alive = true;
}

