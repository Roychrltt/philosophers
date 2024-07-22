/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:22:46 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/22 10:40:35 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (result * sign);
}

void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

long long	get_timestamp(t_params *params)
{
	struct timeval	tv;
	long long		ts;

	gettimeofday(&tv, NULL);
	ts = (tv.tv_sec - params->start_time.tv_sec) * 1000
		+ (tv.tv_usec - params->start_time.tv_usec) / 1000;
	return (ts);
}

void	print_action(t_params *params, int pos, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&(params->check_dead));
	if (params->dead)
	{
		pthread_mutex_unlock(&(params->check_dead));
		return ;
	}
	pthread_mutex_unlock(&(params->check_dead));
	timestamp = get_timestamp(params);
	pthread_mutex_lock(&(params->print_mutex));
	printf("%08lld %d %s\n", timestamp, pos + 1, msg);
	pthread_mutex_unlock(&(params->print_mutex));
}
