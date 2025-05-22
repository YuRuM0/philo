/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:47:52 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/21 18:42:54 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s, int c)
{
	printf("%s\n", s);
	exit(c);
}

long long int	ft_gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error("Gettimeofday error", 1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long int	ft_atoi(const char *nptr)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

void	loading(int t)
{
	long long int	checkpoint;

	checkpoint = ft_gettime();
	while ((ft_gettime() - checkpoint) < t)
		usleep(100);
}

void	print_statement(t_philos *philos, char *msg)
{
	long long int	time;

	pthread_mutex_lock(philos->args->death);
	if (philos->args->over)
	{
		pthread_mutex_unlock(philos->args->death);
		return ;
	}
	time = ft_gettime();
	printf("%lld %d %s\n", time - philos->args->start_time,
		philos->id + 1, msg);
	pthread_mutex_unlock(philos->args->death);
}
