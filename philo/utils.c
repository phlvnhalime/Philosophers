/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:19:17 by hpehliva          #+#    #+#             */
/*   Updated: 2025/03/06 21:19:18 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		write(2, "Error! Get_time\n", 16);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_sleep(long duration_ms)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < duration_ms)
		usleep(500);
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_itoa(long n, char *buffer)
{
	char	tmp[21];
	int		i;
	int		j;
	long	nb;

	i = 0;
	j = 0;
	nb = n;
	if (nb == 0)
		tmp[i++] = '0';
	while (nb)
	{
		tmp[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	while (i > 0)
		buffer[j++] = tmp[--i];
	return (j);
}
