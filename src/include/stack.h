#ifndef DROP_STACK_H
#define DROP_STACK_H

#include <stdlib.h>

typedef struct STACK_STRUCT
{
    struct STACK_STRUCT* parent;
    char* data;
    size_t size;
    size_t init_size;
    u_int64_t ptr;
} stack_T;

stack_T* init_stack(size_t init_size, stack_T* parent);

#endif