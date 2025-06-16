/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:33 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/06/16 17:47:59 by ddo-carm         ###   ########.fr       */
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
	bool			alive;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_times;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philos;

//main
int		arg_check(int ac, char **av);
int		parsing(char **av);
void	start(t_philos *philos, int total);

//init
void	init_philos(t_philos *philos, int ac, char **av);

//routine
void	*routine (void *arg);
int		alive(t_philos *philos);
void	grab_forks(t_philos *philos);
void	release_forks(t_philos *philos);

//actions
void	think(t_philos *philos);
void	eat(t_philos *philos);
void	sleeping(t_philos *philos);

//utils
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	*free_struct(void *lst);

#endif