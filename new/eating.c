/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_times.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:38:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/03 03:38:09 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		philo_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		philo_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork);
	}
	philo_status(philo, "has taken a fork");
}

void	time_to_eat(t_philo *philo)
{
	pick_up(philo);
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal = get_time(philo->table->start_time);
	philo->meal_counter++;
	if (philo->table->philos_must_eat != -1
		&& philo->meal_counter >= philo->table->philos_must_eat)
		philo->fill_full = true;
	pthread_mutex_unlock(&philo->table->state_mutex);
	philo_status(philo, "is eating");
	check_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}
