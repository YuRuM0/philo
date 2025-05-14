/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:57:38 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 22:23:24 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dead(t_arg *arg, t_philo *philo)
{
	long long int	now;
	int				i;

	i = 0;
	now = ft_gettime();
	pthread_mutex_lock(&arg->dead_mutex);
	while (i < arg->n_philo && arg->dead == 0)
	{
		if (now - philo[i].t_last_eat > arg->t_die)
		{
			print_statement(arg, philo[i], "died");
			arg->dead = 1;
		}
		i++;
	}
	pthread_mutex_unlock(&arg->dead_mutex);
}

static void	is_done(t_arg *arg, t_philo *philo)
{
	int	full;
	int	i;

	i = 0;
	full = 0;
	if (arg->t_must_eat <= 0)
        return ;
	while (i < arg->n_philo)
	{
		if (philo[i].n_eaten >= arg->t_must_eat)
			full++;
		i++;
	}
	pthread_mutex_lock(&arg->done_mutex);
	if (full == arg->n_philo)
		arg->done = 1;
	pthread_mutex_unlock(&arg->done_mutex);
}

void *check_overall(void *arginput)
{
	t_arg *arg;
	t_philo *philo;

	philo = (t_philo *)arginput;
	arg = philo->arg;
	while (1)
	{
		is_dead(arg, philo);
		is_done(arg, philo);
		pthread_mutex_lock(&arg->dead_mutex);
		pthread_mutex_lock(&arg->done_mutex);
		if (arg->done == 1 || arg->dead == 1)
			break;
		pthread_mutex_unlock(&arg->dead_mutex);
		pthread_mutex_unlock(&arg->done_mutex);
		usleep(1000);
	}
	return (0);
}
