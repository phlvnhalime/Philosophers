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
