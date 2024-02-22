/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:57:35 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/21 16:32:51 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void*   philo_day(void *arg)
{
    t_philo *philo_data;
    philo_data = (t_philo *) arg;

    while(philo_data->philo_must_eat != 0)
    {
        philo_think(philo_data->index);
        pthread_mutex_lock(&philo_data->mutex);
        philo_eat(philo_data->index, philo_data->time_to_eat);
        pthread_mutex_unlock(&philo_data->mutex);
        philo_sleep(philo_data->index, philo_data->time_to_sleep);
        if (philo_data->philo_must_eat > 0)
            philo_data->philo_must_eat--;
    }
    return NULL;
}

int create_philo(int index, pthread_t *philo, t_table *table)
{
    t_philo *philo_data;

    philo_data = malloc(sizeof(*philo_data));
    philo_data->index = index;
    philo_data->time_to_die = table->time_to_die;
    philo_data->time_to_eat = table->time_to_eat;
    philo_data->time_to_sleep = table->time_to_sleep;
    philo_data->fork = table->mutexes[index];
    philo_data->forks = table->mutexes;
    pthread_mutex_init(&philo_data->mutex, NULL);
    if (table->philo_must_eat)
        philo_data->philo_must_eat = table->philo_must_eat;

    if (pthread_create(philo, NULL, &philo_day, philo_data) != 0)
        return 0;
   // pthread_mutex_unlock(&table->mutexes[index]);
    return 1;
}

int create_philos(t_table *table)
{
    int i;

   table->philos = (pthread_t *) malloc(table->num_philos * sizeof(pthread_t));
   table->mutexes = (pthread_mutex_t *) malloc(table->num_philos * sizeof(pthread_mutex_t));
    i = -1;
    while (++i < table->num_philos)
    {
        if(!create_philo(i, &table->philos[i], table))
            return (0);
    }
    i = -1;
    while (++i < table->num_philos)
    {
        if (pthread_join(table->philos[i], NULL) != 0)
            return (0);
    }
   free(table->philos);
    return (1);
}

