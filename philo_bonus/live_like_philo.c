/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_like_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:27:24 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 21:39:42 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_take_forks(t_philos *philo)
{
	sem_wait(philo->sem_forks_ptr);
	ft_print_state(STATE_FORK, philo);
	sem_wait(philo->sem_forks_ptr);
	ft_print_state(STATE_FORK, philo);
}

void
	ft_eat(t_philos *philo)
{
	ft_print_state(STATE_EAT, philo);
	ft_usleep(philo->time_to_eat);
	if (!sem_wait(philo->sem_last_eat_time_ptr))
	{
		philo->last_eat_time = ft_get_current_time();
		sem_post(philo->sem_last_eat_time_ptr);
	}
	if (philo->number_of_times_philo_must_eat != -1)
		philo->number_of_times_philo_must_eat--;
}

void
	ft_put_forks(t_philos *philo)
{
	sem_post(philo->sem_forks_ptr);
	sem_post(philo->sem_forks_ptr);
}

void
	ft_sleep(t_philos *philo)
{
	ft_print_state(STATE_SLEEP, philo);
	ft_usleep(philo->time_to_sleep);
}

void
	ft_live_like_philo(t_philos *philo)
{
	philo->last_eat_time = ft_get_current_time();
	if (pthread_create(&philo->thread_id, NULL, &ft_control, (void *)philo))
		exit (1);
	if (pthread_detach(philo->thread_id))
		exit (1);
	while (1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		if (philo->number_of_times_philo_must_eat != -1
			&& (philo->number_of_times_philo_must_eat == 0))
			exit (PHILO_FULL);
		ft_sleep(philo);
		ft_print_state(STATE_THINK, philo);
	}
}
