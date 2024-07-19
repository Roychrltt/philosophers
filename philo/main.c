/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/19 18:11:45 by xiaxu            ###   ########.fr       */
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

static int	check_philo_all_alive(t_philo *philo)
{
	int	dead_check;

	pthread_mutex_lock(&(philo->params->check_dead));
	dead_check = philo->params->dead;
	pthread_mutex_unlock(&(philo->params->check_dead));
	return (dead_check);
}

static void	*death(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (!check_philo_all_alive(philos))
	{
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
	pthread_create(&death_thread, NULL, death, philos);
	wait_threads(&params, philos);
	pthread_join(death_thread, NULL);
	free_all(&params, philos);
	return (0);
}
