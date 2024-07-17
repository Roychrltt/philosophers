/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:14:01 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/17 11:00:29 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params	params;
	int			cur;

	init_params(&params, argc, argv);
	create_philos(&params);
	cur = 0;
	while (cur < ft_atoi(argv[1]))
	{
		init_philos(params, cur);
		cur++;
	}
	return (0);
}
