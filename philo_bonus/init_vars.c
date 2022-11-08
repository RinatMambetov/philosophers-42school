/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:05:34 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 21:46:23 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_init_philos_part2(t_vars *vars, t_philos *philo)
{
	philo->start_time = vars->start_time;
	philo->time_to_eat = vars->time_to_eat;
	philo->time_to_die = vars->time_to_die;
	philo->time_to_sleep = vars->time_to_sleep;
	philo->number_of_times_philo_must_eat
		= vars->number_of_times_each_philosopher_must_eat;
	philo->sem_forks_ptr = vars->sem_forks;
	philo->sem_print_ptr = vars->sem_print;
	philo->sem_is_philo_dead_ptr = vars->sem_is_philo_dead;
	philo->sem_last_eat_time_ptr = vars->sem_last_eat_time;
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
		ft_init_philos_part2(vars, &vars->philos[i]);
		vars->philos[i].philo_id = i + 1;
		i++;
	}
	return (0);
}

int
	ft_init_sems(t_vars *vars)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_EAT);
	vars->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0664,
			vars->number_of_philosophers);
	vars->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0664, 1);
	vars->sem_is_philo_dead = sem_open(SEM_DEAD, O_CREAT | O_EXCL, 0664, 1);
	vars->sem_last_eat_time
		= sem_open(SEM_EAT, O_CREAT | O_EXCL, 0664, 1);
	if (vars->sem_forks == SEM_FAILED
		|| vars->sem_print == SEM_FAILED
		|| vars->sem_is_philo_dead == SEM_FAILED
		|| vars->sem_last_eat_time == SEM_FAILED)
		return (-1);
	return (0);
}

int
	ft_init_vars(t_vars *vars)
{
	vars->count_full_philos = 0;
	vars->start_time = ft_get_current_time();
	if (vars->start_time == -1)
		return (-1);
	if (ft_init_sems(vars))
		return (-1);
	if (ft_init_philos(vars))
		return (-1);
	return (0);
}
