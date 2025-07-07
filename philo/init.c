/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/07 17:43:38 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//Init meal

void	init_meal(t_meal *meal, t_philos *philos)
{
	meal->dead_flag = 0;
	meal->philos = philos;
	pthread_mutex_init(&meal->death, NULL);
	pthread_mutex_init(&meal->print, NULL);
	pthread_mutex_init(&meal->meal, NULL);
}

//Init fork mutexes

void	init_forks(pthread_mutex_t *forks, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

//init philos struct

void	init_philos(t_philos *philos, t_meal *meal, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		init_input(&philos[i], av);
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		philos[i].dinner_start = get_time();
		philos[i].dead_flag = &meal->dead_flag;
		philos[i].eating = 0;
		philos[i].print = &meal->print;
		philos[i].death = &meal->death;
		philos[i].meal = &meal->meal;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].total_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

//Init user input

void	init_input(t_philos *philos, char **av)
{
	philos->total_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->total_meals = ft_atoi(av[5]);
	else
		philos->total_meals = -1;
}
