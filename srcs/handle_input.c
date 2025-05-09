/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:25:24 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/09 19:02:34 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	input_checker(char **args)
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

void	init_main(int argc, char *argv[])
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
		main_data->t_must_eat = -1;
	main_data->dead = 0;
	main_data->start_time = ft_gettime();
}

int	init_phil(t_arg *arg, t_philo *phil, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	phil = malloc(sizeof(t_philo) * arg->num_philo);
	if (!phil)
		return (-1);
	while (i < arg->num_philo)
	{
		phil[i].id = i + 1; //subject: start from one
		phil[i].dead = 0;
		phil[i].eaten_meal = 0;
		phil[i].fork_l = forks[i];
		phil[i].fork_r = forks[i % arg->num_philo];
		phil[i].last_eat = ft_gettime();
		i++;
	}
	return (0);
}

int init_mutex(t_arg *arg)
{
	int	i;

	pthread_mutex_init(&arg->dead, NULL);
	pthread_mutex_init(&arg->print, NULL);
	pthread_mutex_init(&arg->fork, NULL);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (!arg->fork)
	return(-1);
	i = 0;
	while (i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
		i++;
	}
	return (0);
}
