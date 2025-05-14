/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:25:24 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/13 18:00:14 by yulpark          ###   ########.fr       */
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

int	init_arg(int argc, char *argv[], t_arg *arg)
{
	if (argc < 5 || argc > 7)
		return (print_error(ERR_INVALID_ARG), 1);
	if (ft_atoi(argv[1]) < 1)
		return (print_error(ERR_INVALID_ARG), 1);
	if (input_checker(argv) != 0)
		return (print_error(ERR_INVALID_ARG), 1);
	arg->num_philo = ft_atoi(argv[1]);
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		arg->t_must_eat = ft_atoi(argv[5]);
	else
		arg->t_must_eat = 0;
	arg->start_time = ft_gettime();
	arg->done = 0;
	return (0);
}

int init_mutex(t_arg *arg)
{
	int	i;

	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (!arg->fork)
		return(print_error(ERR_MALLOC_FAIL), 1);
	i = 0;
	while (i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&arg->dead, NULL);
	pthread_mutex_init(&arg->print, NULL);
	return (0);
}

int	init_phil(t_arg *arg, t_philo *phil)
{
	int	i;

	i = 0;
	while (i < arg->num_philo)
	{
		phil[i].id = i + 1; //subject: start from one
		phil[i].eaten_meal = 0;
		phil[i].fork_l = &arg->fork[i];
		phil[i].fork_r = &arg->fork[i % arg->num_philo];
		phil[i].arg = arg;
		i++;
	}
	return (0);
}

int init_thread(t_arg *arg, t_philo *phil)
{
	int	i;
	int	init_time;

	i = 0;
	init_time = ft_gettime();
	while (i < arg->num_philo)
	{
		if (pthread_create((&phil[i]), NULL, &routine, &phil[i] != 0))
			return(print_error(ERR_THREAD));
		phil[i].last_eat = init_time;
		i++;
	}
	return (0);
}