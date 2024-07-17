/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:15:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/17 18:36:21 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct	s_philo
{
	int				pos;
	int				meal_count;
	int				dead;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_params		*params;
}	t_philo;

typedef struct	s_params
{
	int				number_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meal_max;
	int				dead;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_params;

// init
int		init_params(t_params params);
int		create_philos(t_params params);

// utils
int		ft_atoi(const char* str);
void	ft_putstr(const char *str);

#endif
