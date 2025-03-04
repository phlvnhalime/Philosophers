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

void	must_eat(t_table *table)
{
	int	i;

	i = 0;
	if (table->philos_must_eat != -1)
	{
		pthread_mutex_lock(&table->state_mutex);
		while (i < table->nbr_of_philos && table->philos[i].fill_full)
			i++;
		if (i == table->nbr_of_philos)
		{
			table->end_of_simulation = true;
			printf("%ld All philosophers have eaten enough\n", get_time(0)
				- table->start_time);
			pthread_mutex_unlock(&table->state_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
}

void	time_to_die(t_table *table, long current_time)
{
	int	i;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		pthread_mutex_lock(&table->state_mutex);
		current_time = get_time(table->start_time);
		if ((current_time - table->philos[i].last_meal) > table->time_to_die)
		{
			table->end_of_simulation = true;
			philo_status(&table->philos[i], "died");
			pthread_mutex_unlock(&table->state_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->state_mutex);
		i++;
	}
}

void	end_of_died(t_table *table)
{
	long	current_time;

	current_time = 0;
	while (1)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->end_of_simulation)
		{
			pthread_mutex_unlock(&table->state_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->state_mutex);
		time_to_die(table, current_time);
		must_eat(table);
		usleep(1000);
	}
}
