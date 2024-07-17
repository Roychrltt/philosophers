/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/17 18:36:33 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params	params;

	if (!init_params(&params, argc, argv))
		return (EXIT_FAILURE);
	if (!create_philos(&params))
		return (EXIT_FAILURE);
	free(params->philos);
	free(params->forks);
	return (0);
}
