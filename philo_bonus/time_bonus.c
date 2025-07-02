/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:59:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 16:25:54 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

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

//Waits for each child process to finish

void	wait_childs(t_meal *meal)
{
	int	i;
	int	status;

	i = 0;
	while (i < meal->total_philos)
	{
		waitpid(meal->philos[i].pid, &status, 0);
		i++;
	}
}
