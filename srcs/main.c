/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/21 17:37:14 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args		args;
	t_philos	*philos;

	if (input_checker(argc, argv) == 0)
	{
		arg_init(argc, argv, &args);
		philos = malloc(sizeof(t_philos) * args.n_philo);
		if (!philos)
		{
			free(args.death);
			free(args.forks);
			print_error("Malloc fail", 1);
		}
		philo_init(&args, philos);
		thread_init(&args, philos);
	}
	else
	{
		printf("Invalid Input\n");
		return (1);
	}
	return (0);
}
