#include "philo.h"

void    data_init(t_table *table)
{
    table->end_of_simulation = false;
    table->philos = memory_loop(sizeof(t_philo) * table->nbr_of_philos); // I'm gonna get an error for this part!
    table->forks = memory_loop(sizof(t_fork) * table->nbr_of_philos);

    int i = 0;
    while(i < table->nbr_of_philos)
    {
        pthread_mutex_init(table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
    }

    

    if()
}