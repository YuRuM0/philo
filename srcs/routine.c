/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:33:17 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/12 17:06:02 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	loading(int	t)
{
	int checkpoint;

	checkpoint = ft_gettime();
	while ((ft_gettime() - checkpoint) < t)
		usleep(10);
}

void	print_statement(t_arg *arg, t_philo phil, char *msg)
{
	int time;

	time = ft_gettime();
	pthread_mutex_lock(&arg->print);
	printf("%d %d %s\n", time - arg->start_time, phil.id, msg);
	pthread_mutex_unlock(&arg->print);
}

void	routine(t_arg *arg, t_philo phil)
{
	pthread_mutex_lock(&phil.fork_l);
	print_statement(arg, phil, "took a fork.");
	if (arg->num_philo > 1)
	{
		pthread_mutex_lock(&phil.fork_r);
		print_statement(arg, phil, "is eating.");
		phil.eaten_meal++;
		phil.last_eat = ft_gettime();
		loading(arg->t_eat);
		pthread_mutex_unlock(&phil.fork_r);
	}
	pthread_mutex_unlock(&phil.fork_l);
	print_statement(arg, phil, "is sleeping.");
	loading(arg->t_sleep);
	print_statement(arg, phil, "is thinking.");
}

void *play_routine(void *thread_input)
{
    t_thread_input *input;
    t_philo *philo;
    t_arg *arg;

    input = (t_thread_input *)thread_input;
    philo = &input->philo;
    arg = input->arg;
    if (philo->id % 2 == 0)
        usleep(300);
    else
        usleep(1000);
    while (arg->dead == 0 && arg->done == 0)
    {
        // Check if this philosopher has eaten enough
        if (arg->t_must_eat != -1 && philo->eaten_meal >= arg->t_must_eat)
            break;
        routine(arg, *philo);
    }
    return NULL;
}
