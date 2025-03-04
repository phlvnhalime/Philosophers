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

void	clean(t_table *table) // destroy it all mutex
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->state_mutex);
	free(table->forks);
	free(table->philos);
}

void	create_threads(t_table table)
{
	int	i;

	if (table.nbr_of_philos == 1)
	{
		if (pthread_create(&table.philos[0].thread_id, NULL,
				philosophers_routine, &table.philos[0]))
		{
			clean(&table);
			exit_function("Thread faild\n");
		}
		pthread_join(table.philos[0].thread_id, NULL);
		clean(&table);
		return ;
	}
	i = -1;
	while (++i < table.nbr_of_philos)
	{
		table.philos[i].last_meal = table.start_time;
		if (pthread_create(&table.philos[i].thread_id, NULL,
				philosophers_routine, &table.philos[i]) != 0)
		{
			clean(&table);
			exit_function("Thread faild\n");
		}
	}
}

int	main(int ac, char *av[])
{
	int		i;
	t_table	table;

	if (ac != 5 && ac != 6)
		exit_function("Wrong arguments!");
	parse_input(&table, av);
	table.start_time = get_time(0);
	data_init(&table);
	create_threads(table);
	end_of_died(&table);
	i = 0;
	while (i < table.nbr_of_philos)
	{
		pthread_join(table.philos[i].thread_id, NULL);
		i++;
	}
	clean(&table);
	return (0);
}
