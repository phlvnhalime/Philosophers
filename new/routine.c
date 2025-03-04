/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 06:12:20 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/03 06:12:21 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long start_time)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start_time == 0)
		return (current_time);
	return (current_time - start_time);
}

void	philo_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->table->log_mutex);
	if (!philo->table->end_of_simulation || ft_strcmp(status, "died") == 0)
	{
		printf("%ld %d %s\n", get_time(philo->table->start_time),
			philo->philo_id, status);
	}
	pthread_mutex_unlock(&philo->table->log_mutex);
}

bool	check_simulation(t_philo *philo)
{
	bool	dont_pause;

	pthread_mutex_lock(&philo->table->state_mutex);
	dont_pause = !philo->table->end_of_simulation;
	pthread_mutex_unlock(&philo->table->state_mutex);
	return (dont_pause);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nbr_of_philos == 1)
	{
		philo_status(philo, "has taken a fork");
		check_sleep(philo->table->time_to_die);
		philo_status(philo, "died");
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(1500);
	while (check_simulation(philo))
	{
		time_to_eat(philo);
		philo_status(philo, "is sleeping");
		check_sleep(philo->table->time_to_sleep);
		philo_status(philo, "is thinking");
		check_sleep((philo->table->time_to_die - (philo->table->time_to_eat
					+ philo->table->time_to_sleep)) / 2);
	}
	return (NULL);
}
