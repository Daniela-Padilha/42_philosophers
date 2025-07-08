/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:59:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 00:37:09 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//get time in microseconds

size_t	get_time(void)
{
	struct timeval	t_value;

	if (gettimeofday(&t_value, NULL) == -1)
		write(2, "ERROR: gettimeofday failed\n", 27);
	return (t_value.tv_sec * 1000000 + t_value.tv_usec);
}

//Improved sleep function

int	my_usleep(size_t micro, t_philos *philos)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < micro)
	{
		if (dead_check(philos))
			break ;
		usleep(50);
	}
	return (0);
}

//make threads wait for all to be ready
// void	sync_threads(t_philos *philos, int wait)
// {
// 	bool	ready;

// 	if (wait == 1)
// 	{
// 		while (1)
// 		{
// 			pthread_mutex_lock(philos->sync);
// 			ready = philos->threads_ready;
// 			pthread_mutex_unlock(philos->sync);
// 			if (ready == false)
// 				break ;
// 			my_usleep(1, philos);
// 		}
// 	}
// 	else if (wait == 0)
// 	{
// 		pthread_mutex_lock(philos->sync);
// 		philos->threads_ready = true;
// 		pthread_mutex_unlock(philos->sync);
// 	}
// 	return ;
// }
