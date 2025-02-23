/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:13:48 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:49 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

/*
    The colour codes are used to make the output more readable.
*/
#define RD      "\033[0;31m"
#define GRN     "\033[0;32m"
#define YLLW    "\033[0;33m"
#define BLU     "\033[0;34m"
#define PPLE    "\033[0;35m"
#define C       "\033[0;36m"
#define RST     "\033[0m"

typedef struct s_philo
{
    int         philo_id;
    int         meal_counter;
    bool        fill_full;
    t_fork      left_fork;
    t_fork      right_fork;
    pthread_t   thread_id;

}   t_philo;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
}   t_fork;

typedef struct s_table
{
    long    nbr_of_philos;
    long    time_to_sleep;
    long    time_to_eat;
    long    time_to_die;
    long    number_of_times_each_philos_must_eat;
    bool    end_of_simulation;
    t_fork  *forks;
    t_philo *philos;
}   t_table;

// - Utils:
void    exit_function(const char *str);
// - Parse of arguments:
void    parse_input(t_table *table, char *av[]);

// - Memory allocated loop:
void    memory_loop(size_t size);


#endif