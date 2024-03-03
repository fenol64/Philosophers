/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:01:25 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/03 03:00:10 by fenol64          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d is thinking\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	pthread_mutex_unlock(&philo->table->gate);
	return (philo->table->finished);
}

int	philo_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = get_first_fork(philo);
	if (philo->table->num_philos == 1)
	{
		mspleep(philo->table->time_to_die);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		return (1);
	}
	second_fork = get_second_fork(philo);
	pthread_mutex_lock(&philo->table->gate);
	philo->last_time_eat = get_current_time();
	if (!philo->table->finished)
		printf("%ld %d is eating\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	pthread_mutex_unlock(&philo->table->gate);
	mspleep(philo->table->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
	return (philo->table->finished);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d is sleeping\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	pthread_mutex_unlock(&philo->table->gate);
	mspleep(philo->table->time_to_sleep);
	return (philo->table->finished);
}
