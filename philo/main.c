/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 00:57:54 by ddo-carm         ###   ########.fr       */
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
	start_meal(&meal, forks);
	end_meal(&meal, forks);
	return (0);
}

//Destroys mutexes and prints message if needed

void	destroy(char *err, t_meal *meal, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (err)
	{
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&meal->print);
	pthread_mutex_destroy(&meal->death);
	pthread_mutex_destroy(&meal->meal);
	pthread_mutex_destroy(&meal->eating_lock);
	while (i < meal->total_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return ;
}

//Join threads

void	end_meal(t_meal *meal, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < meal->total_philos)
	{
		if (pthread_join(&meal->philos[i].thread, NULL) != 0)
			free_and_destroy("Error: thread join failed\n", meal, forks);
		i++;
	}
	if (meal->total_philos > 1)
	{
		if (pthread_join(&meal->waiter_thread, NULL) != 0)
		free_and_destroy("Error: thread join failed\n", meal, forks);
	}
	destroy(NULL, meal, forks);
	return ;
}
