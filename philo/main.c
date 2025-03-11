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

void	return_loop(t_table table)
{
	while (1)
	{
		LOCK(&table.write_mutex);
		if (table.end_of_simulation == true)
		{
			UNLOCK(&table.write_mutex);
			break ;
		}
		UNLOCK(&table.write_mutex);
		usleep(1000);
	}
}

int	main(int ac, char *av[])
{
	t_mutex	forks[MAX_PHILOS];
	t_philo	philos[MAX_PHILOS];
	t_table	table;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (parse_input(philos, av) == 1)
		return (1);
	initialized_philos(philos, &table, forks, av);
	initialized_fork(forks, ft_atoi(av[1]));
	simulation_start(&table, philos);
	if (create_threads(&table, forks) != 0)
		return (cleanup("Error: Thread creation or joining", &table, forks), 1);
	return_loop(table);
	cleanup(NULL, &table, forks);
	return (0);
}
