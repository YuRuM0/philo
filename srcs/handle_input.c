/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:25:24 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/05 15:21:35 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int input_checker(char **args)
{
	int i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int init_input(int argc, char *argv[])
{
	t_arg	*main_data;
	
	if (argc < 5 || argc > 7)
		return (print_error(ERR_INVALID_ARG), 1);
	if (ft_atoi(argv[1]) < 1)
		return (print_error(ERR_INVALID_ARG), 1);
	if (input_checker(argv) != 0)
		return (print_error(ERR_INVALID_ARG), 1);
	main_data->num_philo = ft_atoi(argv[1]);
	main_data->t_die = ft_atoi(argv[2]);
	main_data->t_eat = ft_atoi(argv[3]);
	main_data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		main_data->t_must_eat = ft_atoi(argv[5]);
	else
		main_data->t_must_eat = 0;
	return (SUCCESS);
}
