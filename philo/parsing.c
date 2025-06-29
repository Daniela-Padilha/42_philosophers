/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:23:39 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/29 15:44:18 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//checks if args are in the expected format and amount

int	arg_check(int ac, char **av)
{
	int	total_philos;
	int	tmp;
	int	i;

	if (ac < 5)
		return (printf("Invalid: Missing arguments\n"), -1);
	else if (ac > 6)
		return (printf("Invalid: Too many arguments\n"), -1);
	if (arg_check_util(av) == -1)
		return (-1);
	total_philos = ft_atoi(av[1]);
	if (total_philos > PHILO_MAX)
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

//checks if args are numeric and positive

int	arg_check_util(char **av)
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
