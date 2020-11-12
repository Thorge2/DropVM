#ifndef DROP_FUNCTION_H
#define DROP_FUNCTION_H

#include "stack.h"
#include "template.h"
#include "runtime.h"

typedef struct FUNCTION_STRUCT
{
    stack_T* stack;
    u_int64_t counter;
    template_T* template;
} function_T;

function_T* init_function(template_T* template, stack_T* parent);

void function_run(function_T* function, runtime_T* runtime);

#endif