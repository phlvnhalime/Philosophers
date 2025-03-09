/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:56:11 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 21:56:12 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	if(check_end_loop(philo) == 1)
		return;
	print_status(THINK, philo, philo->philo_id);
	check_sleep(((philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep)) / philo->nbr_of_philos));
}

void	sleeping(t_philo *philo)
{
	if(check_end_loop(philo) == 1)
		return;
	print_status(SLEEP, philo, philo->philo_id);
	check_sleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	if(check_end_loop(philo) == 1)
		return;
	mutex_t *first_fork;
	mutex_t *second_fork;

	if(philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	LOCK(first_fork);
	print_status(PICKUP_FORK, philo, philo->philo_id);
	if (philo->nbr_of_philos == 1)
	{
		check_sleep(philo->time_to_die);
		print_status(DEAD, philo, philo->philo_id);
		UNLOCK(first_fork);
		usleep(1000);
		return ;
	}
	LOCK(second_fork);
	print_status(PICKUP_FORK, philo, philo->philo_id);
	LOCK(philo->state_mutex);
	philo->flag_eating = 1;
	philo->last_meal = get_time();
	philo->meal_counter++;
	print_status(EAT, philo, philo->philo_id);
	philo->flag_eating = 0;
	UNLOCK(philo->state_mutex);
	check_sleep(philo->time_to_eat);

	UNLOCK(first_fork);
	UNLOCK(second_fork);
}
