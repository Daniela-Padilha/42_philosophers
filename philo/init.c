/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:25:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//init philos struct

void	init_philos(t_philos *philos, int ac, char **av)
{
	philos->id = 0;
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
	pthread_mutex_init(&philos->left_fork, NULL);
	pthread_mutex_init(&philos->right_fork, NULL);
	pthread_mutex_init(&philos->print, NULL);
}

//creates the threads

void	start(t_philos *philos, int total)
{
	int				i;
	struct	timeval tv;

	i = 0;
	while (i < total)
	{
		gettimeofday(&tv, NULL);
		pthread_create(&philos[i].thread, NULL, routine, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < total)
	{
		gettimeofday(&tv, NULL);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}