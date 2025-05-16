/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/16 17:01:44 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_args args;
	t_philos *philos;

	if(!input_checker(argc, argv))
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
	return (0);
}
