/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:57:35 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/28 19:42:21 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void*   philo_day(void *arg)
{
    t_philo *philo_data;

    philo_data = (t_philo *) arg;

    while(!philo_data->table->finished)
    {
        philo_eat(philo_data);
        philo_think(philo_data);
        philo_sleep(philo_data);   
    }
    philo_data->table->finished = 1;
    return NULL;
}

int create_philo(int index, t_philo *philo, t_table *table)
{
    philo->index = index;
    philo->last_time_eat = table->start_time;
    philo->table = table;
    philo->eat_count = 0;

    if (pthread_create(&philo->thread, NULL, &philo_day, philo) != 0)
        return 0;
    return 1;
}

int create_philos(t_table *table)
{
    int i;

   table->philos = (t_philo *) malloc(table->num_philos * sizeof(t_philo));
   table->forks = (pthread_mutex_t *) malloc(table->num_philos * sizeof(pthread_mutex_t));
   table->gate = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    i = -1;
    while (++i < table->num_philos)
    {
        if(!create_philo(i, &table->philos[i], table))
            return (0);
    }
    i = -1;
    create_vigilant(table);
    while (++i < table->num_philos)
    {
        if (pthread_join(table->philos[i].thread, NULL) != 0)
            return (0);
    }
    return (1);
}

