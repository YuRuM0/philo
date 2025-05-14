/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:45:19 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/14 18:59:21 by yulpark          ###   ########.fr       */
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
	ERR_THREAD,
	ERR_MUTEX
}	t_error;

typedef struct s_arg
{
	int n_philo;
	int t_eat;
	int t_die;
	int t_sleep;
	int t_must_eat;
	int start_time;
	int done;
	int dead;
	int ready;
	pthread_mutex_t dead_mutex;
	pthread_mutex_t done_mutex;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
}	t_arg;

typedef struct s_philo
{
	int n_eaten;
	int t_last_eat;
	int id;
	t_arg *arg;
	pthread_t thread;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
}	t_philo;

// input_handle
int				init_arg(int argc, char *argv[], t_arg *arg);
int				init_mutex(t_arg *arg);
int				init_philo(t_arg *arg);

//loop
void				loop(void *arg);

//utils
int				print_error(t_error error_type);
long long int	ft_gettime(void);
int				ft_atoi(const char *nptr);
void			loading(int	t);
void			print_statement(t_arg *arg, t_philo phil, char *msg);

//main
int				run_thread(t_arg *arg, t_philo *philo);
int				main(int argc, char *argv[]);