/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:16:53 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/05 17:15:10 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//transforms char into long

long	ft_atol(const char *nptr)
{
	int		i;
	int		neg;
	long	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * neg);
}

//transforms char into int

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * neg);
}

//checks if a char is digit

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

//frees memory and destroys mutexes

void	free_and_destroy(char *err, t_meal *meal, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (err)
	{
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&meal->sync);
	pthread_mutex_destroy(&meal->print);
	pthread_mutex_destroy(&meal->death);
	pthread_mutex_destroy(&meal->meal);
	pthread_mutex_destroy(&meal->eating_lock);
	while (i < meal->philos[0].total_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return ;
}
