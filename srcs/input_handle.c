/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:35 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 21:56:00 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	input_checker(char **args)
{
	int i;
	int	j;

	i = 1;
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
	arg->n_philo = ft_atoi(argv[1]);
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		arg->t_must_eat = ft_atoi(argv[5]);
	else
		arg->t_must_eat = 0;
	arg->start_time = ft_gettime();
	arg->done = 0;
	arg->ready = 0;
	return (0);
}

int init_mutex(t_arg *arg)
{
	if (pthread_mutex_init(&arg->dead_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX), 1);
	if (pthread_mutex_init(&arg->done_mutex, NULL) != 0)
		return (print_error(ERR_MUTEX), 1);
	if (pthread_mutex_init(&arg->print, NULL) != 0)
		return (print_error(ERR_MUTEX), 1);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->n_philo);
	if (!arg->fork)
		return (print_error(ERR_MALLOC_FAIL), 1);
	if (pthread_mutex_init(arg->fork, NULL) != 0)
		return (print_error(ERR_MUTEX), 1);
	return (0);
}

int init_philo(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	if (arg->n_philo > 1)
	{
		while (i < arg->n_philo)
		{
			philo[i].n_eaten = 0;
			philo[i].t_last_eat = arg->start_time;
			philo[i].id = i;
			philo[i].arg = arg;
			philo[i].r_fork = &arg->fork[i];
			philo[i].l_fork = &arg->fork[(i + 1) % arg->n_philo];
			i++;
		}
	}
	return (0);
}

void	clean_up(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&arg->dead_mutex);
	pthread_mutex_destroy(&arg->done_mutex);
	pthread_mutex_destroy(&arg->print);
	while (i < arg->n_philo)
	{
		pthread_mutex_destroy(&arg->fork[i]);
		i++;
	}
	free(arg->fork);
	free(arg);
	free(philo);
}
