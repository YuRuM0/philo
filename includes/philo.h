/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:58:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/09 18:53:11 by yulpark          ###   ########.fr       */
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
	SUCCESS = 0,
	ERR_TIMEVAL
}	t_error;

typedef struct s_arg
{
	int num_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int	t_must_eat;
	int start_time;
	pthread_mutex_t *dead;
	pthread_mutex_t print;
	pthread_mutex_t *fork; //array of all possible forks
}	t_arg;

typedef struct s_philo
{
	int eaten_meal;
	int last_eat;
	int id;
	int dead;
	pthread_t thread;
	pthread_mutex_t fork_l;
	pthread_mutex_t fork_r;
	t_arg	*data;
}	t_philo;

//handle input
void	init_main(int argc, char *argv[]);

//utils
int		ft_atoi(const char *nptr);
void	print_error(t_error error_type);
int		ft_gettime(void);

//main
int		main(int argc, char *argv[]);
