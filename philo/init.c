/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:01:32 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/20 13:49:05 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_philo *philo, t_params *params, int cur)
{
	philo->pos = cur;
	philo->meal_count = 0;
	philo->time_to_eat = params->time_to_eat;
	philo->time_to_sleep = params->time_to_sleep;
	philo->time_to_die = params->time_to_die;
	philo->last_meal = 0;
	philo->left_fork = cur;
	philo->right_fork = (cur + 1) % params->num;
	philo->params = params;
	pthread_mutex_init(&(philo->meal_mutex), NULL);
	if (pthread_create(&(philo->thread), NULL, &life, philo))
	{
		pthread_mutex_destroy(&(philo->meal_mutex));
		return (0);
	}
	return (1);
}

int	create_philos_and_forks(t_params *params, t_philo **philos)
{
	int	i;

	*philos = malloc(params->num * sizeof (t_philo));
	if (!(*philos))
		return (0);
	params->forks = malloc(params->num * sizeof (pthread_mutex_t));
	if (!params->forks)
	{
		free(*philos);
		return (0);
	}
	i = 0;
	while (i < params->num)
	{
		if (!init_philo(&(*philos)[i], params, i))
		{
			free(*philos);
			free(params->forks);
			return (0);
		}
		pthread_mutex_init(&(params->forks[i]), NULL);
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

void	init_params(t_params *params, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		print_usage();
	params->num = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->meal_max = -1;
	params->dead = 0;
	if (argc > 5)
		params->meal_max = ft_atoi(argv[5]);
	if (params->num < 0 || params->time_to_die < 0
		|| params->time_to_eat < 0 || params->time_to_sleep < 0
		|| (argc > 5 && params->meal_max < 0))
		print_usage();
	gettimeofday(&(params->start_time), NULL);
	pthread_mutex_init(&(params->print_mutex), NULL);
	pthread_mutex_init(&(params->check_dead), NULL);
}
