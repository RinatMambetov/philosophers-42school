/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:44:36 by greita            #+#    #+#             */
/*   Updated: 2022/05/12 19:37:23 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define STATE_FORK		0
# define STATE_EAT		1
# define STATE_SLEEP	2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_FULL		5

typedef struct s_philos
{
	pthread_t			thread_id;
	int					philo_id;
	pthread_mutex_t		*mtx_left_fork;
	pthread_mutex_t		*mtx_right_fork;
	pthread_mutex_t		mtx_last_eat_time;
	pthread_mutex_t		mtx_number_of_times_philo_must_eat;
	pthread_mutex_t		*mtx_print_ptr;
	pthread_mutex_t		*mtx_is_someone_died_ptr;
	long long int		last_eat_time;
	long long int		start_time;
	int					number_of_times_philo_must_eat;
	int					time_to_eat;
	int					time_to_sleep;
	int					*is_someone_died_ptr;
}	t_philos;

typedef struct s_vars
{
	t_philos			*philos;
	pthread_mutex_t		*mtx_forks;
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_is_someone_died;
	long long int		start_time;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					is_someone_died;
}	t_vars;

int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
void			ft_putendl_fd(char *s, int fd);
long			ft_atoi(const char *str);
int				ft_init_args(t_vars *vars, int argc, char **argv);
int				ft_init_vars(t_vars *vars);
long long int	ft_get_current_time(void);
void			*ft_live_like_philo(void *arg);
void			ft_usleep(long long int sleep_time);
void			ft_print_state(int state, t_philos *philo);
void			ft_free_all(t_vars *vars);
void			ft_destroy_all(t_vars *vars);
int				ft_control(t_vars *vars);

#endif
