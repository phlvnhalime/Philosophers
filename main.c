/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:13:08 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:10 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Current Problem:
    1. The simulation should stop when a philosopher dies.
    2. Deadlock and syncranization problems.
    3. Missing died message.
    4. The time is not correct.
*/

void    clean(t_table *table)// destroy it all mutex
{
    int i = 0;
    while(i < table->nbr_of_philos)
    {
        pthread_mutex_destroy(&table->forks[i].fork);
        i++;
    }
    pthread_mutex_destroy(&table->log_mutex);
    pthread_mutex_destroy(&table->state_mutex);
    free(table->forks);
    free(table->philos);
}

int main(int ac, char *av[])
{
    /*
        If the av is not 5 or 6  output should be wrong!
    */
    if(ac != 5 && ac != 6)
        exit_function("Wrong arguments: <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosophers_must_eat]>");
    t_table table;
    //TODO List:
    //1. Parse_input (as a valid character)
    parse_input(&table, av);
    table.start_time = get_time();
    data_init(&table);

    // if(table.nbr_of_philos == 0)
    //     exit_function("Number of philos must be positive\n");
    

    /*
        CAUTION: If the number of philosophers is 0, the program should be terminated.
        and if the number of philosophers is 1, the program should be terminated.
    */
    if(table.nbr_of_philos == 1)
    {
        pthread_create(&table.philos[0].thread_id , NULL, philosophers_routine, &table.philos[0]);
        pthread_join(table.philos[0].thread_id, NULL);
        // usleep(table.time_to_die * 1000);
        // printf("%ld is died\n", table.time_to_die);
        clean(&table);
        return 0;
        // Check the clean function!
    }

    // int i = 0;
    // while(1< table.nbr_of_philos)
    // {
    //     table.philos[i].last_meal = table.start_time;
    //     i++;
    // }
    
    int i = 0;
    while(i < table.nbr_of_philos)
    {
        table.philos[i].last_meal = table.start_time;
        if(pthread_create(&table.philos[i].thread_id, NULL, philosophers_routine, &table.philos[i]) != 0)
        {
            clean(&table);
            exit_function("Thread faild\n");
        }
        i++;
    }

    end_of_died(&table);
    // printf("hey\n");
    i = 0;
    while(i < table.nbr_of_philos)
    {
        pthread_join(table.philos[i].thread_id, NULL);
        i++;
    }
    clean(&table);

    return 0;
}
