/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:44:36 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 21:44:53 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define STATE_FORK		0
# define STATE_EAT		1
# define STATE_SLEEP	2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_FULL		5

# define PHILO_FULL		10
# define PHILO_DEAD		11

# define SEM_FORKS		"/sem_forks"
# define SEM_PRINT		"/sem_print"
# define SEM_DEAD		"/sem_dead"
# define SEM_EAT		"/sem_eat"

typedef struct s_philos
{
	pthread_t			thread_id;
	pid_t				process_id;
	int					philo_id;
	long long int		last_eat_time;
	long long int		start_time;
	int					number_of_times_philo_must_eat;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	sem_t				*sem_forks_ptr;
	sem_t				*sem_print_ptr;
	sem_t				*sem_is_philo_dead_ptr;
	sem_t				*sem_last_eat_time_ptr;
}	t_philos;

typedef struct s_vars
{
	t_philos			*philos;
	long long int		start_time;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					count_full_philos;
	sem_t				*sem_forks;
	sem_t				*sem_print;
	sem_t				*sem_is_philo_dead;
	sem_t				*sem_last_eat_time;
}	t_vars;

int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
void			ft_putendl_fd(char *s, int fd);
long			ft_atoi(const char *str);
int				ft_init_args(t_vars *vars, int argc, char **argv);
int				ft_init_vars(t_vars *vars);
long long int	ft_get_current_time(void);
void			ft_live_like_philo(t_philos *philo);
void			ft_usleep(long long int sleep_time);
void			ft_print_state(int state, t_philos *philo);
void			*ft_control(void *arg);
void			ft_close_unlink_sems(t_vars *vars);

#endif
