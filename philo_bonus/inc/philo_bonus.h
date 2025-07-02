/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:35:33 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/07/01 12:53:32 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>


# define PHILO_MAX 200

typedef struct s_philos
{
	int			id;
	pid_t		pid;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			total_meals;
	int			meals_eaten;
	size_t		last_meal;
	size_t		dinner_start;
	bool		*dead_flag;
	bool		eating;
	t_meal		*meal;
}	t_philos;

typedef struct s_meal
{
	bool		dead_flag;
	int			total_philos;
	sem_t		*forks_sem;
	sem_t		*death_sem;
	sem_t		*waiter_sem;
	sem_t		*print_sem;
	t_philos	*philos;
}	t_meal;

//parsing
int		arg_check(int ac, char **av);
int		arg_check_util(char **av);
int		ft_isdigit(int c);

//init
t_meal	*init(char **av);
int		init_meal(t_meal *meal, char **av);
void	init_philos(t_philos *philos, t_meal *meal, char **av);
void	init_input(t_philos *philos, char **av);
void	unlink_all(void);

//routine
void	*routine(void *arg);
bool	dead_check(t_philos *philos);
void	start_meal(t_meal *meal);
void	grab_forks(t_meal *meal);
void	release_forks(t_meal *meal);

//actions
void	think(t_philos *philos);
void	eat(t_meal *meal);
void	sleeping(t_philos *philos);

//waiter.c
void	*waiter(void *arg);
bool	starved(t_philos *philos, size_t time_to_die);
bool	funeral(t_philos *philos);
bool	no_more_food(t_philos *philos);
void	speak(char *msg, t_philos *philos, int id);

//time.c
size_t	get_time(void);
int		my_usleep(size_t milisec);
void	wait_childs(t_meal *meal);

//utils
long	ft_atol(const char *nptr);
int		ft_atoi(const char *nptr);
int		ft_strlen(char *str);
void	free_and_close(char *err, pid_t pid, t_meal *meal, int free_meal);
void	kill_processes(t_meal *meal);

#endif