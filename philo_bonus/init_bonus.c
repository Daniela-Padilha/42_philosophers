/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:57:34 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 18:21:50 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

//Init all

t_meal	*init(char **av)
{
	t_meal	*meal;
	
	meal = (t_meal *)malloc(sizeof(t_meal));
	if (!meal)
		return (NULL);
	if (init_meal(meal, av) == -1)
		return (free(meal), NULL);
	meal->philos = (t_philos *)malloc(sizeof(t_philos) * meal->total_philos);
	if (!meal->philos)
		return (free(meal), NULL);
	init_philos(meal->philos, meal, av);
	return (meal);
}

//Init meal

int	init_meal(t_meal *meal, char **av)
{
	unlink_all();
	meal->dead_flag = false;
	meal->total_philos = ft_atoi(av[1]);
	meal->forks_sem = sem_open("forks_sem", O_CREAT, 0644, meal->total_philos);
	if (meal->forks_sem == SEM_FAILED)
		return (-1);
	meal->death_sem = sem_open("death_sem", O_CREAT, 0644, 1);
	if (meal->death_sem == SEM_FAILED)
		return (-1);
	meal->waiter_sem = sem_open("waiter_sem", O_CREAT, 0644, 1);
	if (meal->waiter_sem == SEM_FAILED)
		return (-1);
	meal->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (meal->print_sem == SEM_FAILED)
		return (-1);
	return (0);
}

//init philos struct

void	init_philos(t_philos *philos, t_meal *meal, char **av)
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
		philos[i].eating = false;
		philos[i].meal = meal;
		i++;
	}
}

//Init user input

void	init_input(t_philos *philos, char **av)
{
	philos->time_to_die = ft_atol(av[2]);
	philos->time_to_eat = ft_atol(av[3]);
	philos->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		philos->total_meals = ft_atol(av[5]);
	else
		philos->total_meals = -1;
}

//Unlink all sem

void	unlink_all(void)
{
	sem_unlink("forks_sem");
	sem_unlink("death_sem");
	sem_unlink("waiter_sem");
}
