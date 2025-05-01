/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:58:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/02 00:53:51 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum e_error
{
	ERR_MALLOC_FAIL,
	ERR_INVALID_ARG,
	SUCCESS = 0
}	t_error;

typedef struct s_arg
{
	int num_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int	t_must_eat;
}	t_arg;

//handle error
void	print_error(t_error error_type);

//handle input
int		ft_atoi(const char *nptr);
int		init_input(int argc, char *argv[]);

//main
int		main(int argc, char *argv[]);