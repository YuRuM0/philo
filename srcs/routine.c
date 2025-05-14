/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/13 18:22:04 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->dead);
	if (ft_gettime() - philo->last_eat >= philo->arg->t_die)
	{
		pthread_mutex_unlock(philo->arg->dead);
		philo->arg->dead = 1;
		print_statement(philo->arg, *philo, "is dead");
	}
	pthread_mutex_unlock(philo->arg->dead);
}

int is_done(t_philo philo)
{
	
}

int routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->arg->print);
	print_statement(philo->arg, *philo, " has taken a fork");
	pthread_mutex_unlock(&philo->arg->print);
	pthread_mutex_lock(&philo->fork_r);
	philo->last_eat = ft_gettime();
	pthread_mutex_lock(&philo->arg->print);
	print_statement(philo->arg, *philo, " is eating");
	pthread_mutex_unlock(&philo->arg->print);
	loading(&philo->arg->t_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(&philo->fork_r);
	print_statement(philo->arg, *philo, " is sleeping");
	loading(&philo->arg->t_sleep);
	print_statement(philo->arg, *philo, " is thinking");
}

int	thread(t_arg *arg)
{
	t_philo *phil;
	int	i;
	
	phil = malloc(sizeof(t_philo) * arg->num_philo);
	if (!phil)
		return(print_error(ERR_MALLOC_FAIL), 1);
	if (init_phil(arg, phil) != 0)
		return (1);
	if (init_thread(arg, phil) != 0)
		return (1);
	//check
	i = 0;
	while (i < arg->num_philo)
	{
		pthread_join(phil[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(arg->dead);
	pthread_mutex_destroy(arg->fork);
	pthread_mutex_destory(arg->print);
	free(arg->fork);
	return (0);
}
