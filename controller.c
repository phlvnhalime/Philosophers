/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:18 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/25 12:15:19 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    end_of_died(t_table *table)//Masada herkesi öldür! :D
{
    int i;
    while(1)
    {
        pthread_mutex_lock(&table->state_mutex);
        if(table->end_of_simulation)
        {
            pthread_mutex_unlock(&table->state_mutex);
            break;
        }
        pthread_mutex_unlock(&table->state_mutex);
        i = 0;
        while(i < table->nbr_of_philos)
        {
            pthread_mutex_lock(&table->state_mutex);
            if(get_time() - table->philos[i].last_meal > table->time_to_die)
            {
                table->end_of_simulation = true;
                pthread_mutex_unlock(&table->state_mutex);
                philo_status(&table->philos[i], "died");
                return ; // or break. test it.
            }
            if(table->philos_must_eat != -1 && table->philos[i].meal_counter >= table->philos_must_eat)
            {
                table->philos[i].fill_full = true;
            }
            pthread_mutex_unlock(&table->state_mutex);
            i++;
        }
        if (table->philos_must_eat != -1)
        {
            i = 0;
            pthread_mutex_lock(&table->state_mutex);
            while(i < table->nbr_of_philos && table->philos[i].fill_full)
                i++;
            if(i == table->nbr_of_philos)
                table->end_of_simulation = true;
            pthread_mutex_unlock(&table->state_mutex);
        }
        usleep(1000);
    }
}
