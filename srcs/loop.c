/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:15 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/21 18:15:30 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_philos *philos)
{
	if (philos->args->n_philo == 1)
	{
		while (philos->args->over != 1)
			loading(100);
		pthread_mutex_unlock(philos->right_fork);
		return (1);
	}
	return (0);
}

static void	print_think_sleep(t_philos *philos)
{
	print_statement(philos, "is sleeping");
	print_statement(philos, "is thinking");
}

void	*loop(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (!philos->args->ready)
		loading(10);
	if (philos->id % 2)
		loading(philos->args->t_eat * 0.5);
	while (philos->args->over != 1)
	{
		pthread_mutex_lock(philos->left_fork);
		print_statement(philos, "has taken a fork");
		if (one_philo(philos) == 1)
			break ;
		pthread_mutex_lock(philos->right_fork);
		print_statement(philos, "has taken a fork");
		philos->t_last_eat = ft_gettime();
		loading(philos->args->t_eat);
		print_statement(philos, "is eating");
		philos->n_eaten++;
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		print_think_sleep(philos);
		loading(philos->args->t_sleep);
	}
	return (NULL);
}
