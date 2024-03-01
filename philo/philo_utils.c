/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:42:08 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/29 19:30:40 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    exit_program(t_table *table)
{
    (void)table;
}

int check_philos_eat_count(t_philo *philos)
{
    int i;
    int ret;
    
    ret = 0;
    i = 0;
    while (i < philos[i].table->philo_must_eat)
    {
        if (philos[i].eat_count == philos[i].table->philo_must_eat)
            ret++;
        i++;
    }
    if (ret == philos[i].table->philo_must_eat)
        return (1);
    return (0);
}

void*   vigilant_day(void *arg)
{
    t_table *table;
    int i;
    long long time;
    
    table = (t_table *) arg;

    while (!table->finished)
    {
        i = -1;
        while (++i < table->num_philos)
        {
            time = get_current_time();
            if (check_philos_eat_count(table->philos) == 1 && table->philo_must_eat > 0)
                table->finished = 1;
            if (time - table->philos[i].last_time_eat > table->philos[i].table->time_to_die)
            {
                printf("%lld %d died\n", time - table->philos[i].table->start_time, i + 1);
                table->finished = 1;
                exit(1);
            }
        }
    }
    exit_program(table);
    return NULL;
}


void    create_vigilant(t_table *table)
{

    if (pthread_create(&table->vigilant, NULL, &vigilant_day, table) != 0)
    {
        printf("Error: pthread_create\n");
        exit_program(table);
    }
    if (pthread_join(table->vigilant, NULL) != 0)
    {
        printf("Error: pthread_join\n");
        exit_program(table);
    }
    
}
