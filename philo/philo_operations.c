/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:01:25 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/21 15:33:33 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philo_think(int philo_index)
{
    printf("philo %d is thinking\n", philo_index);
}

void philo_eat(int philo_index, int time_to_eat)
{
    printf("philo %d is eating\n", philo_index);
    usleep(time_to_eat);
}

void philo_sleep(int philo_index, int time_to_sleep)
{
    printf("philo %d is sleeping\n", philo_index);
    usleep(time_to_sleep);
}