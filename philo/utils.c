/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:22:46 by xiaxu             #+#    #+#             */
/*   Updated: 2024/07/18 17:23:09 by xiaxu            ###   ########.fr       */
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
	ts = (tv.tv_sec - params->start.tv_sec) * 1000 +
		(tv.tv_usec - params->start.tv_usec) / 1000;
	return (ts);
}

void	print_action(t_params *params, int pos, int status)
{
	long long	timestamp;
	char		*msg;

	timestamp = get_timestamp(params);
	if (status == FORK)
		msg = FORK_MSG;
	else if (status == EAT)
		msg = EAT_MSG;
	else if (status == THINK)
		msg = THINK_MSG;
	else if (status == SLEEP)
		msg = SLEEP_MSG;
	else
		msg = DEAD_MSG;
	pthread_mutex_lock(patams->print_mutex);
	printf("%08lld %d %s\n", timestamp, pos + 1, msg);
	pthread_mutex_unlock(patams->print_mutex);
}
