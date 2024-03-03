/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:57:35 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/03 04:09:57 by fenol64          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_count(t_philo *philo)
{
	if (philo->table->philo_must_eat <= 0)
		return (1);
	if (philo->eat_count >= philo->table->philo_must_eat)
		return (0);
	return (1);
}

void	*philo_day(void *arg)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)arg;
	if (philo_data->index % 2)
		usleep(1000);
	while (1)
	{
		if (philo_data->table->finished)
			break ;
		if (philo_think(philo_data))
			break ;
		if (check_eat_count(philo_data) && philo_eat(philo_data))
			break ;
		if (philo_sleep(philo_data))
			break ;
	}
	return (NULL);
}

int	create_philo(int index, t_philo *philo, t_table *table)
{
	philo->index = index;
	philo->last_time_eat = table->start_time;
	philo->table = table;
	philo->eat_count = 0;
	if (pthread_create(&philo->thread, NULL, &philo_day, philo) != 0)
		return (0);
	return (1);
}

int	create_philos(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(table->num_philos * sizeof(t_philo));
	table->forks = (pthread_mutex_t *)malloc(table->num_philos
			* sizeof(pthread_mutex_t));
	table->gate = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	i = -1;
	while (++i < table->num_philos)
	{
		if (!create_philo(i, &table->philos[i], table))
			return (0);
	}
	i = -1;
	create_vigilant(table);
	while (++i < table->num_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
	}
	return (1);
}
