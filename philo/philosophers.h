/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:36:33 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/29 21:43:16 by fnascime         ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct s_philo
{
    int index;
    long long    last_time_eat;
    int eat_count;
    t_table *table;
    pthread_t thread;
} t_philo;


typedef struct s_table
{
    long long    start_time;
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
    pthread_mutex_t gate;
    int finished;
    pthread_t vigilant;
    t_philo *philos;
    pthread_mutex_t *forks;
} t_table;

int create_philos(t_table *table);

// philo operations
void    philo_think(t_philo *philo_data);
void    philo_eat(t_philo *philo_data);
void    philo_sleep(t_philo *philo_data);
void    get_forks(t_philo *philo_data);
void    create_vigilant(t_table *table);


// utils
long long get_current_time();
int ft_atoi(char *str);
void mspleep(long long time);



#endif
