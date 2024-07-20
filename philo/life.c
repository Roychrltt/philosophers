/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:45:57 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/20 12:44:29 by xiaxu            ###   ########.fr       */
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

void	ft_eat(t_philo *philo)
{
	if (philo->params->num == 1)
	{
		print_action(philo->params, 0, FORK);
		usleep(1000 * philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(&(philo->params->forks[philo->left_fork]));
	print_action(philo->params, philo->pos, FORK);
	pthread_mutex_lock(&(philo->params->forks[philo->right_fork]));
	print_action(philo->params, philo->pos, FORK);
	pthread_mutex_lock(&(philo->meal_mutex));
	print_action(philo->params, philo->pos, EAT);
	if (is_dead(philo))
		return ;
	usleep(1000 * philo->time_to_eat);
	philo->last_meal = get_timestamp(philo->params);
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_unlock(&(philo->params->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->params->forks[philo->right_fork]));
	philo->meal_count++;
}

void	*life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->pos % 2)
		usleep(1000);
	while (!is_dead(philo))
	{
		if (philo->meal_count >= philo->params->meal_max
				&& philo->params->meal_max > 0)
			break ;
		ft_eat(philo);
		print_action(philo->params, philo->pos, SLEEP);
		usleep(1000 * philo->params->time_to_sleep);
		if (is_dead(philo))
			break ;
		print_action(philo->params, philo->pos, THINK);
	}
	return (NULL);
}
