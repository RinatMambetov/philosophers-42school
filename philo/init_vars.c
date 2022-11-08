/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:05:34 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 10:41:50 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int
	ft_init_mtx_forks(t_vars *vars)
{
	int	i;

	i = 0;
	vars->mtx_forks = malloc(sizeof(pthread_mutex_t)
			* vars->number_of_philosophers);
	if (!vars->mtx_forks)
	{
		ft_putendl_fd("Error malloc", 2);
		return (-1);
	}
	while (i < vars->number_of_philosophers)
	{
		if (pthread_mutex_init(&vars->mtx_forks[i], NULL))
		{
			ft_putendl_fd("Error mutex", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int
	ft_init_philos_part2(t_vars *vars, t_philos *philo)
{
	philo->is_someone_died_ptr = &vars->is_someone_died;
	philo->mtx_print_ptr = &vars->mtx_print;
	philo->mtx_is_someone_died_ptr = &vars->mtx_is_someone_died;
	philo->start_time = vars->start_time;
	philo->time_to_eat = vars->time_to_eat;
	philo->time_to_sleep = vars->time_to_sleep;
	philo->number_of_times_philo_must_eat
		= vars->number_of_times_each_philosopher_must_eat;
	if (pthread_mutex_init(&philo->mtx_last_eat_time, NULL)
		|| pthread_mutex_init(&philo->mtx_number_of_times_philo_must_eat, NULL))
	{
		ft_putendl_fd("Error mutex", 2);
		return (-1);
	}
	return (0);
}

int
	ft_init_philos(t_vars *vars)
{
	int	i;

	i = 0;
	vars->philos = malloc(sizeof(t_philos)
			* vars->number_of_philosophers);
	if (!vars->philos)
	{
		ft_putendl_fd("Error malloc", 2);
		return (-1);
	}
	while (i < vars->number_of_philosophers)
	{
		if (ft_init_philos_part2(vars, &vars->philos[i]))
			return (-1);
		vars->philos[i].philo_id = i + 1;
		vars->philos[i].mtx_left_fork = &vars->mtx_forks[i];
		if (i == 0)
			vars->philos[i].mtx_right_fork
				= &vars->mtx_forks[vars->number_of_philosophers - 1];
		else
			vars->philos[i].mtx_right_fork = &vars->mtx_forks[i - 1];
		i++;
	}
	return (0);
}

int
	ft_init_vars(t_vars *vars)
{
	vars->is_someone_died = 0;
	vars->start_time = ft_get_current_time();
	if (vars->start_time == -1)
		return (-1);
	if (pthread_mutex_init(&vars->mtx_print, NULL))
	{
		ft_putendl_fd("Error mutex", 2);
		return (-1);
	}
	if (pthread_mutex_init(&vars->mtx_is_someone_died, NULL))
	{
		ft_putendl_fd("Error mutex", 2);
		return (-1);
	}
	if (ft_init_mtx_forks(vars))
		return (-1);
	if (ft_init_philos(vars))
		return (-1);
	return (0);
}
