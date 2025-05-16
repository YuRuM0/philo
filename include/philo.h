/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:37:58 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/16 16:51:47 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_args
{
	int n_philo;
	int t_die;
	int t_eat;
	int t_sleep;
	int t_must_eat; //loop
	int ready;
	int over;
	int meal_needed;
	long long int start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t *death;
}	t_args;

typedef struct s_philos
{
	int id;
	int dead;
	int n_eaten;
	long long int t_last_eat;
	long long int thead_start;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_args	*args;
}	t_philos;

//utils.c
int	ft_atoi(const char *nptr);
void print_error(char *s, int c);
long long int	ft_gettime(void);
void	print_statement(t_philos *philos, char *msg);
void	loading(int	t);
//init.c
int	input_checker(int argc, char **args);
void arg_init(int argc, char *argv[], t_args *args);
void philo_init(t_args *args, t_philos *philos);
void thread_init(t_args *args, t_philos *philos);

//loop.c
void *loop(void *arg);

//checks.c
void thread_checker(t_args *args, t_philos *philos);
void clean_thread(t_args *args, t_philos *philos);

//main.c
int main(int argc, char *argv[]);

#endif