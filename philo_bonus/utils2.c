/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:23:35 by greita            #+#    #+#             */
/*   Updated: 2022/05/14 12:32:20 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->sem_print_ptr);
	time = ft_get_current_time() - philo->start_time;
	if (state == 0)
		printf("%lld %d has taken a fork\n", time, philo->philo_id);
	if (state == 1)
		printf("%lld %d is eating\n", time, philo->philo_id);
	if (state == 2)
		printf("%lld %d is sleeping\n", time, philo->philo_id);
	if (state == 3)
		printf("%lld %d is thinking\n", time, philo->philo_id);
	if (state == 4)
		printf("%lld %d died\n", time, philo->philo_id);
	if (state == 5)
		printf("Each of philosophers is full\n");
	sem_post(philo->sem_print_ptr);
}

void
	ft_close_unlink_sems(t_vars *vars)
{
	sem_close(vars->sem_forks);
	sem_unlink(SEM_FORKS);
	sem_close(vars->sem_print);
	sem_unlink(SEM_PRINT);
	sem_close(vars->sem_is_philo_dead);
	sem_unlink(SEM_DEAD);
	sem_close(vars->sem_last_eat_time);
	sem_unlink(SEM_EAT);
}
