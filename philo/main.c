/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/12 17:53:01 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_philos	*philos;
	int			total;

	if (arg_check(ac, av) == -1)
		return (0);
	else
	{
		total = ft_atoi(av[1]);
		philos = malloc(sizeof(t_philos) * total);
		if (!philos)
			return (0);
		init_philos(philos, ac, av);
		start(philos, av[1], total);
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

void	start(t_philos *philos, char *philo, int total)
{
	int				i;
	struct	timeval tv;

	total = ft_atoi(philo);
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
