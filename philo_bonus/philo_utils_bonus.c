/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:16:53 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 16:32:36 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

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

//frees memory, closes pid and semaphores, and prints error if needed

void	free_and_close(char *err, pid_t pid, t_meal *meal, int free_meal)
{
	if (err)
	{
		write(2, err, ft_strlen(err));
		write(2, "\n", 1);
	}
	if (free_meal)
	{
		if (meal)
		{
			if (meal->forks_sem)
				sem_close(meal->forks_sem);
			if (meal->death_sem)
				sem_close(meal->death_sem);
			if (meal->print_sem)
				sem_close(meal->print_sem);
			if (meal->waiter_sem)
				sem_close(meal->waiter_sem);
			free(meal);
		}
	}
	if (pid != -1)
		close(pid);
	return ;
}

//Kills philo process when the program ends

void	kill_processes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->total_philos)
	{
		sem_wait(meal->death_sem);
		i++;
	}
	i = 0;
	while (i < meal->total_philos)
	{
		kill(meal->philos->pid, SIGKILL);
		i++;
	}
}
