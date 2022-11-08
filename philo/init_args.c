/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:55:02 by greita            #+#    #+#             */
/*   Updated: 2022/05/10 20:16:56 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int
	ft_check_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		return (-1);
	}
	return (0);
}

int
	ft_check_args_is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				ft_putendl_fd("Invalid arguments", 2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int
	ft_check_value_of_args(t_vars *vars)
{
	if (vars->number_of_philosophers < 1 || vars->number_of_philosophers > 200)
		return (-1);
	if (vars->time_to_die < 60 || vars->time_to_die > INT_MAX)
		return (-1);
	if (vars->time_to_eat < 60 || vars->time_to_eat > INT_MAX)
		return (-1);
	if (vars->time_to_sleep < 60 || vars->time_to_sleep > INT_MAX)
		return (-1);
	if (vars->number_of_times_each_philosopher_must_eat == 0
		|| vars->number_of_times_each_philosopher_must_eat > INT_MAX)
		return (-1);
	return (0);
}

int
	ft_init_args(t_vars *vars, int argc, char **argv)
{
	if (ft_check_number_of_args(argc))
		return (-1);
	if (ft_check_args_is_digit(argc, argv))
		return (-1);
	vars->number_of_philosophers = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		vars->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		vars->number_of_times_each_philosopher_must_eat = -1;
	if (ft_check_value_of_args(vars))
	{
		ft_putendl_fd("Invalid value of arguments", 2);
		return (-1);
	}
	return (0);
}
