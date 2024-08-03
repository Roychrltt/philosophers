/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:45:57 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/03 10:35:56 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&(philo->params->check_dead));
	is_dead = philo->params->dead;
	pthread_mutex_unlock(&(philo->params->check_dead));
	return (is_dead);
}

static void	ft_eat(t_philo *philo)
{
	if (philo->params->num == 1)
	{
		print_action(philo->params, 0, FORK_MSG);
		usleep(1000 * philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(&(philo->params->forks[philo->left_fork]));
	print_action(philo->params, philo->pos, FORK_MSG);
	pthread_mutex_lock(&(philo->params->forks[philo->right_fork]));
	print_action(philo->params, philo->pos, FORK_MSG);
	print_action(philo->params, philo->pos, EAT_MSG);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal = get_timestamp(philo->params);
	pthread_mutex_unlock(&(philo->meal_mutex));
	usleep(1000 * philo->time_to_eat);
	pthread_mutex_unlock(&(philo->params->forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->params->forks[philo->left_fork]));
	pthread_mutex_lock(&(philo->count_mutex));
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->count_mutex));
}

void	*life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->params->print_mutex));
	pthread_mutex_unlock(&(philo->params->print_mutex));
	if (philo->pos % 2)
		usleep(1000);
	while (!is_dead(philo))
	{
		ft_eat(philo);
		pthread_mutex_lock(&(philo->count_mutex));
		if ((philo->meal_count >= philo->params->meal_max
				&& philo->params->meal_max > 0) || philo->params->num == 1)
		{
			pthread_mutex_unlock(&(philo->count_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->count_mutex));
		usleep(100);
		print_action(philo->params, philo->pos, SLEEP_MSG);
		usleep(1000 * philo->params->time_to_sleep);
		print_action(philo->params, philo->pos, THINK_MSG);
	}
	return (NULL);
}
