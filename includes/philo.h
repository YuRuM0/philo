/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:58:00 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/13 18:00:05 by yulpark          ###   ########.fr       */
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
	ERR_TIMEVAL,
	ERR_THREAD
}	t_error;

typedef struct s_arg
{
	int num_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int	t_must_eat;
	int start_time;
	int	done;
	pthread_mutex_t *dead;
	pthread_mutex_t print;
	pthread_mutex_t *fork; //array of all possible forks
}	t_arg;

typedef struct s_philo
{
	int eaten_meal;
	int last_eat;
	int id;
	t_arg	*arg;
	pthread_t thread;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
}	t_philo;

//handle input
int		init_arg(int argc, char *argv[], t_arg *main_data);
int		init_phil(t_arg *arg, t_philo *phil);
int		init_mutex(t_arg *arg);
int		init_thread(t_arg *arg, t_philo *phil);

//utils
int		ft_atoi(const char *nptr);
int		print_error(t_error error_type);
int		ft_gettime(void);
void	print_statement(t_arg *arg, t_philo phil, char *msg);
void	loading(int	t);

//routine
int routine(t_philo *philo);
int	thread(t_arg *arg);

//main
int		main(int argc, char *argv[]);
