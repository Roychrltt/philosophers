/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:01:32 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/18 15:38:32 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_params *params, int cur)
{
	params->philo[cur].pos = cur;
	params->philo[cur].meal_count = 0;
	params->philo[cur].last_meal = 0;
	params->philo[cur].dead = 0;
	params->philo[cur].left_fork = 0;
	params->philo[cur].right_fork = 0;
	pthread_create(&params->philo[cur].thread, NULL, &life, &params->philos[cur]);
	params->philo[cur].params = *params;
}

int	create_philos_and_forks(t_params *params)
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

static void	print_usage(void)
{
	ft_putstr("Usage: ./philo number_of_philosophers\n");
	ft_putstr("\ttime_to_die (in milliseconds)\n");
	ft_putstr("\ttime_to_eat (in milliseconds)\n");
	ft_putstr("\ttime_to_sleep (in milliseconds)\n");
	ft_putstr("\t[number_of_times_each_philosopher_must_eat] (optional)\n");
	ft_putstr("\tPlease enter only positive integers.\n");
	exit(EXIT_FAILURE);
}

void	init_param(t_params *params, int argc, char **argv)
{
	if (argc < 5 || argv > 6)
		print_usage();
	params->number_of_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->meal_max = -1;
	params->any_dead = 0;
	if (argv > 5)
		params->meal_max = ft_atoi(argv[5]);
	if (params->number_of_philos < 0 || params->time_to_die < 0
			|| params->time_to_eat < 0 || params->time_to_sleep < 0
			|| (argc > 5 && params->meal_max < 0))
		print_usage();
	gettimeofday(&params->start_time, NULL);
	pthread_mutex_init(&params->print_mutex, NULL);
}
