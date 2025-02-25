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

/*
    For each memory allocation. I will not forget it the return NULL.
    I can't do free because some links connect each other i have to do this on working functions.
*/
void *memory_loop(size_t size)
{
    void *turn;

    turn = malloc(size);
    if(NULL == turn)
        exit_function("Memory doesn't allocate");
    return turn;
}
