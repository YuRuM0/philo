/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:56 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/21 18:09:18 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_done(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->args->n_philo)
	{
		if (philos[i].n_eaten < philos[i].args->t_must_eat)
			return (0);
		i++;
	}
	return (1);
}

static int	check_dead(t_philos *philos)
{
	long long int	checkpoint;

	checkpoint = ft_gettime();
	if (checkpoint - philos->t_last_eat >= philos->args->t_die)
	{
		print_statement(philos, "died");
		philos->dead = 1;
		return (1);
	}
	return (0);
}

void	thread_checker(t_args *args, t_philos *philos)
{
	int	i;

	while (!args->ready)
		usleep(100);
	while (!args->over)
	{
		i = 0;
		while (i < args->n_philo)
		{
			if (check_dead(&philos[i]) == 1)
			{
				pthread_mutex_lock(philos->args->death);
				args->over = 1;
				pthread_mutex_unlock(philos->args->death);
				break ;
			}
			i++;
		}
		if (args->meal_needed && check_if_done(philos))
		{
			args->over = 1;
			printf("All philosophers ate %d times!\n", args->t_must_eat);
		}
	}
}

void	clean_thread(t_args *args, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(philos[i].thread, (void *)&philos[i]);
		i++;
	}
	pthread_mutex_destroy(args->death);
	pthread_mutex_destroy(args->forks);
	free(args->death);
	free(args->forks);
	free(philos);
}
