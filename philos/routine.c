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

void    thinking(t_philo *philo)
{
    print_status(THINK, philo, philo->philo_id);
    check_sleep(philo->time_to_sleep);
}

void    sleeping(t_philo *philo)
{
    print_status(SLEEP, philo, philo->philo_id);
    check_sleep(philo->time_to_sleep);
}

void eating(t_philo *philo)
{
	LOCK(philo->right_fork);
	print_status(PICKUP_FORK, philo, philo->philo_id);
	if(philo->nbr_of_philos == 1)
	{
		check_sleep(philo->time_to_die);
		UNLOCK(philo->right_fork);
		return ;
	}
	LOCK(philo->left_fork);
	print_status(PICKUP_FORK, philo, philo->philo_id);
	philo->flag_eating = 1;
	print_status(EAT, philo, philo->philo_id);
	LOCK(philo->state_mutex);
	philo->last_meal = get_time();
	philo->meal_counter++;
	UNLOCK(philo->state_mutex);
	check_sleep(philo->time_to_eat);
	philo->flag_eating = 0;
	UNLOCK(philo->right_fork);
	UNLOCK(philo->left_fork);
}

