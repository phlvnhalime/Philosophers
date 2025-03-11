/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:52:18 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 20:52:19 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	unsigned long long	nbr;
	int					sign;
	int					i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}

int	check_av(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < 0 || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parse_input(t_philo *philos, char *av[])
{
	if (ft_atoi(av[1]) > MAX_PHILOS || ft_atoi(av[1]) <= 0
		|| check_av(av[1]) == 1)
		return (write(2, "Invalid philo number\n", 21), 1);
	if (ft_atoi(av[2]) <= 0 || check_av(av[2]) == 1)
		return (write(2, "Invalid time_to_die\n", 20), 1);
	if (ft_atoi(av[3]) <= 0 || check_av(av[3]) == 1)
		return (write(2, "Invalid time_to_eat\n", 20), 1);
	if (ft_atoi(av[4]) <= 0 || check_av(av[4]) == 1)
		return (write(2, "Invalid time_to_sleep\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_av(av[5]) == 1))
		return (write(2, "Invalid nnbr_of_times_philos_must_eat\n", 38), 1);
	return (0);
}
