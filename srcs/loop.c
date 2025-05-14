/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:38:10 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 19:04:16 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void loop_eat(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_statement(philo->arg, *philo, " has taken a fork");
}

void loop_rest(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(&arg->print);
	print_statement(philo->arg, *philo, " is sleeping");
	pthread_mutex_unlock(&arg->print);
	loading(&philo->arg->t_sleep);
	pthread_mutex_lock(&arg->print);
	print_statement(philo->arg, *philo, " is thinking");
	pthread_mutex_unlock(&arg->print);
}
void loop(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (philo->arg->ready != 1)
		usleep(10);
	if (philo->id % 2)
		usleep(500);
	
	return (0);
}