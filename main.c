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
    - Each philosophers should be a thread.
    {
        How can i showed each philosophers as a thread in C?
        How many philosophers should be in ?
        {
            Global variables are forbidden!
            • Your(s) program(s) should take the following arguments:
            number_of_philosophers time_to_die time_to_eat time_to_sleep
            [number_of_times_each_philosopher_must_eat]
            ◦ number_of_philosophers: The number of philosophers and also the number
            of forks.
            ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
            milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
            ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
            During that time, they will need to hold two forks.
            ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
            ◦ number_of_times_each_philosopher_must_eat (optional argument): If all
            philosophers have eaten at least number_of_times_each_philosopher_must_eat
            times, the simulation stops. If not specified, the simulation stops when a
            philosopher dies.
            • Each philosopher has a number ranging from 1 to number_of_philosophers.
            • Philosopher number 1 sits next to philosopher number number_of_philosophers.
            Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
        }
    }
    About the logs of your program:
    {
        • Any state change of a philosopher must be formatted as follows:
        ◦ timestamp_in_ms X has taken a fork
        ◦ timestamp_in_ms X is eating
        ◦ timestamp_in_ms X is sleeping
        ◦ timestamp_in_ms X is thinking
        ◦ timestamp_in_ms X died
        Replace timestamp_in_ms with the current timestamp in milliseconds
        and X with the philosopher number.
        • A displayed state message should not be mixed up with another message.
        • A message announcing a philosopher died should be displayed no more than 10 ms
        after the actual death of the philosopher.
        • Again, philosophers should avoid dying!
    }
*/
/*
    *DATA_INITIALIZED    
        - int pthread_create(pthread_t *restrict thread, const pthread_attr_t, void*(*start_routine)(void *), void *restrict arg)
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
    free(table->forks);
    free(table->philos);
}

int main(int ac, char *av[])
{
    /*
        If the av is not 5 or 6  output should be wrong!
    */
    if(ac == 5 || ac == 6)
    {
        t_table table;
        //TODO List:
        //1. Parse_input (as a valid character)
        parse_input(&table, av);

        //2. Data_initialized 

        data_init(&table);
        table.start_time = get_time();

        if(table.nbr_of_philos == 0)
            exit_function("There is not any philosophers");
        int i = 0;
        while(i < table.nbr_of_philos)
        {
            table.philos[i].last_meal = table.start_time;
            pthread_create(&table.philos[i].thread_id, NULL, philosophers_routine, &table.philos[i]);
            i++;
        }
        // add the start time!
        // 3. start time table.start_time = get_time()
        // I have to add no philosophers rules // TODO
        
        // if the philosopher 1 person? what will happen? //TODO
        //4. controller
        end_of_died(&table);
        // printf("hey\n");
        i = 0;
        while(i < table.nbr_of_philos)
            pthread_join(table.philos[i].thread_id, NULL), i++;
        //5. Clean (Memory_leaks)
        clean(&table);
    }
    else
    {
        exit_function("Wrong arguments: <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosophers_must_eat]>");
    }
    return 0;
}
