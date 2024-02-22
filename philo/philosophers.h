/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:36:33 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/21 14:14:38 by fnascime         ###   ########.fr       */
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

typedef struct s_table
{
    int num_philos;
    pthread_t *philos;
    pthread_mutex_t *mutexes;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
} t_table;

typedef struct s_philo
{
    int index;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
    pthread_mutex_t mutex;
} t_philo;

int create_philos(t_table *table);

// philo operations
void philo_think(int philo_index);
void philo_eat(int philo_index, int time_to_eat);
void philo_sleep(int philo_index, int time_to_sleep);

// utils
int ft_atoi(char *str);



#endif
