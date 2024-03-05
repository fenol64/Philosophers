/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:42:08 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/04 21:12:32 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->gate);
	if (philo->table->philo_must_eat <= 0)
	{
		pthread_mutex_unlock(&philo->table->gate);
		return (1);
	}
	if (philo->eat_count >= philo->table->philo_must_eat)
	{
		pthread_mutex_unlock(&philo->table->gate);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->gate);
	return (1);
}

int	check_philos_eat_count(t_philo *philos)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < philos->table->num_philos)
	{
		pthread_mutex_lock(&philos[i].table->gate);
		if (philos[i].eat_count >= philos[i].table->philo_must_eat)
		{
			ret++;
			if (ret >= philos[i].table->num_philos)
			{
				pthread_mutex_unlock(&philos[i].table->gate);
				return (1);
			}
		}
		pthread_mutex_unlock(&philos[i].table->gate);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_table *table)
{
	if (table->philo_must_eat > 0 && check_philos_eat_count(table->philos))
	{
		pthread_mutex_lock(&table->gate);
		table->finished = 1;
		return (1);
	}
	return (0);
}

void	*vigilant_day(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	while (1)
	{
		if (check_if_all_ate(table))
			break ;
		pthread_mutex_lock(&table->gate);
		if (get_current_time()
			- table->philos[i].last_time_eat > table->time_to_die)
		{
			if (!table->finished)
				printf("%ld %d died\n", get_formatted_time(table->start_time), i
					+ 1);
			table->finished = 1;
			break ;
		}
		i = (i + 1) % table->num_philos;
		pthread_mutex_unlock(&table->gate);
	}
	pthread_mutex_unlock(&table->gate);
	usleep(1000);
	return (NULL);
}

void	create_vigilant(t_table *table)
{
	if (pthread_create(&table->vigilant, NULL, &vigilant_day, table) != 0)
		printf("Error: pthread_create\n");
	if (pthread_join(table->vigilant, NULL) != 0)
		printf("Error: pthread_join\n");
}
