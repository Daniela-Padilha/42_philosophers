/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:33 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/20 18:34:01 by ddo-carm         ###   ########.fr       */
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
	int				id;
	int				philo_nbr;
	bool			eaten;
	bool			alive;
	size_t			t_start;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	int				eat_times;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	print;
}	t_philos;

//parsing
int		arg_check(int ac, char **av);
int		arg_check_util(char **av);

//init
void	init_philos(t_philos *philos, int ac, char **av);
void	start(t_philos *philos, int total);

//routine
void	*routine (void *arg);
void	grab_forks(t_philos *philos);
void	release_forks(t_philos *philos);

//actions
void	think(t_philos *philos);
void	eat(t_philos *philos);
void	sleeping(t_philos *philos);

//waiter.c
void	waiter(t_philos *philos);

//time.c
size_t	get_time(void);

//utils
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	free_and_destroy(t_philos *philos);

#endif