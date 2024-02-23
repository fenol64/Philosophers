/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:57:35 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/23 16:51:20 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void*   philo_day(void *arg)
{
    t_philo *philo_data;
    int loop;

    philo_data = (t_philo *) arg;
    loop = 1;
    if (philo_data->philo_must_eat != 0)
        loop = 0;
    while(philo_data->philo_must_eat != 0 || loop)
    {
        is_dead(philo_data->index, philo_data->start_time, philo_data->time_to_die);
        philo_think(philo_data->index, philo_data->start_time);
        philo_eat(philo_data->index, philo_data->time_to_eat, philo_data->start_time);
        philo_sleep(philo_data->index, philo_data->time_to_sleep, philo_data->start_time);
        if (philo_data->philo_must_eat > 0 && loop != 1)
            philo_data->philo_must_eat--;
    }
    return NULL;
}

int create_philo(int index, pthread_t *philo, t_table *table)
{
    t_philo *philo_data;

    philo_data = malloc(sizeof(*philo_data));
    philo_data->index = index;
    philo_data->start_time = table->start_time;
    philo_data->time_to_die = table->time_to_die;
    philo_data->time_to_eat = table->time_to_eat;
    philo_data->time_to_sleep = table->time_to_sleep;
    philo_data->forks = table->forks;

    if (table->philo_must_eat)
        philo_data->philo_must_eat = table->philo_must_eat;

    if (pthread_create(philo, NULL, &philo_day, philo_data) != 0)
        return 0;
    return 1;
}

int create_philos(t_table *table)
{
    int i;

   table->philos = (pthread_t *) malloc(table->num_philos * sizeof(pthread_t));
   table->forks = (pthread_mutex_t *) malloc(table->num_philos * sizeof(pthread_mutex_t));
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

