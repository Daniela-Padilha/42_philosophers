/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/03 13:07:43 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	init_philos(t_philos *philos, int ac, char **av)
{
	philos->philo_nbr = 0;
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->eat_times = ft_atoi(av[5]);
	else
		philos->eat_times = 0;
	philos->eaten = false;
	philos->next = NULL;
}
