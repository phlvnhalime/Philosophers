/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:15:09 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/25 12:15:11 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_sleep(long durasion_ms)
{
	long	start_time;

	start_time = get_time(0);
	while (get_time(0) - start_time < durasion_ms)
		usleep(500);
}
