/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:01:32 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/17 18:36:29 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_params *params, int cur)
{
	params->philo[cur].pos = cur;
	params->philo[cur].meal_count = 0;
	params->philo[cur].dead = 0;
	params->philo[cur].left_fork = 0;
	params->philo[cur].right_fork = 0;
	params->philo[cur].thread = 0;
	params->philo[cur].params = *params;
}

int	create_philo(t_params *params)
{
	int	i;

	params->philos = malloc(params->number_of_philos * sizeof (t_philo));
	if (!params->philos)
		return (0);
	params->forks = malloc(params->number_of_philos
			* sizeof (pthread_mutex_t));
	if (!params->forks)
	{
		free(params->philos);
		return (0);
	}
	i = 0;
	while (i < params->number_of_philos)
	{
		init_philo(params, i);
		i++;
	}
	return (1);
}

int	init_param(t_params *params, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr("Usage: ./philo number_of_philosophers time_to_die ");
		ft_putstr("time_to_eat time_to_sleep [number_of_times_to_eat]\n");
		return (0);
	}
	params->number_of_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->meal_max = -1;
	params->dead = 0;
	if (argv > 5)
		params->meal_max = ft_atoi(argv[5]);
	if (params->number_of_philos < 0 || params->time_to_die < 0
			|| params->time_to_eat < 0 || params->time_to_sleep < 0
			|| (argc > 5 && params->meal_max < 0))
		return (0);
	return (1);
}
