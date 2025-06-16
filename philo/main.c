/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/16 18:48:58 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_philos	*philos;
	int			total_philos;

	if (arg_check(ac, av) == -1)
		return (0);
	else
	{
		total_philos = ft_atoi(av[1]);
		philos = malloc(sizeof(t_philos) * total_philos);
		if (!philos)
			return (0);
		init_philos(philos, ac, av);
		start(philos, total_philos);
	}
	free_and_destroy(philos);
	return (0);
}

int	arg_check(int ac, char **av)
{
	int	total_philos;
	int	tmp;
	int	i;

	if (ac < 5)
		return (printf("Invalid: Missing arguments\n"), -1);
	else if (ac > 6)
		return (printf("Invalid: Too many arguments\n"), -1);
	if (parsing(av) == -1)
		return (-1);
	total_philos = ft_atoi(av[1]);
	if (total_philos > 200)
		return (printf("Invalid: Too many philos\n"), -1);
	i = 2;
	while (av[i] && i < 5)
	{
		tmp = ft_atoi(av[i]);
		if (tmp < 60)
			return (printf("Invalid: time values must be > 60 ms\n"), -1);
		i++;
	}
	return (0);
}

int	parsing(char **av)
{
	int	i;
	int	j;
	
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("Invalid: Non numeric arguments\n"), -1);
			if (*av[i] == '0')
			{
				if (i == 5)
					break ;
				else
					return (printf("Invalid: Negative arguments\n"), -1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


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
