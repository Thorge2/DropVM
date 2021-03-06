#ifndef DROP_STACK_H
#define DROP_STACK_H

#include <stdlib.h>

typedef struct STACK_STRUCT
{
    unsigned char* data;
    size_t size;
    size_t init_size;
    u_int32_t ptr;
} stack_T;

stack_T* init_stack(size_t init_size);

void stack_push(stack_T* stack, char data);
unsigned char stack_pop(stack_T* stack);

void stack_set_value(stack_T* stack, u_int32_t ptr, unsigned char data);
unsigned char stack_get_value(stack_T* stack, u_int32_t ptr);

#endif