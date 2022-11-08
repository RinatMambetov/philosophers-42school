/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:23:35 by greita            #+#    #+#             */
/*   Updated: 2022/05/14 12:31:57 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int
	ft_get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putendl_fd("Error gettimeofday", 2);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void
	ft_usleep(long long int sleep_time)
{
	long long int	sleep_start_time;

	sleep_start_time = ft_get_current_time();
	while (1)
	{
		if (ft_get_current_time() - sleep_start_time >= sleep_time)
			break ;
		usleep(500);
	}
}

void
	ft_print_state(int state, t_philos *philo)
{
	long long int	time;

	pthread_mutex_lock(philo->mtx_print_ptr);
	time = ft_get_current_time() - philo->start_time;
	if (state == STATE_FORK)
		printf("%lld %d has taken a fork\n", time, philo->philo_id);
	if (state == STATE_EAT)
		printf("%lld %d is eating\n", time, philo->philo_id);
	if (state == STATE_SLEEP)
		printf("%lld %d is sleeping\n", time, philo->philo_id);
	if (state == STATE_THINK)
		printf("%lld %d is thinking\n", time, philo->philo_id);
	if (state == STATE_DIED)
		printf("%lld %d died\n", time, philo->philo_id);
	if (state == STATE_FULL)
		printf("Each of philosophers is full\n");
	pthread_mutex_unlock(philo->mtx_print_ptr);
}

void
	ft_free_all(t_vars *vars)
{
	free(vars->mtx_forks);
	free(vars->philos);
}

void
	ft_destroy_all(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		pthread_mutex_destroy(&vars->mtx_forks[i]);
		pthread_mutex_destroy(&vars->philos[i].mtx_last_eat_time);
		pthread_mutex_destroy(&vars
			->philos[i].mtx_number_of_times_philo_must_eat);
		i++;
	}
	pthread_mutex_destroy(&vars->mtx_print);
	pthread_mutex_destroy(&vars->mtx_is_someone_died);
}
