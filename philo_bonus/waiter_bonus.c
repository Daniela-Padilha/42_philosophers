/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:48:03 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 18:20:19 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

//thread that monitors when the program should end

void	*waiter(void *arg)
{
	t_philos	*philos;
	size_t	time_since_meal;
	bool	is_eating;

	philos = (t_philos *)arg;
	while (1)
	{
		sem_wait(philos->meal->waiter_sem);
		time_since_meal =  get_time() - philos->last_meal;
		is_eating = philos->eating;
		if (time_since_meal >= philos->time_to_die && is_eating == false)
		{
			speak("died", philos, philos->id);
			exit(1);
		}
		sem_post(philos->meal->waiter_sem);
		my_usleep(500);
	}
	return (arg);
}

//Checks if everyone ate total_meals

bool	no_more_food(t_meal *meal)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (meal->philos[0].total_meals == -1)
		return (false);
	while (i < meal->total_philos)
	{
		if (meal->philos[i].meals_eaten >= meal->philos[i].total_meals)
			done_eating++;
		i++;
	}
	if (done_eating == meal->total_philos)
	{
		*meal->philos->dead_flag = true;
		return (true);
	}
	return (false);
}

//Prints log

void	speak(char *msg, t_philos *philos, int id)
{
	size_t	time;

	sem_wait(philos->meal->print_sem);
	time = get_time() - philos->dinner_start;
	if (ft_strcmp(msg, "died") == 0)
		printf("%zu		%i %s\n", time, id, msg);
	else if (ft_strcmp(msg, "died") != 0)
		printf("%zu		%i %s\n", time, id, msg);
	sem_post(philos->meal->print_sem);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
