/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:27:00 by greita            #+#    #+#             */
/*   Updated: 2022/05/14 11:57:20 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int
	ft_start(t_vars *vars, int item)
{
	t_philos	*philo;

	while (item < vars->number_of_philosophers)
	{
		philo = &vars->philos[item];
		philo->last_eat_time = ft_get_current_time();
		if (pthread_create(&philo->thread_id, NULL,
				ft_live_like_philo, (void *)philo))
			return (-1);
		if (pthread_detach(philo->thread_id))
			return (-1);
		item += 2;
	}
	return (0);
}

int
	ft_start_threads(t_vars *vars)
{
	if (ft_start(vars, 0))
		return (-1);
	usleep(200);
	if (ft_start(vars, 1))
		return (-1);
	return (0);
}

int
	main(int argc, char **argv)
{
	t_vars	vars;

	if (ft_init_args(&vars, argc, argv))
		return (-1);
	if (ft_init_vars(&vars))
	{
		ft_free_all(&vars);
		return (-1);
	}
	if (ft_start_threads(&vars))
	{
		ft_destroy_all(&vars);
		ft_free_all(&vars);
		return (-1);
	}
	if (ft_control(&vars))
	{
		ft_destroy_all(&vars);
		ft_free_all(&vars);
		return (0);
	}
}
