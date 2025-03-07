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

void    print_status(t_state status, t_philo *philo, int id)
{
    long time;
    char buffer[50];
    int len;
    static const char *message[] = {
        "has taken a fork",
        "is eating",
        "is sleeping",
        "is thinking",
        "died"
    };

    LOCK(philo->write_mutex);
    time = get_time() - philo->start_time;
    if (check_end_loop(philo) == false)
    {
        // Convert time to string
        len = ft_itoa(time, buffer);
        write(1, buffer, len);
        write(1, " ", 1);
        
        // Convert id to string
        len = ft_itoa(id, buffer);
        write(1, buffer, len);
        write(1, " ", 1);
        
        // Write the message
        write(1, message[status], ft_strlen(message[status]));
        write(1, "\n", 1);
    }
    UNLOCK(philo->write_mutex);
}

int time_to_die(t_philo *philo, long time_to_die)
{
    LOCK(philo->state_mutex);
    if ((get_time()- philo->last_meal) >= time_to_die)
        return (UNLOCK(philo->state_mutex), 1);
    UNLOCK(philo->state_mutex);
    return (0);
}

int check_died(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].nbr_of_philos)
    {
        if (time_to_die(&philos[i], philos[i].time_to_die))
        {
            LOCK(philos[0].dead_mutex);
            print_status(DEAD, &philos[i], philos[i].philo_id);
            *philos->die = true;
            UNLOCK(philos[0].dead_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}
int check_fill_ful(t_philo *philo)
{
    int i;
    int full;

    i = -1;
    full = 0;
    if(philo[0].philos_must_eat == -1)
        return (0);
    while(++i < philo[0].nbr_of_philos)
    {
        LOCK(philo[i].state_mutex);
        if (philo[i].meal_counter >= philo[i].philos_must_eat)
            full++;
        UNLOCK(philo[i].state_mutex);
    }
    if (full == philo[0].nbr_of_philos)
    {
        LOCK(philo[0].dead_mutex);
        *philo->die = true;
        write(1, "All philosophers have eaten enough\n", 36);
        UNLOCK(philo[0].dead_mutex);
        return (1);
    }
    return (0);
}

void    *controller(void *av)
{
    t_philo *philos;

    philos = (t_philo *)av;
    while (1)
    {
        if (check_died(philos) == 1 || check_fill_ful(philos) == 1)
            break;
        usleep(1000);
    }
    return (av);
}