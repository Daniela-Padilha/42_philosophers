/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/12 18:00:59 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*routine (void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (alive(philos))
	{
		think(philos);
		grab_forks(philos);
		eat(philos);
		release_forks(philos);
		sleeping(philos);
	}
	return (NULL);
}

int	alive(t_philos *philos)
{
	usleep (philos->time_to_die);
	if (philos->eaten)
	{
		philos->alive = true;
		return (1);
	}
	else
	{
		philos->alive = false;
		return (0);
	}
}
void	grab_forks(t_philos *philos)
{
	pthread_mutex_lock(philos->left_fork);
	pthread_mutex_lock(philos->right_fork);
	printf("i am grabing forks");
}

void	release_forks(t_philos *philos)
{
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	printf("i am releasing forks");
}
