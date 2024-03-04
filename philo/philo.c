/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:14:25 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/04 20:56:48 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_day(void *arg)
{
	t_philo	*philo_data;
	int		table_finish;

	philo_data = (t_philo *)arg;
	pthread_mutex_lock(&philo_data->table->gate);
	table_finish = philo_data->table->finished;
	pthread_mutex_unlock(&philo_data->table->gate);
	if (philo_data->index % 2)
		usleep(1000);
	while (1)
	{
		if (table_finish)
			break ;
		if (philo_think(philo_data))
			break ;
		if (philo_eat(philo_data) && check_eat_count(philo_data))
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
		pthread_mutex_init(&table->forks[i], NULL);
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
