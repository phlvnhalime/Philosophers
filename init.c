/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:27 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/25 12:15:28 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void) // this function is like that
{
    struct timeval tv;// keep time as seconds and microseconds.
    gettimeofday(&tv, NULL); // current time saved to tv
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // 1 second = 1000 millisaniye
    // 1 micro second = 0.000001 second 1e6
}

void philo_status(t_philo *philo, const char *status) // Control it Think, sleep and eat 
{
    pthread_mutex_lock(&philo->table->log_mutex);
    if(!philo->table->end_of_simulation || ! ft_strcmp(status, "died")) // TODO strcmp
        printf("%ld %d %s \n",get_time()- philo->table->start_time, philo->philo_id, status);
    // Check the links for this connection! 
    // Add log_mutex! or create a function for mutex?
    //First i will start to add log_mutex
    pthread_mutex_unlock(&philo->table->log_mutex);
}


void    *philosophers_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    // t_table *table = philo->thread_id;

    // int left_fork = philo->philo_id - 1;
    // int right_fork = philo->philo_id % table->nbr_of_philos;


    while(!philo->table->end_of_simulation)
    {
        //philo_status(t_philo *philo, const char *status); TODO
        philo_status(philo, "is thinking");
        if (philo->philo_id % 2 == 0) // first philosophers start to eating with left fork
        {
            pthread_mutex_lock(&philo->right_fork.fork);
            philo_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->left_fork.fork);
            philo_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&philo->left_fork.fork);
            philo_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->right_fork.fork);
            philo_status(philo, "has taken a fork");
        }
        // add the last meal with given time!
        philo->last_meal = get_time();
        philo_status(philo, "is eating");
        //add usleep 
        usleep(philo->table->time_to_eat * 1000);
        philo->meal_counter++;
        //close the mutex!
        pthread_mutex_unlock(&philo->left_fork.fork);
        pthread_mutex_unlock(&philo->right_fork.fork);
        if(philo->table->philos_must_eat != -1 && philo->meal_counter >= philo->table->philos_must_eat)
            philo->fill_full = true;
        philo_status(philo, "is sleeping");
        // add usleep for time to sleep! 
        usleep(philo->table->time_to_sleep * 1000);
    }
    return NULL;
}

void    data_init(t_table *table)
{
    table->end_of_simulation = false;
    table->philos = memory_loop(sizeof(t_philo) * table->nbr_of_philos); // I'm gonna get an error for this part!
    table->forks = memory_loop(sizeof(t_fork) * table->nbr_of_philos);

    /*
        Start forks with mutex
    */
    int i = 0;
    while(i < table->nbr_of_philos)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
        i++;
    }

    /*
        Start philos:
    */
    i = 0;
    while(i < table->nbr_of_philos)
    {
        table->philos[i].philo_id = i + 1;
        table->philos[i].meal_counter = 0;
        table->philos[i].fill_full = false;
        /*
            assign all forks to philos,
            left_fork = table->forks[i];
            right_fork = table->forks[(i + 1) % table->nbr_of_philos]
        */
       table->philos[i].left_fork = table->forks[i];
       table-> philos[i].right_fork = table->forks[(i + 1) % table->nbr_of_philos];
       table->philos[i].table = table;
       i++; 
    }
}
