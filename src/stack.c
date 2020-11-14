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
    stack->base_ptr = 0;

    return stack;
}

void stack_push(stack_T* stack, char data)
{
    u_int32_t index = stack->base_ptr + stack->ptr;
    if (index == stack->size)
    {
        stack->size += stack->init_size;
        stack->data = realloc(stack->data, stack->size * sizeof(char));
    }
    stack->data[index] = data;
    stack->ptr++;
}

unsigned char stack_pop(stack_T* stack)
{
    stack->ptr--;
    u_int32_t index = stack->base_ptr + stack->ptr;
    if (index < 0)
    {
        printf("[Stack pop] stack limits exceeded: %d\n", index);
        exit(1);
    }

    return stack->data[index];
}

void stack_set_value(stack_T* stack, u_int32_t ptr, unsigned char data)
{
    u_int32_t index = stack->base_ptr + ptr;
    if (index < 0 || index > stack->size)
    {
        printf("[Stack set] stack limits exceeded: %d\n", index);
        exit(1);
    }

    stack->data[index]= data;
}

unsigned char stack_get_value(stack_T* stack, u_int32_t ptr)
{
    u_int32_t index = stack->base_ptr + ptr;
    if (index < 0 || index > stack->size)
    {
        printf("[Stack set] stack limits exceeded: %d\n", index);
        exit(1);
    }

    return stack->data[index];
}

void stack_set_frame(stack_T* stack, u_int32_t ptr)
{
    if (ptr < 0 || ptr > stack->size)
    {
        printf("[Stack frame] out of range: %d\n", ptr);
        exit(1);
    }

    stack->base_ptr = ptr;
}
