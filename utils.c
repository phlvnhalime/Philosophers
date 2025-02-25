/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:57:37 by hpehliva          #+#    #+#             */
/*   Updated: 2025/02/18 15:57:39 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    exit_function(const char *str)
{
    printf(RD"%s\n"RST, str);
    exit(EXIT_FAILURE);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while(s1[i] || s2[i])
    {
        if(s1[i] != s2[i])
            return((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return 0;
}