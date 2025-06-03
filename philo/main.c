/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/03 14:56:20 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_philos	*philos;
	int			total;
	int			i;

	if (arg_check(ac, av) == -1)
		return (0);
	else
	{
		total = ft_atoi(av[1]);
		philos = malloc(sizeof(t_philos) * total);
		if (!philos)
			return (0);
		init_philos(philos, ac, av);
		start(philos, av[1]);
	}
	i = 0;
	while (i < total)
	{
		pthread_create(&philos[i].thread, NULL, routine, (void *)&philos[i]);
		i++;
	}
	i = 0;
	while (i < total)
	{
		pthread_join(&philos[i].thread, NULL);
		i++;
	}
	free_struct((void *)philos);
	return (0);
}

int	arg_check(int ac, char **av)
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
				return (printf("Non numeric arguments\n"), -1);
			j++;
		}
		i++;
	}
	if (ac < 5)
		return (printf("Missing arguments\n"), -1);
	else if (ac > 6)
		return (printf("Too many arguments\n"), -1);
	return (0);
}

void	start(t_philos *philos, char *philo)
{
	int				nbr;
	int				i;
	struct	timeval tv;

	nbr = ft_atoi(philo);
	i = 1;
	while (i <= nbr)
	{
		gettimeofday(&tv, NULL);
		printf("%li philosopher number: %i\n", tv.tv_usec, i);
		i++;
	}
	printf("and %i forks\n", nbr);
	free_struct((void *)philos);
}
