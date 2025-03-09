/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:47:38 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 20:47:40 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> // For testing strcmp
# include <sys/_types.h>
# include <sys/cdefs.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>

/*
	The colour codes are used to make the output more readable.
*/
# define RD "\033[0;31m"
# define GRN "\033[0;32m"
# define YLLW "\033[0;33m"
# define BLU "\033[0;34m"
# define PPLE "\033[0;35m"
# define C "\033[0;36m"
# define RST "\033[0m"


/*
    Define it as a keyword to mutex lock and unlock and initialize and mutex_t
*/
# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock
# define INIT pthread_mutex_init
# define DESTROY pthread_mutex_destroy
# define mutex_t pthread_mutex_t


/*
    Define the maximum number of philosophers
*/
# define MAX_PHILOS 300

// typedef enum e_mutex
// {
// 	LOCK,
// 	UNLOCK,
// 	INIT,
// 	DESTROY
// }						t_mutex;

typedef enum e_state
{
	PICKUP_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}						t_state;

typedef struct s_table	t_table;


typedef struct s_philo
{
	pthread_t			thread_id;
	int					philo_id;
	int					flag_eating;
	int					meal_counter;
	long				last_meal;
	long				time_to_sleep;
	long				time_to_eat;
	long				time_to_die;
    long				start_time;
	int					philos_must_eat;
	int					nbr_of_philos;
	bool				*die;
	mutex_t				*left_fork;
	mutex_t				*right_fork;
	mutex_t     		*dead_mutex;
	mutex_t     		*state_mutex;
    mutex_t             *write_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	bool				end_of_simulation;
	mutex_t     		dead_mutex;
	mutex_t     		state_mutex;
    mutex_t             write_mutex;
	pthread_t			monitor_thread;
	t_philo				*philos;
};

/* Parsing Arguments */
int	parse_input(t_philo *philos, char *av[]);
int check_av(char *av);
long	ft_atoi(char *str);

/*INITIALIZED*/
void    initialized_arguments(t_philo *philos, char *av[]);
void    simulation_start(t_table *table, t_philo *philos);
void    initialized_fork(mutex_t *forks, int nbr_philos);
void initialized_philos(t_philo *philos, t_table *table, mutex_t *forks, char *av[]);

/* Routine */
int create_threads(t_table *table, mutex_t *forks);
void	handle_single_philos(t_philo *philos);
void    *philosophers_routine(void *av);
int check_end_loop(t_philo *philo);

/* SIMULATION */
void    *controller(void *av);
int check_fill_ful(t_philo *philo);
int check_died(t_philo *philos);
int time_to_die(t_philo *philo, long time_to_die);
void    print_status(t_state status, t_philo *philo, int id);

/* UTILS */
long long get_time(void);
int check_sleep(long duration_ms);
int ft_strlen(const char *str);
int ft_itoa(long n, char *buffer);

/* EATING-SLEEPING-THINKING*/
void    thinking(t_philo *philo);
void    sleeping(t_philo *philo);
void eating(t_philo *philo);

/*CLEAN*/
void cleanup(char *str, t_table *table, mutex_t *forks);

/*SAFE MUTEX*/
// void safe_mutex(mutex_t *mutex, t_mutex opcode);
#endif