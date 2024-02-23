/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:36:33 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/23 16:49:24 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef struct s_table
{
    long long    start_time;
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
    pthread_t *philos;
    pthread_mutex_t *forks;
} t_table;

typedef struct s_philo
{
    int index;
    long long    start_time;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
    pthread_mutex_t *forks;
} t_philo;

int create_philos(t_table *table);

// philo operations
void philo_think(int philo_index, long long start);
void philo_eat(int philo_index, int time_to_eat, long long start);
void philo_sleep(int philo_index, int time_to_sleep, long long start);
void    is_dead(int philo_index, long long start, int time_to_die);

// utils
long long get_current_time();
int ft_atoi(char *str);
void mspleep(long long time);



#endif
