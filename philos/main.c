/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:49:52 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 20:49:53 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char *av[])
{
    mutex_t forks[MAX_PHILOS];
    t_philo philos[MAX_PHILOS];
    t_table table;

    if (ac != 5 && ac != 6)
        return (write(2, "Wrong argument count\n", 22),1);
    if (parse_input(philos, av) == 1)
        return (1);
    int i = 0;
    while(i < MAX_PHILOS)
    {
        INIT(&forks[i], NULL);
        i++;
    }
    simulation_start(&table, philos);
    initialized_fork(forks, ft_atoi(av[1]));
    initialized_philos(philos, &table, forks, av);
    create_threads(&table, forks);
    i = 0;
    while(i < MAX_PHILOS)
    {
        pthread_join(philos[i].thread_id, NULL);
        i++;
    }
    i = 0;

    while(i < MAX_PHILOS)
    {
        DESTROY(&forks[i]);
        i++;
    }
    cleanup(NULL, &table, forks);
    return (0);
}