/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:47:32 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 21:47:34 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(char *str, t_table *table, mutex_t *forks)
{
	int	i;
	
	LOCK(&table->dead_mutex);
	if(table->philos->die)
	{
		UNLOCK(&table->dead_mutex);
		return;
	}
	UNLOCK(&table->dead_mutex);
	i = 0;
	while(i < table->philos[0].nbr_of_philos)
	{
		if(pthread_join(table->philos[i].thread_id, NULL) == 0)
			write(2,"ERROR: Join thread\n", 19);
		i++;
	}


	i = 0;
	while (i < table->philos[0].nbr_of_philos)
	{
		if(DESTROY(&forks[i]) != 0)
			write(2, "Error destroying fork mutex\n", 28);
		i++;
	}
	if(DESTROY(&table->write_mutex) != 0)
		write(2, "Error destroying fork mutex\n", 28);
	if(DESTROY(&table->state_mutex) != 0)
		write(2, "Error destroying fork mutex\n", 28);
	if(DESTROY(&table->dead_mutex) != 0)
		write(2, "Error destroying fork mutex\n", 28);
		if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
}
