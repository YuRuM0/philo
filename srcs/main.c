/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:05:27 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/12 17:12:38 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checking if finished
//create & destroy thread
//main

/* Fixed thread_routine function */
static int thread_routine(t_arg *arg, t_philo *phil)
{
    int i;
    t_thread_input *inputs;

    inputs = malloc(sizeof(t_thread_input) * arg->num_philo);
    if (!inputs)
        return (print_error(ERR_MALLOC_FAIL), 1);
    i = 0;
    while (i < arg->num_philo)
    {
        inputs[i].arg = arg;
        inputs[i].philo = phil[i];
        phil[i].last_eat = ft_gettime();
        
        if (pthread_create(&phil[i].thread, NULL, (void *)play_routine, &inputs[i]) != 0)
        {
            free(inputs);
            return (print_error(ERR_THREAD_CREATE), 1);
        }
        i++;
    }
    is_done(arg, phil);
    free(inputs);
    return 0;
}

int	main(int argc, char *argv[])
{
	t_arg	*arg;
	t_philo *philo;
	int		i;
	
	if (init_arg(argc, argv, arg) != 0)
		return (1);
	if (init_mutex(arg) != 0 || init_phil(arg, philo) != 0)
		return (1);
	thread_routine(arg, philo);
	i = 0;
	while (i < arg->num_philo)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (&arg->fork[i])
	{
		pthread_mutex_destroy(&arg->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->print);
	free(philo);
	free(arg->fork);
	return (0);	
}
