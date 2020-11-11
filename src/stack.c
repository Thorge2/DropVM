#include "include/stack.h"
#include <stdlib.h>

stack_T* init_stack(size_t init_size, stack_T* parent)
{
    stack_T* stack = calloc(1, sizeof(struct STACK_STRUCT));
    stack->parent = parent;
    stack->size = init_size;
    stack->init_size = init_size;

    stack->data = calloc(stack->size, sizeof(char));
    stack->ptr = -1;

    return stack;
}