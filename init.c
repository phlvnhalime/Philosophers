#include "philo.h"

static void philo_status(t_philo *philo, const char *str)
{
    pthread_mutex_lock(&),// Check the links for this connection! /TODO
}


void    *philosophers_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->thread_id;

    int left_fork = philo->philo_id - 1;
    int right_fork = philo->philo_id % table->nbr_of_philos;

    while(1)
    {
        //philo_status(t_philo *philo, const char *str); TODO
    }

}

void    data_init(t_table *table)
{
    table->end_of_simulation = false;
    table->philos = memory_loop(sizeof(t_philo) * table->nbr_of_philos); // I'm gonna get an error for this part!
    table->forks = memory_loop(sizof(t_fork) * table->nbr_of_philos);

    /*
        Start forks wit mutex
    */
    int i = 0;
    while(i < table->nbr_of_philos)
    {
        pthread_mutex_init(table->forks[i].fork, NULL);
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
    }
}