/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:05:27 by yulpark           #+#    #+#             */
/*   Updated: 2025/05/09 17:46:29 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philo.h"

//int	main(int argc, char *argv[])
//{
//	if (init_input(argc, argv) != SUCCESS)
//		return (1);
//	else
//	{
//		;
//	}
//	return (0);
//}

#include <pthread.h>
#include <stdio.h>

void* foo(int *i) {
	(*i)++;
	printf("MUFA\n");
 }
int main() {

    // Create a pthread_t variable to store
    // thread ID
	pthread_t threads[10000];
	int i = 0;
    // Creating a new thread.
	int j = 0;
	while (j < 10000)
	{
		pthread_create(&threads[j], NULL, foo, &i);
		j++;
	}
	j = 0;
	while (j < 10000)
	{
		pthread_join(threads[j], NULL);
		j++;
	}
    return 0;
}
