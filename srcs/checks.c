/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:56 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/16 18:26:12 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_if_done(t_philos *philos)
{
	int i;

	i = 0;
	while (i < philos->args->n_philo)
	{
		if (philos[i].n_eaten < philos[i].args->t_must_eat)
			return (0); // at least one hasn't eaten enough
		i++;
	}
	usleep(300);
	return (1);
}
static int check_dead(t_philos *philos)
{
    long long int checkpoint;
    
    pthread_mutex_lock(philos->args->death);
    checkpoint = ft_gettime();
    if (checkpoint - philos->t_last_eat >= philos->args->t_die)
    {
		pthread_mutex_unlock(philos->args->death);
        print_statement(philos, "died");
        philos->dead = 1;
        philos->args->over = 1;
        pthread_mutex_unlock(philos->right_fork);
		pthread_mutex_unlock(philos->left_fork);
        return (1);
    }
    pthread_mutex_unlock(philos->args->death);
    return (0);
}

void thread_checker(t_args *args, t_philos *philos)
{
	int	i;

	while (!args->ready)
		usleep(100);
	while (!args->over)
	{
		i = 0;
		while (i < args->n_philo)
		{
			if (check_dead(&philos[i]) == 1)
				args->over = 1;	
			i++;		
		}
		if (args->meal_needed && check_if_done(philos))
		{
			args->over = 1;
			printf("All philosophers ate %d times and are happy!\n", args->t_must_eat);
		}
	}
}

void clean_thread(t_args *args, t_philos *philos)
{
	int i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(philos[i].thread, (void *)&philos[i]);
		i++;
	}
	pthread_mutex_destroy(args->death);
	pthread_mutex_destroy(args->forks);
	free(args->death);
	free(args->forks);
	free(philos);
}
