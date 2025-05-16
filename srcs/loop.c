/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:15 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/16 18:18:12 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//same
void *loop(void *arg)
{
	t_philos *philos;

	philos = (t_philos *)arg;
	while (!philos->args->ready)
		usleep(100);
	if (philos->id % 2)
		loading(philos->args->t_eat * 0.9 + 1);
	while (philos->args->over != 1)
	{
		pthread_mutex_lock(philos->left_fork);
		print_statement(philos, "has taken a fork");
		pthread_mutex_lock(philos->right_fork);
		print_statement(philos, "has taken a fork");
		philos->t_last_eat = ft_gettime();
		loading(philos->args->t_eat);
		print_statement(philos, "is eating");
		philos->n_eaten++;
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		loading(philos->args->t_sleep);
		print_statement(philos, "is sleeping");
		print_statement(philos, "is thinking");
	}
	return (NULL);
}
