#include "include/stack.h"
#include <stdlib.h>
#include <stdio.h>

stack_T* init_stack(size_t init_size)
{
    stack_T* stack = calloc(1, sizeof(struct STACK_STRUCT));
    stack->size = init_size;
    stack->init_size = init_size;

    stack->data = calloc(stack->size, sizeof(char));
    stack->ptr = -1;
    stack->base_ptr = -1;

    return stack;
}

void stack_push(stack_T* stack, char data)
{
    if (stack->ptr == stack->size)
    {
        stack->size += stack->init_size;
        stack->data = realloc(stack->data, stack->size * sizeof(char));
    }
    stack->ptr += 1;
    stack->data[stack->ptr] = data;
}

unsigned char stack_pop(stack_T* stack)
{
    if (stack->ptr == -1)
    {
        printf("[Stack pop] stack limits exceeded: %ld\n", stack->ptr);
        exit(1);
    }

    unsigned char data = stack->data[stack->ptr--];
    return data;
}
