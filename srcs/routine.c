/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/09 19:38:01 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_statement(t_arg *arg, t_philo *phil, char *msg)
{
	int time;

	time = ft_gettime();
	if ()
	{

	}
	printf("%d %d %s\n", time, phil->id, "")
}

void	routine(t_arg *arg, t_philo *phil)
{
	pthread_mutex_lock(&phil->fork_l);
	//print time : phil x took a fork
	if (arg->num_philo > 1)
	{
		pthread_mutex_lock(&phil->fork_r);
		//print time : phil x took a fork
		//print eating
		phil->eaten_meal++;
		phil->last_eat = ft_gettime();
		//wait for time to eat
		pthread_mutex_unlock(&phil->fork_r);
	}
	pthread_mutex_unlock(&phil->fork_l);
}
