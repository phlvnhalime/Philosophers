/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:55:50 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 20:55:52 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    initialized_arguments(t_philo *philos, char *av[])
{
    philos->nbr_of_philos = ft_atoi(av[1]);
    philos->time_to_die = ft_atoi(av[2]);
    philos->time_to_eat = ft_atoi(av[3]);
    philos->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        philos->philos_must_eat = ft_atoi(av[5]);
    else
        philos->philos_must_eat = -1;
}

void initialized_philos(t_philo *philos, t_table *table, mutex_t *forks, char *av[])
{
	int	i;
    int n = ft_atoi(av[1]);

	i = -1;
	while (++i < n)
	{
		philos[i].philo_id = i + 1;
        philos[i].flag_eating = 0;
		philos[i].meal_counter = 0;
		philos[i].fill_full = false;
        initialized_arguments(&philos[i], av);
        philos[i].last_meal = get_time();
        philos[i].start_time = get_time();
        philos[i].write_mutex = &table->write_mutex;
        philos[i].state_mutex = &table->state_mutex;
        philos[i].dead_mutex = &table->dead_mutex;
        philos[i].die = &table->end_of_simulation;
		philos[i].right_fork = &forks[i];
        philos[i].left_fork = &forks[(i + 1) % n];
	}
}

void    initialized_fork(mutex_t *forks, int nbr_philos)
{
    int i;

    i = 0;
    while (i < nbr_philos)
    {
        INIT(&forks[i], NULL);
        i++;
    }
}


void    simulation_start(t_table *table, t_philo *philos)
{
    table->end_of_simulation = false;
    table->philos = philos;
    
    INIT(&table->write_mutex, NULL);
    INIT(&table->dead_mutex, NULL);
    INIT(&table->state_mutex, NULL);
}