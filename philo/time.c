/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:59:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/30 18:48:35 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//get time in milliseconds

size_t	get_time(void)
{
	struct timeval	t_value;

	if (gettimeofday(&t_value, NULL) == -1)
		write(2, "ERROR: gettimeofday failed\n", 27);
	return (t_value.tv_sec * 1000 + t_value.tv_usec / 1000);
}

//Improved sleep function

int	my_usleep(size_t milisec)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milisec)
		;
	return (0);
}

void	sync_threads(t_philos *philos, int wait)
{
	if (wait == 1)
	{
		pthread_mutex_lock(philos->sync);
		if (philos->threads_ready == false)
			my_usleep(50);
		pthread_mutex_unlock(philos->sync);
	}
	else if (wait == 0)
	{
		pthread_mutex_lock(philos->sync);
		philos->threads_ready = true;
		pthread_mutex_unlock(philos->sync);
	}
	return ;
}
