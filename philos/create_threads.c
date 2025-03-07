/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:26:27 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 21:26:29 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_end_loop(t_philo *philo)
{
    LOCK(philo->dead_mutex);
    if (*philo->die == true)
        return (UNLOCK(philo->dead_mutex), 1);
    UNLOCK(philo->dead_mutex);
    return (0);
}

void    *philosophers_routine(void *av)
{
    t_philo *philos;

    philos = (t_philo *)av;
    if(philos->philo_id % 2 == 0)
        usleep(1000);
    while (!check_end_loop(philos))
    {
        eating(philos);
        sleeping(philos);
        thinking(philos);
    }
    return (av);
}

int create_threads(t_table *table, mutex_t *forks)
{
    pthread_t monitor;
    int i ;

    if (pthread_create(&monitor, NULL, &controller, table->philos) != 0)
        cleanup("Error: Simulation doesn't work", table, forks);
    i = 0;
    while (i < table->philos[0].nbr_of_philos)
    {
        if (pthread_create(&table->philos[i].thread_id, NULL, 
                          philosophers_routine, &table->philos[i]) != 0)
            cleanup("Error: Philos routine threads doesn't work.", table, forks);
        i++;
    }
    i = 0;
    if(pthread_join(monitor, NULL) != 0)
        cleanup("Thread join error", table, forks);
    while(i < table->philos[0].nbr_of_philos)
    {
        if(pthread_join(table->philos[i].thread_id, NULL) != 0)
            cleanup("thread_id gave error", table, forks);
        i++;
    }
    return (0);
}
