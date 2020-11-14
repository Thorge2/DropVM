#ifndef DROP_FUNCTION_H
#define DROP_FUNCTION_H

#include "stack.h"
#include "template.h"
#include "runtime.h"

typedef struct FUNCTION_STRUCT
{
    u_int32_t counter;
    template_T* template;
} function_T;

function_T* init_function(template_T* template);

void function_run(function_T* function, runtime_T* runtime);

unsigned char function_get_current(function_T* function);
u_int32_t function_get_adress(function_T* function);

void function_push(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_pop(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_load(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_move(function_T* funtion, runtime_T* runtime, unsigned char num_bytes);

void function_add(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_sub(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_mult(function_T* function, runtime_T* runtime, unsigned char num_bytes);
void function_div(function_T* function, runtime_T* runtime, unsigned char num_bytes);

#endif