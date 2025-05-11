/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:01:45 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/10 21:20:10 by yulpark          ###   ########.fr       */
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
