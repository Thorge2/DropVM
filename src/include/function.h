#ifndef DROP_FUNCTION_H
#define DROP_FUNCTION_H

#include "stack.h"
#include "template.h"

typedef struct FUNCTION_STRUCT
{
    stack_T* stack;
    u_int64_t counter;
    template_T* template;
} function_T;

function_T* init_function(template_T* template, stack_T* parent);

#endif