/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/20 12:37:52 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->num)
	{
		pthread_mutex_destroy(&(params->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(params->print_mutex));
	pthread_mutex_destroy(&(params->check_dead));
	free(philos);
	free(params->forks);
}

static int	check_philo_alive(t_philo *philo, long long current)
{
	long long	time_since_eat;

	pthread_mutex_lock(&(philo->meal_mutex));
	time_since_eat = current - philo->last_meal;
	pthread_mutex_unlock(&(philo->meal_mutex));
	if (time_since_eat > philo->time_to_die)
	{
		pthread_mutex_lock(&(philo->params->check_dead));
		philo->params->dead = 1;
		pthread_mutex_unlock(&(philo->params->check_dead));
		print_action(philo->params, philo->pos, DEAD);
		return (1);
	}
	return (0);
}

static void	*death(void *arg)
{
	t_philo		**philos;
	t_params	*params;
	int			cur;

	philos = (t_philo **)arg;
	params = philos[0]->params;
	while (1)
	{
		cur = 0;
		while (cur < params->num)
		{
			if (check_philo_alive(&(*philos)[cur], get_timestamp(params)))
				break ;
			cur++;
		}
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;
	pthread_t	death_thread;

	init_params(&params, argc, argv);
	philos = NULL;
	if (!create_philos_and_forks(&params, &philos))
		return (EXIT_FAILURE);
	pthread_create(&death_thread, NULL, death, &philos);
	wait_threads(&params, philos);
	pthread_join(death_thread, NULL);
	free_all(&params, philos);
	return (0);
}
