/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:59:20 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:29:15 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//get time in milliseconds

size_t	get_time(void)
{
	struct	timeval t_value;
	
	if (gettimeofday(&t_value, NULL) == -1)
		write(2, "ERROR: gettimeofday failed\n", 27);
	return (t_value.tv_sec * 1000 + t_value.tv_usec / 1000);
}
