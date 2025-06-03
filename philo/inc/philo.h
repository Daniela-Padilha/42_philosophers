/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:33 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:51 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philos {
	int				philo_nbr;
	bool			eaten;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fotk;
	pthread_mutex_t	*right_fork;
	struct s_philos	*next;
}	t_philos;

//main
int		arg_check(int ac, char **av);
void	start(t_philos *philos, char *philo);

//init
void	init_philos(t_philos *philos, int ac, char **av);

//routine
void	*routine (void *arg);

//utils
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	*free_struct(void *lst);

#endif