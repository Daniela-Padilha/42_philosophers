/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:59:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/07 17:33:19 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// //get time in microseconds

// size_t	get_time(void)
// {
// 	struct timeval	t_value;

// 	if (gettimeofday(&t_value, NULL) == -1)
// 	{
// 		write(2, "ERROR: gettimeofday failed\n", 27);
// 		return (0);
// 	}
// 	return (t_value.tv_sec * 1000000 + t_value.tv_usec);
// }

// //Improved sleep function

// int	my_usleep(size_t micro, t_philos *philos)
// {
// 	size_t	start;
// 	(void)philos;

// 	start = get_time();
// 	while ((get_time() - start) < micro)
// 		usleep(50);
// 	return (0);
// }

int	my_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Gets the current time in milliseconds

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
