/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:15:37 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/20 16:30:01 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define FORK_MSG	"has taken a fork"
# define EAT_MSG	"is eating"
# define THINK_MSG	"is thinking"
# define SLEEP_MSG	"is sleeping"
# define DEAD_MSG	"died"

typedef struct s_params
{
	int				num;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meal_max;
	int				dead;
	struct timeval	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_dead;
}	t_params;

typedef struct s_philo
{
	int				pos;
	int				meal_count;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long long		last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_params		*params;
}	t_philo;

// init
void		init_params(t_params *params, int argc, char **argv);
int			create_philos_and_forks(t_params *params, t_philo **philos);

// utils
int			ft_atoi(const char *str);
void		ft_putstr(const char *str);
long long	get_timestamp(t_params *params);
void		print_action(t_params *params, int pos, char *msg);
void		wait_threads(t_params *params, t_philo *philos);

// life
void		ft_eat(t_philo *philo);
void		*life(void *arg);

#endif
