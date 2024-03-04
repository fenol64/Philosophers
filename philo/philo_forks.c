/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:25:11 by fenol64           #+#    #+#             */
/*   Updated: 2024/03/04 19:12:35 by fnascime         ###   ########.fr       */
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

int	get_forks(t_philo *philo, int *forks_pointer)
{
	if (philo->table->num_philos == 1)
	{
		mspleep(philo->table->time_to_die);
		return (0);
	}
	if ((philo->index + 1) == philo->table->num_philos)
	{
		forks_pointer[0] = get_second_fork(philo);
		forks_pointer[1] = get_first_fork(philo);
	}
	else
	{
		forks_pointer[0] = get_first_fork(philo);
		forks_pointer[1] = get_second_fork(philo);
	}
	return (1);
}

int	release_forks(int first_fork, int second_fork, t_philo *philo)
{
	if ((philo->index + 1) == philo->table->num_philos)
	{
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks[first_fork]);
		pthread_mutex_unlock(&philo->table->forks[second_fork]);
	}
	return (1);
}

void	free_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
