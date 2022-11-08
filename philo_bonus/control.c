/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:37:00 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 21:38:58 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int
	ft_is_philo_died(t_philos *philo)
{
	long	time;

	if (!sem_wait(philo->sem_last_eat_time_ptr))
	{
		time = ft_get_current_time() - philo->last_eat_time;
		sem_post(philo->sem_last_eat_time_ptr);
	}
	else
		return (1);
	if (time > philo->time_to_die)
	{
		ft_print_state(STATE_DIED, philo);
		return (1);
	}
	return (0);
}

void
	*ft_control(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		sem_wait(philo->sem_is_philo_dead_ptr);
		if (ft_is_philo_died(philo))
			exit (PHILO_DEAD);
		sem_post(philo->sem_is_philo_dead_ptr);
	}
	return (NULL);
}
