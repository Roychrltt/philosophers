/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/19 14:36:00 by xiaxu            ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	init_params(&params, argc, argv);
	philos = NULL;
	if (!create_philos_and_forks(&params, philos))
		return (EXIT_FAILURE);
	free_all(&params, philos);
	return (0);
}
