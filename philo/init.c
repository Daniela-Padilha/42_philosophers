/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 01:05:42 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//Init meal

void	init_meal(t_meal *meal, t_philos *philos, char **av)
{
	meal->total_philos = ft_atoi(av[1]);
	meal->time_to_die = ft_atol(av[2]) * 1000;
	meal->time_to_eat = ft_atol(av[3]) * 1000;
	meal->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		meal->total_meals = ft_atol(av[5]);
	else
		meal->total_meals = -1;
	meal->dinner_start = get_time();
	meal->dead_flag = false;
	meal->philos = philos;
	pthread_mutex_init(&meal->death_lock, NULL);
	pthread_mutex_init(&meal->eating_lock, NULL);
	pthread_mutex_init(&meal->print_lock, NULL);
	pthread_mutex_init(&meal->meal_lock, NULL);
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
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		philos[i].dead_flag = &meal->dead_flag;
		philos[i].eating = false;
		philos[i].right_fork = &forks[i];
		if (i == 0)
			philos[i].left_fork = &forks[ft_atoi(av[1]) - 1];
		else
			philos[i].left_fork = &forks[i - 1];
		i++;
	}
}
