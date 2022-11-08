/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_like_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:27:24 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 22:08:22 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_take_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->mtx_left_fork);
	ft_print_state(STATE_FORK, philo);
	pthread_mutex_lock(philo->mtx_right_fork);
	ft_print_state(STATE_FORK, philo);
}

void
	ft_eat(t_philos *philo)
{
	ft_print_state(STATE_EAT, philo);
	ft_usleep(philo->time_to_eat);
	if (!pthread_mutex_lock(&philo->mtx_last_eat_time))
		philo->last_eat_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->mtx_last_eat_time);
	if (!pthread_mutex_lock(&philo->mtx_number_of_times_philo_must_eat))
	{
		if (philo->number_of_times_philo_must_eat != -1)
			philo->number_of_times_philo_must_eat--;
	}
	pthread_mutex_unlock(&philo->mtx_number_of_times_philo_must_eat);
}

void
	ft_put_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->mtx_left_fork);
	pthread_mutex_unlock(philo->mtx_right_fork);
}

void
	ft_sleep(t_philos *philo)
{
	ft_print_state(STATE_SLEEP, philo);
	ft_usleep(philo->time_to_sleep);
}

void *
	ft_live_like_philo(void *arg)
{
	int			temp;
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->mtx_is_someone_died_ptr);
		temp = *(philo->is_someone_died_ptr);
		pthread_mutex_unlock(philo->mtx_is_someone_died_ptr);
		if (!temp)
		{
			ft_take_forks(philo);
			ft_eat(philo);
			ft_put_forks(philo);
			if (philo->number_of_times_philo_must_eat == 0)
				break ;
			ft_sleep(philo);
			ft_print_state(STATE_THINK, philo);
		}
		else
			break ;
	}
	return (NULL);
}
