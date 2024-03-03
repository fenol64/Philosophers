/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:25:11 by fenol64           #+#    #+#             */
/*   Updated: 2024/03/03 03:43:07 by fenol64          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_first_fork(t_philo *philo)
{
	int	first_fork;

	first_fork = philo->index;
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d has taken a fork\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	pthread_mutex_unlock(&philo->table->gate);
	return (first_fork);
}

int	get_second_fork(t_philo *philo)
{
	int	second_fork;

	second_fork = (philo->index + 1) % philo->table->num_philos;
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	pthread_mutex_lock(&philo->table->gate);
	if (!philo->table->finished)
		printf("%ld %d has taken a fork\n",
			get_formatted_time(philo->table->start_time), philo->index + 1);
	pthread_mutex_unlock(&philo->table->gate);
	return (second_fork);
}

void	free_forks(pthread_mutex_t *forks, int num_philos)
{
	int i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}