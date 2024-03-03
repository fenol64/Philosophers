/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:12:46 by fnascime          #+#    #+#             */
/*   Updated: 2024/03/03 04:40:18 by fenol64          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int c, char **v)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (c < 5 || c > 6)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	table.start_time = get_current_time();
	table.num_philos = ft_atoi(v[1]);
	table.time_to_die = ft_atoi(v[2]);
	table.time_to_eat = ft_atoi(v[3]);
	table.time_to_sleep = ft_atoi(v[4]);
	if (v[5])
		table.philo_must_eat = ft_atoi(v[5]);
	create_philos(&table);
	free(table.philos);
	free_forks(table.forks, table.num_philos);
	return (0);
}
