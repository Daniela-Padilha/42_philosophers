/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:48:03 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/29 22:56:10 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//thread that monitors when the program should end

void	*waiter(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		if (funeral(philos) == true || no_more_food(philos) == true)
			break ;
	}
	return (arg);
}

//Check if philo died of starvation

bool	starved(t_philos *philos, size_t time_to_die)
{
	pthread_mutex_lock(philos->meal);
	if (get_time() - philos->last_meal >= time_to_die
		&& philos->eating == false)
	{
		pthread_mutex_unlock(philos->meal);
		return (true);
	}
	pthread_mutex_unlock(philos->meal);
	return (false);
}

//Changes the flag of a dead philo and prints message

bool	funeral(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].total_philos)
	{
		if (starved(&philos[i], philos[i].time_to_die))
		{
			speak("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].death);
			*philos->dead_flag = true;
			pthread_mutex_unlock(philos[0].death);
			return (true);
		}
		i++;
	}
	return (false);
}

//Checks if everyone ate total_meals

bool	no_more_food(t_philos *philos)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (philos[0].total_meals == -1)
		return (false);
	while (i < philos[0].total_philos)
	{
		pthread_mutex_lock(philos[i].meal);
		if (philos[i].meals_eaten >= philos[i].total_meals)
			done_eating++;
		pthread_mutex_unlock(philos[i].meal);
		i++;
	}
	if (done_eating == philos[0].total_philos)
	{
		pthread_mutex_lock(philos[0].death);
		*philos->dead_flag = true;
		pthread_mutex_unlock(philos[0].death);
		return (true);
	}
	return (false);
}

//Prints log

void	speak(char *msg, t_philos *philos, int id)
{
	size_t	time;

	pthread_mutex_lock(philos->print);
	time = get_time() - philos->dinner_start;
	if (!dead_check(philos))
		printf("%zu %i %s\n", time, id, msg);
	pthread_mutex_unlock(philos->print);
}
