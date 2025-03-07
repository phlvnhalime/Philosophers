/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:47:32 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 21:47:34 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup(char *str, t_table *table, mutex_t *forks)
{
    int i;

    
    // Print cleanup message if provided
    if (str)
    {
        write(2, str, ft_strlen(str));
		write(2, "\n", 1);
    }

    // Destroy all mutexes
    DESTROY(&table->write_mutex);
    DESTROY(&table->state_mutex);
    DESTROY(&table->dead_mutex);
    i = 0;
    while (i < table->philos[0].nbr_of_philos)
    {
        DESTROY(&forks[i]);
        i++;
    }
    
}
