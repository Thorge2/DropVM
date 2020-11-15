#include "include/stack.h"
#include <stdlib.h>
#include <stdio.h>

stack_T* init_stack(size_t init_size)
{
    stack_T* stack = calloc(1, sizeof(struct STACK_STRUCT));
    stack->size = init_size;
    stack->init_size = init_size;

    stack->data = calloc(stack->size, sizeof(char));
    stack->ptr = 0;

    return stack;
}

void stack_push(stack_T* stack, char data)
{
    if (stack->ptr == stack->size)
    {
        stack->size += stack->init_size;
        stack->data = realloc(stack->data, stack->size * sizeof(char));
    }
    stack->data[stack->ptr] = data;
    stack->ptr++;
}

unsigned char stack_pop(stack_T* stack)
{
    stack->ptr--;
    if (stack->ptr < 0)
    {
        printf("[Stack pop] stack limits exceeded: %d\n", stack->ptr);
        exit(1);
    }

    return stack->data[stack->ptr];
}

void stack_set_value(stack_T* stack, u_int32_t ptr, unsigned char data)
{
    if (ptr < 0 || ptr > stack->size)
    {
        printf("[Stack set] stack limits exceeded: %d\n", stack->ptr);
        exit(1);
    }

    if (ptr > stack->ptr)
        stack->ptr = ptr;

    stack->data[ptr] = data;
}

unsigned char stack_get_value(stack_T* stack, u_int32_t ptr)
{
    if (ptr < 0 || ptr > stack->size)
    {
        printf("[Stack get] stack limits exceeded: %d\n", stack->ptr);
        exit(1);
    }

    return stack->data[ptr];
}
