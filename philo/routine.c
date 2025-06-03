/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:54 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/03 15:10:41 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*routine (void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (alive(philo))
	{
		think(philo);
		grab_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep(philo);
	}
	return (NULL);
}

think()
{
	
}

eat()
{

}

sleep()
{

}
