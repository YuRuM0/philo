/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:53:59 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 19:55:46 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int run_thread(t_arg *arg, t_philo *philo)
{
	int	i;

	i  = 0;
	while (i < arg->n_philo)
	{
		if (!pthread_create(&philo[i].thread, NULL, &loop, NULL))
			return (print_error(ERR_THREAD), 1);
		i++;
	}
	arg->ready = 1;
	while (i < arg->n_philo)
	{
		pthread_join(&philo[i].thread, NULL);
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_arg	*arg;
	t_philo *philo;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (print_error(ERR_MALLOC_FAIL), NULL);
	if (!init_arg(argc, argv, arg))
		return (1);
	philo = malloc(sizeof(t_philo) * arg->n_philo);
	if (!init_philo(arg))
		return (1);
	run_thread(arg, philo);
	//check
	pthread_mutex_destroy(&arg->dead_mutex);
	pthread_mutex_destroy(&arg->done_mutex);
	pthread_mutex_destroy(&arg->print);
	pthread_mutex_destroy(arg->fork);
	free(arg);
	free(arg->fork);
	return (0);
}
