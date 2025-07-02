/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:14:42 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/02 18:29:16 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_meal	*meal;

	if (arg_check(ac, av) == -1)
		return (0);
	meal = init(av);
	start_meal(meal);
	// kill_processes(meal);
	wait_childs(meal);
	free(meal->philos);
	free_and_close(NULL, -1, meal, 1);
	unlink_all();
	return (0);
}
