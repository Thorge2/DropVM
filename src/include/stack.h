#ifndef DROP_STACK_H
#define DROP_STACK_H

#include <stdlib.h>

typedef struct STACK_STRUCT
{
    unsigned char* data;
    size_t size;
    size_t init_size;
    u_int64_t ptr;
    u_int64_t base_ptr;
} stack_T;

stack_T* init_stack(size_t init_size);

void stack_push(stack_T* stack, char data);
unsigned char stack_pop(stack_T* stack);

void stack_set_value(stack_T* stack, u_int64_t ptr, unsigned char data);
unsigned char stack_get_value(stack_T* stack, u_int64_t ptr);

void stack_set_frame(stack_T* stack, u_int64_t ptr);

#endif