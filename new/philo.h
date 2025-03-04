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
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> // For testing strcmp
# include <sys/_types.h>
# include <sys/cdefs.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

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

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					philo_id;
	int					meal_counter;
	bool				fill_full;
	long				last_meal;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	struct s_table		*table;

}						t_philo;

struct					s_table
{
	long				nbr_of_philos;
	long				time_to_sleep;
	long				time_to_eat;
	long				time_to_die;
	long				philos_must_eat;
	long				start_time;
	bool				end_of_simulation;
	pthread_mutex_t		log_mutex;
	pthread_mutex_t		state_mutex;
	t_fork				*forks;
	t_philo				*philos;
};

// - Utils:
void					exit_function(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
// GET_ARG
void					create_threads(t_table table);
// - Parse of arguments:
void					parse_input(t_table *table, char *av[]);
void					check_sleep(long durasion_ms);

// end of the simulation.
void					must_eat(t_table *table);
void					time_to_die(t_table *table, long current_time);
void					end_of_died(t_table *table);

//	#	Routine for threads
//	#	#	Time
long					get_time(long start_time);
//	#	#	#	Philos died message
bool					out_print(t_philo *philo, const char *status);
// 	#	#	#	#	Simulations rules
bool					check_simulation(t_philo *philo);
void					philo_status(t_philo *philo, const char *status);
void					*philosophers_routine(void *arg);
bool					check_simulation(t_philo *philo);
// INITIALIZED
void					data_init(t_table *table);
void					init_philos(t_table *table);
void					init_forks(t_table *table);
// EATING
void					pick_up(t_philo *philo);
void					time_to_eat(t_philo *philo);

// CLEAN
void					clean(t_table *table);
void					check_sleep(long durasion_ms);

#endif
