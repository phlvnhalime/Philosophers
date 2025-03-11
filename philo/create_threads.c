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

void	print_status(t_state status, t_philo *philo, int id)
{
	long				time;
	char				buffer[50];
	int					len;
	static const char	*message[] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	LOCK(philo->dead_mutex);
	if (*philo->die)
	{
		UNLOCK(philo->dead_mutex);
		return ;
	}
	UNLOCK(philo->dead_mutex);
	time = get_time() - philo->start_time;
	LOCK(philo->write_mutex);
	len = ft_itoa(time, buffer);
	write(1, buffer, len);
	write(1, " ", 1);
	len = ft_itoa(id, buffer);
	write(1, buffer, len);
	write(1, " ", 1);
	write(1, message[status], ft_strlen(message[status]));
	write(1, "\n", 1);
	UNLOCK(philo->write_mutex);
}

void	handle_single_philos(t_philo *philos)
{
	eating(philos);
	LOCK(philos->dead_mutex);
	*philos->die = true;
	LOCK(philos->write_mutex);
	philos->table->end_of_simulation = true;
	UNLOCK(philos->write_mutex);
	UNLOCK(philos->dead_mutex);
	usleep(1000);
}

int	check_end_loop(t_philo *philo)
{
	LOCK(philo->dead_mutex);
	if (*philo->die == true)
	{
		UNLOCK(philo->dead_mutex);
		return (1);
	}
	UNLOCK(philo->dead_mutex);
	return (0);
}

void	*philosophers_routine(void *av)
{
	t_philo	*philos;

	philos = (t_philo *)av;
	if (philos->nbr_of_philos == 1)
	{
		handle_single_philos(philos);
		return (NULL);
	}
	if (philos->philo_id % 2 == 0)
		usleep(1000);
	while (check_end_loop(philos) == false)
	{
		if (check_end_loop(philos))
			break ;
		eating(philos);
		if (check_end_loop(philos))
			break ;
		sleeping(philos);
		if (check_end_loop(philos))
			break ;
		thinking(philos);
	}
	return (av);
}

int	create_threads(t_table *table, t_mutex *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &controller, table->philos) != 0)
		cleanup("Error: Simulation doesn't work", table, forks);
	i = 0;
	while (i < table->philos[0].nbr_of_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philosophers_routine, &table->philos[i]) != 0)
			cleanup("Error: Philos routine threads doesn't work.", table,
				forks);
		i++;
	}
	usleep(1000);
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		cleanup("Thread join error", table, forks);
	while (i < table->philos[0].nbr_of_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			cleanup("thread_id gave error", table, forks);
		i++;
	}
	return (0);
}
