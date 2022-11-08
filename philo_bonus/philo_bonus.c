/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:27:00 by greita            #+#    #+#             */
/*   Updated: 2022/05/14 14:44:07 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int
	ft_create_childs(t_vars *vars)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = vars->philos;
	while (i < vars->number_of_philosophers)
	{
		philos[i].process_id = fork();
		if (philos[i].process_id == -1)
			return (-1);
		if (philos[i].process_id == 0)
			ft_live_like_philo(&philos[i]);
		usleep(100);
		i++;
	}
	return (0);
}

void
	ft_wait_all(t_vars *vars)
{
	int	i;
	int	j;
	int	status;
	int	exit_status;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (exit_status == PHILO_DEAD)
		{
			j = 0;
			while (j < vars->number_of_philosophers)
			{
				kill(vars->philos[j].process_id, SIGKILL);
				j++;
			}
		}
		else if (exit_status == PHILO_FULL)
			vars->count_full_philos++;
		if (vars->count_full_philos == vars->number_of_philosophers)
			ft_print_state(STATE_FULL, vars->philos);
		i++;
	}
}

int
	main(int argc, char **argv)
{
	t_vars	vars;

	if (ft_init_args(&vars, argc, argv))
		return (-1);
	if (ft_init_vars(&vars))
	{
		ft_close_unlink_sems(&vars);
		free(vars.philos);
		return (-1);
	}
	if (ft_create_childs(&vars))
	{
		ft_close_unlink_sems(&vars);
		free(vars.philos);
		return (-1);
	}
	ft_wait_all(&vars);
	ft_close_unlink_sems(&vars);
	free(vars.philos);
	return (0);
}
