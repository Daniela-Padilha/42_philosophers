/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:31:04 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//the routine the philos will follow

void	*routine (void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (philos->alive)
	{
		think(philos);
		eat(philos);
		sleeping(philos);
	}
	return (NULL);
}

//mutexes to lock the forks when grabed by a philo

void	grab_forks(t_philos *philos)
{
	pthread_mutex_lock(&philos->left_fork);
	pthread_mutex_lock(&philos->right_fork);
	pthread_mutex_lock(&philos->print);
	printf("i am grabing forks\n");
	pthread_mutex_unlock(&philos->print);
}

//mutexes to unlock the forks when released by a philo

void	release_forks(t_philos *philos)
{
	pthread_mutex_unlock(&philos->left_fork);
	pthread_mutex_unlock(&philos->right_fork);
	pthread_mutex_lock(&philos->print);
	printf("i am releasing forks\n");
	pthread_mutex_unlock(&philos->print);
}
