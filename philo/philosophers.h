/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:36:33 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/14 16:52:06 by fenol64          ###   ########.fr       */
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

typedef struct s_philo
{
    int id;
    int is_dead;
    int is_eating;
    int is_sleeping;
    int is_thinking;
    struct s_philo *next_philo;
} t_philo;

typedef struct s_fork
{
    int id;
    int is_taken;
} t_fork;

typedef struct s_table
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int philo_must_eat;
} t_table;


#endif
