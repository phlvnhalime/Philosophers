/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:27 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/25 12:15:28 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_of_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_of_philos)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].meal_counter = 0;
		table->philos[i].fill_full = false;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->nbr_of_philos];
		table->philos[i].table = table;
	}
}

void	data_init(t_table *table)
{
	table->end_of_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->nbr_of_philos);
	table->forks = malloc(sizeof(t_fork) * table->nbr_of_philos);
	if (!table->philos || !table->forks)
		exit_function("Memory allocation failed!");
	init_forks(table);
	usleep(10);
	init_philos(table);
	pthread_mutex_init(&table->state_mutex, NULL);
	pthread_mutex_init(&table->log_mutex, NULL);
}
