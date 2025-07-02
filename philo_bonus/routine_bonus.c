/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 18:28:30 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

//the routine the philos will follow

void	routine(t_philos *philos)
{
	pthread_t	waiter_thread;

	if (pthread_create(&waiter_thread, NULL, waiter, philos) != 0)
		write(2, "Error: thread creation failed\n", 30);
	if (philos->id % 2 == 0)
		my_usleep(100);
	while (1)
	{
		eat(philos);
		sleeping(philos);
		think(philos);
	}
	exit(0);
}

//mutexes to lock the forks when grabed by a philo

void	grab_forks(t_meal *meal)
{
	sem_wait(meal->forks_sem);
	speak("has taken a fork", meal->philos, meal->philos->id);
	if (meal->total_philos == 1)
	{
		my_usleep(meal->philos->time_to_die);
		sem_post(meal->forks_sem);
		return ;
	}
	sem_wait(meal->forks_sem);
	speak("has taken a fork", meal->philos, meal->philos->id);
}

//Unlock the forks when released by a philo

void	release_forks(t_meal *meal)
{
	if (meal->total_philos == 1)
		return ;
	sem_post(meal->forks_sem);
	sem_post(meal->forks_sem);
}

//Create thread snf processes

void	start_meal(t_meal *meal)
{
	int	i;
	
	i = 0;
	while (i < meal->total_philos)
	{
		meal->philos[i].pid = fork();
		if (meal->philos[i].pid == -1)
			free_and_close("Error: fork failed\n", meal->philos[i].pid, meal, 0);
		else if (meal->philos[i].pid == 0)
		{
			routine(&(meal)->philos[i]);
			exit(0);
		}
		i++;
	}
}
