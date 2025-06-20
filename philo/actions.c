/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:30:15 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:34:07 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//makes philos think while waiting

void	think(t_philos *philos)
{
	size_t	time;
	
	pthread_mutex_lock(&philos->print);
	time = get_time() - philos->t_start;
	printf("%i is thinking\n", philos->philo_nbr);
	pthread_mutex_unlock(&philos->print);
}

//makes philos grab forks, eat and release forks

void	eat(t_philos *philos)
{
	grab_forks(philos);
	usleep(philos->time_to_eat);
	pthread_mutex_lock(&philos->print);
	printf("%i is eating\n", philos->philo_nbr);
	pthread_mutex_unlock(&philos->print);
	release_forks(philos);
}

//makes philos sleep for a determined amout of time

void	sleeping(t_philos *philos)
{
	usleep(philos->time_to_sleep);
	pthread_mutex_lock(&philos->print);
	printf("%i is sleeping\n", philos->philo_nbr);
	pthread_mutex_unlock(&philos->print);
}
