/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:01:25 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/04 19:11:46 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_think(t_philo *philo)
{
	int	table_finish;

	table_finish = 0;
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d is thinking\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	table_finish = philo->table->finished;
	pthread_mutex_unlock(&philo->table->gate);
	return (table_finish);
}

int	philo_eat(t_philo *philo)
{
	int	table_finish;
	int	forks[2];

	table_finish = 0;
	if (!get_forks(philo, forks))
		return (table_finish);
	pthread_mutex_lock(&philo->table->gate);
	philo->last_time_eat = get_current_time();
	if (!philo->table->finished)
		printf("%ld %d is eating\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	philo->eat_count++;
	table_finish = philo->table->finished;
	pthread_mutex_unlock(&philo->table->gate);
	mspleep(philo->table->time_to_eat);
	release_forks(forks[0], forks[1], philo);
	return (table_finish);
}

int	philo_sleep(t_philo *philo)
{
	int	table_finish;

	table_finish = 0;
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d is sleeping\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	table_finish = philo->table->finished;
	pthread_mutex_unlock(&philo->table->gate);
	mspleep(philo->table->time_to_sleep);
	return (table_finish);
}
