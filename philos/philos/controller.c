/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:17:49 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 22:17:50 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_die(t_philo *philo, long time_to_die)
{
	LOCK(philo->state_mutex);
	if ((get_time() - philo->last_meal) >= time_to_die && philo->flag_eating == 0)
		return (UNLOCK(philo->state_mutex), 1);
	UNLOCK(philo->state_mutex);
	return (0);
}

int	check_died(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nbr_of_philos)
	{
		if (time_to_die(&philos[i], philos[i].time_to_die))
		{
			print_status(DEAD, &philos[i], philos[i].philo_id);
			LOCK(philos->dead_mutex);
			*philos->die = true;
			UNLOCK(philos->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
int	check_fill_ful(t_philo *philo)
{
	int	i;
	int	full;

	i = -1;
	full = 0;
	if (philo[0].philos_must_eat == -1)
		return (0);
	while (++i < philo[0].nbr_of_philos)
	{
		LOCK(philo[i].state_mutex);
		if (philo[i].meal_counter >= philo[i].philos_must_eat)
			full++;
		UNLOCK(philo[i].state_mutex);
	}
	if (full == philo[0].nbr_of_philos)
	{
		write(1, "All philosophers have eaten enough\n", 36);
		LOCK(philo[0].dead_mutex);
        *philo->die = true;
		UNLOCK(philo[0].dead_mutex);
		return (1);
    }
	return (0);
}

void	*controller(void *av)
{
	t_philo *philos;

	philos = (t_philo *)av;
	if(philos[0].nbr_of_philos == 1)
		return (av);
	while (1)
	{
		// LOCK(philos->dead_mutex);
		if (check_died(philos) == 1 || check_fill_ful(philos) == 1)
		{
			// UNLOCK(philos->dead_mutex);
			break ;
		}
	}

	return (av);
}