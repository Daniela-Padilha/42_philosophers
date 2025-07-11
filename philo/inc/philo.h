/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:33 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/11 12:06:15 by ddo-carm         ###   ########.fr       */
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

# define PHILO_MAX 200

typedef struct s_philos
{
	pthread_t		thread;
	int				id;
	int				total_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				total_meals;
	int				meals_eaten;
	time_t			last_meal;
	time_t			dinner_start;
	bool			*dead_flag;
	bool			*start_bool;
	bool			eating;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*eating_lock;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*start_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philos;

typedef struct s_meal
{
	bool			start_bool;
	bool			dead_flag;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	death;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	t_philos		*philos;
}	t_meal;

//parsing
int		arg_check(int ac, char **av);
int		arg_check_util(char **av);

//init
void	init_meal(t_meal *meal, t_philos *philos);
void	init_forks(pthread_mutex_t *forks, int total_philos);
void	init_philos(t_philos *philos, t_meal *meal,
			pthread_mutex_t *forks, char **av);
void	init_input(t_philos *philos, char **av);

//routine
void	*routine(void *arg);
bool	dead_check(t_philos *philos);
void	start_meal(t_meal *meal, pthread_mutex_t *forks);
void	grab_forks(t_philos *philos);
void	release_forks(t_philos *philos);

//actions
void	think(t_philos *philos);
void	eat(t_philos *philos);
void	sleeping(t_philos *philos);

//waiter.c
void	*waiter(void *arg);
bool	starved(t_philos *philos, time_t time_to_die);
bool	funeral(t_philos *philos);
bool	no_more_food(t_philos *philos);
void	speak(char *msg, t_philos *philos, int id);

//time.c
time_t	get_time(void);
int		my_usleep(time_t micro, t_philos *philos);

//utils
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_strlen(char *str);
void	free_and_destroy(char *err, t_meal *meal, pthread_mutex_t *forks);

#endif