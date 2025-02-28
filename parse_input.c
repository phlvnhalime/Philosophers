/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:12:24 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/18 16:12:25 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi(const char *str)
{
	long		num;
	int			len;

	len = 0;
	num = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_function("Only positive number!");
	if (!(*str >= '0' && *str <= '9'))
		exit_function("this is not valid digit");
	// nbr = str;
	// while (*str++ >= '0' && *str++ <= '9')
	// 	++len;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		len++;
		str++;
	}
	if(num > INT_MAX || len > 10) 
    	exit_function("the limit is INT_MAX");
	return (num);
}


void	parse_input(t_table *table, char *av[])
{
	table->nbr_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->philos_must_eat = ft_atoi(av[5]);
	else
		table->philos_must_eat = -1;
	if( table->nbr_of_philos < 1 || table->time_to_die < 1  || table->time_to_eat  < 1 || table->time_to_sleep  < 1 || (table->philos_must_eat != -1 && table->philos_must_eat < 1))
		exit_function("Arguments must be possitive and non zero");
}