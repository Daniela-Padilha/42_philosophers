/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/29 17:13:09 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_meal			meal;
	t_philos		philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (arg_check(ac, av) == -1)
		return (0);
	init_meal(&meal, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &meal, forks, av);
	start_meal(philos, ft_atoi(av[1]));
	free_and_destroy(NULL, &meal, forks);
	return (0);
}
