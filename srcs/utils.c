/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:01:45 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/13 12:50:17 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(t_error error_type)
{
	if (error_type == ERR_INVALID_ARG)
		printf("Invalid input\n");
	if (error_type == ERR_MALLOC_FAIL)
		printf("Malloc fail\n");
	if (error_type == ERR_TIMEVAL)
		printf("gettimeofday error\n");
	return (1);
}

int	ft_gettime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error(ERR_TIMEVAL);
		return (ERR_TIMEVAL);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

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
void	loading(int	t)
{
	int checkpoint;

	checkpoint = ft_gettime();
	while ((ft_gettime() - checkpoint) < t)
		usleep(10);
}

void	print_statement(t_arg *arg, t_philo phil, char *msg)
{
	int time;

	time = ft_gettime();
	pthread_mutex_lock(&arg->print);
	printf("%d %d %s\n", time - arg->start_time, phil.id, msg);
	pthread_mutex_unlock(&arg->print);
}