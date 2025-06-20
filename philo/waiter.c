/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:48:03 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:27:44 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//thread that monitors philos

void	waiter(t_philos *philos)
{
	while (1)
	{
		
		if (!philos->alive)
			break ;
	}
}
