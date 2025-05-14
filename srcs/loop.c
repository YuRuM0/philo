/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:38:10 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 22:02:38 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	loop_eat(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->id % 2)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	else
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(first);
	print_statement(philo->arg, *philo, "has taken a fork");
	pthread_mutex_lock(second);
	philo->t_last_eat = ft_gettime();
	print_statement(philo->arg, *philo, "is eating");
	loading(philo->arg->t_eat);
	philo->n_eaten++;
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

static void	loop_rest(t_philo *philo)
{
	print_statement(philo->arg, *philo, "is sleeping");
	loading(philo->arg->t_sleep);
	print_statement(philo->arg, *philo, "is thinking");
}

void	*loop(void *arg)
{
	t_philo	*philo;
	int		exit;

	philo = (t_philo *)arg;
	while (philo->arg->ready != 1)
		usleep(10);
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		exit = 0;
		pthread_mutex_lock(&philo->arg->dead_mutex);
		if (philo->arg->dead == 1)
			exit = 1;
		pthread_mutex_unlock(&philo->arg->dead_mutex);
		pthread_mutex_lock(&philo->arg->done_mutex);
		if (philo->arg->done == 1)
			exit = 1;
		pthread_mutex_unlock(&philo->arg->done_mutex);
		if (exit)
			break;
		loop_eat(philo);
		loop_rest(philo);
	}
	return (0);
}
