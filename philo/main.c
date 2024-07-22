/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/22 10:40:47 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_params *params, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < params->num)
	{
		pthread_mutex_destroy(&(params->forks[i]));
		pthread_mutex_destroy(&((*philos)[i].meal_mutex));
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&(params->print_mutex));
	pthread_mutex_destroy(&(params->check_dead));
	free(*philos);
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
		print_action(philo->params, philo->pos, DEAD_MSG);
		pthread_mutex_lock(&(philo->params->check_dead));
		philo->params->dead = 1;
		pthread_mutex_unlock(&(philo->params->check_dead));
		return (1);
	}
	return (0);
}

static int	check_max_meal(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < (*philos)[0].params->num)
	{
		if ((*philos)[i].meal_count < (*philos)[0].params->meal_max)
			return (0);
		i++;
	}
	return (1);
}

static void	*death(void *arg)
{
	t_philo		**philos;
	t_params	*params;
	int			cur;
	int			check;

	philos = (t_philo **)arg;
	params = philos[0]->params;
	check = 0;
	while (!check)
	{
		cur = 0;
		while (cur < params->num)
		{
			if (check_philo_alive(&(*philos)[cur], get_timestamp(params)))
			{
				check = 1;
				break ;
			}
			cur++;
		}
		if (params->meal_max > 0 && check_max_meal(philos))
			break ;
		usleep(50);
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
	pthread_join(death_thread, NULL);
	free_all(&params, &philos);
	return (0);
}
