/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:01:25 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/22 21:44:24 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void get_fork(int philo_index, long long start)
{
    printf("%lld philo %d took the fork\n", get_current_time() - start, philo_index + 1);
}

void philo_think(int philo_index, long long start)
{
    printf("%lld philo %d is thinking\n", get_current_time() - start, philo_index + 1);
}

void philo_eat(int philo_index, int time_to_eat, long long start)
{
    printf("%lld philo %d is eating\n", get_current_time() - start, philo_index + 1);
    mspleep(time_to_eat);
}

void philo_sleep(int philo_index, int time_to_sleep, long long start)
{
    printf("%lld philo %d is sleeping\n", get_current_time() - start, philo_index + 1);
    mspleep(time_to_sleep);
}

void philo_died(int philo_index, long long start)
{
    printf("%lld philo %d died\n", get_current_time() - start, philo_index + 1);
}