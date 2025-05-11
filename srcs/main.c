/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:05:27 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/11 15:02:37 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checking if finished
//create & destroy thread
//main

void	is_done(t_arg *arg, t_philo *phil)
{
	// if more than time to die-> die
	// print die
	// if eating done || someone dies
		// terminate
}

int	main(int argc, char *argv[])
{
	t_arg	*arg;
	t_philo *phil;
	int		i;
	
	if (init_arg(argc, argv, arg) != 0)
		return (1);
	if (init_mutex(arg) != 0 != 0)
		return (1);
	if (init_phil(arg, phil) != 0)
		return (1);
	//run the programme!
	i = 0;
	while (&arg->fork[i])
	{
		pthread_mutex_destroy(&arg->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&arg->print);
	free(phil);
	free(arg->fork);
	return (0);	
}
