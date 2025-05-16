/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:43:28 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/16 17:23:35 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_checker(int argc, char **args)
{
	int i;
	int	j;

	if (argc != 5 && argc != 6)
		return (1);
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
void arg_init(int argc, char *argv[], t_args *args)
{
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->t_must_eat = -1;
	args->meal_needed = 0;
	if (argc == 6)
	{
		args->meal_needed = 1;
		args->t_must_eat = ft_atoi(argv[5]);
	}
	args->start_time = 0;
	args->ready = 0;
	args->over = 0;
	args->death = malloc(sizeof(pthread_mutex_t));
	if (!args->death)
		print_error("Malloc fail", 1);
	if (pthread_mutex_init(args->death, NULL) != 0)
		print_error("Mutex fail", 1);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n_philo);
	if (!args->forks)
	{
		free(args->death);
		print_error("Malloc fail", 1);
	}
}

void philo_init(t_args *args, t_philos *philos)
{
	int i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i++], NULL) != 0)
		{
			free(args->death);
			free(args->forks);
			print_error("Mutex fail", 1);
		}
	}
	i = -1;
	while (++i < args->n_philo)
	{
		philos[i].id = i;
		philos[i].dead = 0;
		philos[i].n_eaten = 0;
		philos[i].t_last_eat = 0;
		philos[i].thead_start = 0;
		philos[i].args = args;
		philos[i].left_fork = &args->forks[i];
		philos[i].right_fork = &args->forks[(i + 1) % (args->n_philo)];
	}
}

void thread_init(t_args *args, t_philos *philos)
{
	int i;

	i = -1;
	while (++i < args->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &loop, &philos[i]) != 0)
		{
			free(args->death);
			free(args->forks);
			free(philos);
			print_error("Thread creation fail", 1);
		}
	}
	args->start_time = ft_gettime();
	i = -1;
	while (++i < args->n_philo)
	{
		philos[i].t_last_eat = args->start_time;		
		philos[i].thead_start = args->start_time;
	}
	args->ready = 1;
	thread_checker(args, philos);
	clean_thread(args, philos);
}
