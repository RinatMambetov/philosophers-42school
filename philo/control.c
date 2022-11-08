/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:37:00 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 21:35:07 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int
	ft_is_philos_full(t_vars *vars)
{
	int			i;
	int			total;
	t_philos	*philos;

	i = 0;
	total = 0;
	philos = vars->philos;
	if (vars->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (i < vars->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].mtx_number_of_times_philo_must_eat);
		if (philos[i].number_of_times_philo_must_eat == 0)
			total++;
		pthread_mutex_unlock(&philos[i].mtx_number_of_times_philo_must_eat);
		if (total == vars->number_of_philosophers)
		{
			ft_print_state(STATE_FULL, &philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int
	ft_is_philo_died(t_vars *vars)
{
	int				i;
	long long int	time;
	t_philos		*philo;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		philo = &vars->philos[i];
		pthread_mutex_lock(&philo->mtx_last_eat_time);
		time = ft_get_current_time() - philo->last_eat_time;
		pthread_mutex_unlock(&philo->mtx_last_eat_time);
		if (time > vars->time_to_die)
		{
			pthread_mutex_lock(philo->mtx_is_someone_died_ptr);
			*(philo->is_someone_died_ptr) = 1;
			pthread_mutex_unlock(philo->mtx_is_someone_died_ptr);
			ft_print_state(STATE_DIED, philo);
			return (1);
		}
		i++;
	}
	return (0);
}

int
	ft_control(t_vars *vars)
{
	while (1)
	{
		if (ft_is_philos_full(vars))
			return (-1);
		if (ft_is_philo_died(vars))
			return (-1);
	}
	return (0);
}
