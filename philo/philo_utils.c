/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:42:08 by fnascime          #+#    #+#             */
/*   Updated: 2024/02/23 16:54:45 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    is_dead(int philo_index, long long start, int time_to_die)
{
    long long time;

    time = get_current_time();
    if (time - start > time_to_die)
    {
        printf("%lld %d died\n", time - start, philo_index + 1);
        exit(1);
    }
}
