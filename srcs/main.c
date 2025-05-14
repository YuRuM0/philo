/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:59 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 22:22:53 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_thread(t_arg *arg, t_philo *philo)
{
	int	i;
	pthread_t checker_thread;

	i  = 0;
	while (i < arg->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, loop, &philo[i]))
			return (print_error(ERR_THREAD), 1);
		i++;
	}
	arg->ready = 1;
	//
	if (pthread_create(&checker_thread, NULL, check_overall, philo))
		return (print_error(ERR_THREAD), 1);
	i = 0;
	while (i < arg->n_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(checker_thread, NULL);
	return (0);
}

static int combined_init(int argc, char *argv[], t_arg *arg, t_philo *philo)
{
	if (init_arg(argc, argv, arg))
		return (free(arg), 1);
	if (init_mutex(arg))
		return (free(arg), 1);
	if (init_philo(arg, philo))
	{
		free(arg->fork);
		free(arg);
		free(philo);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int errno;
	t_arg *arg;
	t_philo *philo;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (print_error(ERR_MALLOC_FAIL), 1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (print_error(ERR_MALLOC_FAIL), 1);
	errno = combined_init(argc, argv, arg, philo);
	if (errno)
		return (errno);
	if (run_thread(arg, philo))
		errno = 1;
	if (arg->dead != 1)
		printf("Everyone survived!");
	clean_up(arg, philo);
	return (errno);
}
