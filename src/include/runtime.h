#ifndef DROP_RUNTIME_H
#define DROP_RUNTIME_H

#include "template.h"
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct RUNTIME_STRUCT
{
    template_T** templates;
    u_int32_t template_count;
    bool running;

    stack_T* function_stack;
    stack_T* data_stack;
} runtime_T;

runtime_T* init_runtime();

void runtime_push_template(runtime_T* runtime, template_T* template);

int runtime_run(runtime_T* runtime);

#endif