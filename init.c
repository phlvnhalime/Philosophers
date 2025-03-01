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

void check_sleep(long durasion_ms)
{
    usleep(durasion_ms * 1000);
}

long    get_time(void) // this function is like that
{
    struct timeval tv;// keep time as seconds and microseconds.
    gettimeofday(&tv, NULL); // current time saved to tv
    return ((long long)tv.tv_sec * 1e3 + tv.tv_usec / 1e3); // 1 second = 1000 millisaniye
    // 1 micro second = 0.000001 second 1e6
}

void philo_status(t_philo *philo, const char *status) // Control it Think, sleep and eat 
{

    pthread_mutex_lock(&philo->table->log_mutex);

    // pthread_mutex_lock(&philo->table->state_mutex);
    bool out_print = !philo->table->end_of_simulation || (strcmp(status, "died") == 0);
    // pthread_mutex_unlock(&philo->table->state_mutex);

    if(out_print)
    {
        // long timestamp = get_time() - philo->table->start_time;
        printf("%ld %d %s\n", get_time() - philo->table->start_time, philo->philo_id, status);
    }
    pthread_mutex_unlock(&philo->table->log_mutex);
}


void    *philosophers_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    /*
        For 1 philosopher!!
    */
    if(philo->table->nbr_of_philos == 1)
    {
        philo_status(philo, "has taken a fork");
        // usleep(philo->table->time_to_die );
        check_sleep(philo->table->time_to_die);
        philo_status(philo, "died");
        return NULL;
    }

    // 200ms gecikme eklersek;
    if(philo->philo_id % 2)
        usleep(150);
    
    while(1)
    {

        if (philo->philo_id % 2 == 0) // first philosophers start to eating with left fork
        {
            pthread_mutex_lock(&philo->right_fork->fork);
            philo_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->left_fork->fork);
            philo_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&philo->left_fork->fork);
            philo_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->right_fork->fork);
            philo_status(philo, "has taken a fork");
        }

        /*
            Condition start from here. Check simutalion state before eating!!
        */
        pthread_mutex_lock(&philo->table->state_mutex);
        if( philo->table->end_of_simulation)
        {
            pthread_mutex_unlock(&philo->right_fork->fork);
            pthread_mutex_unlock(&philo->left_fork->fork);
            pthread_mutex_unlock(&philo->table->state_mutex);
            return NULL;
        }
        // add the last meal with given time!
        
        philo->last_meal = get_time();
        // pthread_mutex_unlock(&philo->table->state_mutex);
        // pthread_mutex_lock(&philo->table->state_mutex);
         philo->meal_counter++;
        if(philo->table->philos_must_eat != -1 && philo->meal_counter >= philo->table->philos_must_eat)
            philo->fill_full = true;
        pthread_mutex_unlock(&philo->table->state_mutex);

        philo_status(philo, "is eating");
        usleep(philo->table->time_to_eat * 1000);
        printf(GRN"%ld\n"RST, get_time());


        pthread_mutex_unlock(&philo->right_fork->fork);
        pthread_mutex_unlock(&philo->left_fork->fork);
        

        /*
            Time to sleep is start in here!!
        */
        philo_status(philo, "is sleeping");
        usleep(philo->table->time_to_sleep * 1000);
        printf(GRN"%ld\n"RST, get_time());

        pthread_mutex_lock(&philo->table->state_mutex);
        if(philo->table->end_of_simulation)
        {
            pthread_mutex_unlock(&philo->table->state_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philo->table->state_mutex);

        /*
            Time to think!!
        */
        philo_status(philo, "is thinking");
        long think_time = ((philo->table->time_to_die -(philo->table->time_to_eat + philo->table->time_to_sleep)) * 1e3);
        printf(GRN"%ld\n"RST, get_time());
        usleep(150000);
    }

    return NULL;
}

void    data_init(t_table *table)
{
    table->end_of_simulation = false;
    table->philos = memory_loop(sizeof(t_philo) * table->nbr_of_philos); // I'm gonna get an error for this part!
    table->forks = memory_loop(sizeof(t_fork) * table->nbr_of_philos);
    
    int i = 0;
    while(i < table->nbr_of_philos)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
        i++;
    }

    i = 0;
    while(i < table->nbr_of_philos)
    {
        table->philos[i].philo_id = i + 1;
        table->philos[i].meal_counter = 0;
        table->philos[i].fill_full = false;
        table->philos[i].left_fork = &table->forks[i];
        table-> philos[i].right_fork = &table->forks[(i + 1) % table->nbr_of_philos];
        table->philos[i].table = table;
        i++; 
    }
    pthread_mutex_init(&table->state_mutex, NULL);
    pthread_mutex_init(&table->log_mutex, NULL);
}
