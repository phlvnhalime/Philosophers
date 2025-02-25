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
    while(!table->end_of_simulation)
    {
        i = 0;
        while(i < table->nbr_of_philos)
        {
            if(get_time() - table->philos[i].last_meal > table->time_to_die)
            {
                table->end_of_simulation = true;
                philo_status(&table->philos[i], "died");
                return ; // or break. test it.
            }
            if(table->philos_must_eat != -1 && table->philos[i].meal_counter >= table->philos_must_eat)
            {
                table->philos[i].fill_full = true;
            }
            i++;
        }
        if (table->philos_must_eat != -1)
        {
            i = 0;
            while(i < table->philos_must_eat && table->philos[i].fill_full)
                i++;
            if(i == table->nbr_of_philos)
                table->end_of_simulation = true;
        }
        usleep(1000);
    }
}
