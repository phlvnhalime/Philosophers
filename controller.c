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
    long current_time;
    while(1)
    {
        i = 0;
        while(i < table->nbr_of_philos)
        {
            pthread_mutex_lock(&table->state_mutex);
            current_time = get_time();
            // printf("Check: %d starved for %ld ms \n", i+1, time_last_meal);
            if((current_time - table->philos[i].last_meal) > table->time_to_die)
            {
                // printf("Check: %d starved for %ld ms \n", i+1, current_time);
                table->end_of_simulation = true;
                philo_status(&table->philos[i], "died");
                pthread_mutex_unlock(&table->state_mutex);
                return ; // or break. test it.
            }
            pthread_mutex_unlock(&table->state_mutex);
            i++;
        }  
        /*
            add a funtion describe the status of time last_meal. 
        */
        if (table->philos_must_eat != -1)
        {
            i = 0;
            pthread_mutex_lock(&table->state_mutex);
            while(i < table->nbr_of_philos && table->philos[i].fill_full)
                i++;
            if(i == table->nbr_of_philos)
            {
                table->end_of_simulation = true;
                pthread_mutex_unlock(&table->state_mutex);
                //Add a message!
                return ;
            }
            pthread_mutex_unlock(&table->state_mutex);
        }
        usleep(50);
    }
}
