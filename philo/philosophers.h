/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fenol64 <fenol64@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:02:17 by fenol64           #+#    #+#             */
/*   Updated: 2024/03/03 04:50:26 by fenol64          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					index;
	time_t				last_time_eat;
	int					eat_count;
	t_table				*table;
	pthread_t			thread;
}						t_philo;

typedef struct s_table
{
	time_t				start_time;
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_must_eat;
	int					finished_eating;
	pthread_mutex_t		gate;
	int					finished;
	pthread_t			vigilant;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_table;

int						create_philos(t_table *table);

// philo operations
int						philo_think(t_philo *philo_data);
int						philo_eat(t_philo *philo_data);
int						philo_sleep(t_philo *philo_data);
void					create_vigilant(t_table *table);

// philo forks
int						get_first_fork(t_philo *philo);
int						get_second_fork(t_philo *philo);
void					free_forks(pthread_mutex_t *forks, int num_philos);

// time utils
time_t					get_current_time(void);
time_t					get_formatted_time(time_t start_time);
void					mspleep(time_t time);

// utils
int						check_eat_count(t_philo *philo);
int						ft_atoi(char *str);

#endif