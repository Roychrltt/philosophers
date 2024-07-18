/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/18 16:59:53 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->number_of_philos)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	free(params->philos);
	free(params->forks);
}

int main(int argc, char **argv)
{
	t_params	params;

	init_params(&params, argc, argv);
	if (!create_philos_and_forks(&params))
		return (EXIT_FAILURE);
	free_all(&params);
	return (0);
}
