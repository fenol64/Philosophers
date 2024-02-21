/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:57:35 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/21 10:37:26 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t message = PTHREAD_MUTEX_INITIALIZER;

void*   philo_day(void *arg)
{
    t_philo *philo_data;
    philo_data = (t_philo *) arg;
   // (void) philo_data;
    pthread_mutex_lock(&message);
    printf("hello from tread %d %p %p\n", philo_data->index, arg, philo_data);
    pthread_mutex_unlock(&message);
  // char c = philo_data->index + '0';
    //printf("%c:\n", c);
    return NULL;
}

int create_philo(int index, pthread_t *philo, t_table *table)
{
    t_philo *philo_data = malloc(sizeof(*philo_data));

   //pthread_mutex_lock(&table->mutexes[index]);
    philo_data->index = index;
    philo_data->time_to_die = table->time_to_die;
    philo_data->time_to_eat = table->time_to_eat;
    philo_data->time_to_sleep = table->time_to_sleep;
   // philo_data.mutex = table->mutexes[index];
   // pthread_mutex_init(&philo_data.mutex, NULL);
    
    if (pthread_create(philo, NULL, &philo_day, philo_data) != 0)
        return 0;
   // pthread_mutex_unlock(&table->mutexes[index]);
    return 1;
}

int create_philos(t_table *table)
{
    int i;
    
    table->philos = (pthread_t *) malloc(table->num_philos * sizeof(pthread_t));
   // table->mutexes = (pthread_mutex_t *) malloc(table->num_philos * sizeof(pthread_mutex_t));
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
        //printf("thread %d cabo\n", i);
    }
   free(table->philos);
   // while (++i < table->num_philos)
   //     pthread_mutex_destroy(&table->mutexes[i]);
  //  free(table->mutexes);
    return (1);
}

