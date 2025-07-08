/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:48:03 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/08 01:12:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//thread that monitors when the program should end

void	*waiter(void *arg)
{
	t_meal	*meal;

	meal = (t_meal *)arg;
	while (1)
	{
		if (funeral(meal->philos, meal) || no_more_food(meal->philos, meal))
			return (NULL);
		my_usleep(1000, meal->philos);
	}
	return (arg);
}

//Check if philo died of starvation

bool	starved(t_philos *philos, t_meal *meal, size_t time_to_die)
{
	size_t	time_since_meal;
	bool	is_eating;

	pthread_mutex_lock(&meal->meal_lock);
	time_since_meal = get_time() - philos->last_meal;
	pthread_mutex_unlock(&meal->meal_lock);
	pthread_mutex_lock(&meal->eating_lock);
	is_eating = philos->eating;
	pthread_mutex_unlock(&meal->eating_lock);
	if (time_since_meal >= time_to_die && is_eating == false)
		return (true);
	return (false);
}

//Changes the flag of a dead philo and prints message

bool	funeral(t_philos *philos, t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->total_philos)
	{
		if (starved(&philos[i], meal, meal->time_to_die))
		{
			speak("died", &philos[i], philos[i].id);
			pthread_mutex_lock(&meal->death_lock);
			*philos->dead_flag = true;
			pthread_mutex_unlock(&meal->death_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

//Checks if everyone ate total_meals

bool	no_more_food(t_philos *philos, t_meal *meal)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (meal->total_meals == -1)
		return (false);
	while (i < meal->total_philos)
	{
		pthread_mutex_lock(&meal->meal_lock);
		if (philos[i].meals_eaten >= meal->total_meals)
			done_eating++;
		pthread_mutex_unlock(&meal->meal_lock);
		i++;
	}
	if (done_eating == meal->total_philos)
	{
		pthread_mutex_lock(&meal->death_lock);
		*philos->dead_flag = true;
		pthread_mutex_unlock(&meal->death_lock);
		return (true);
	}
	return (false);
}
