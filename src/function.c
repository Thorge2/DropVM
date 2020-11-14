#include "include/function.h"
#include "include/codes.h"
#include <stdlib.h>
#include <stdio.h>

function_T* init_function(template_T* template)
{
    function_T* func = calloc(1, sizeof(struct FUNCTION_STRUCT));
    func->template = template;
    func->counter = 0;

    return func;
}

void function_run(function_T* function, runtime_T* runtime)
{
    while (function->template->code[function->counter] != END && function->template->code[function->counter] != RETURN && runtime->running)
    {
        switch (function->template->code[function->counter])
        {
            case NOOP:
            {
                function->counter++;
                break;
            }
            case HALT:
            {
                runtime->running = false;
                break;
            }
            case PUSH:
            {
                function_push(function, runtime, 1);
                function->counter++;
                break;
            }
            case PUSH16:
            {
                function_push(function, runtime, 2);
                function->counter++;
                break;
            }
            case PUSH32:
            {
                function_push(function, runtime, 4);
                function->counter++;
                break;
            }
            case PUSH64:
            {
                function_push(function, runtime, 8);
                function->counter++;
                break;
            }
            case POP:
            {
                function_pop(function, runtime, 1);
                function->counter++;
                break;
            }
            case POP16:
            {
                function_pop(function, runtime, 2);
                function->counter++;
                break;
            }
            case POP32:
            {
                function_pop(function, runtime, 4);
                function->counter++;
                break;
            }
            case POP64:
            {
                function_pop(function, runtime, 8);
                function->counter++;
                break;
            }
            case LOAD:
            {
                function_load(function, runtime, 1);
                function->counter++;
                break;
            }
            case LOAD16:
            {
                function_load(function, runtime, 2);
                function->counter++;
                break;
            }
            case LOAD32:
            {
                function_load(function, runtime, 4);
                function->counter++;
                break;
            }
            case LOAD64:
            {
                function_load(function, runtime, 8);
                function->counter++;
                break;
            }
            case MOVE:
            {
                function_move(function, runtime, 1);
                function->counter++;
                break;
            }
            case MOVE16:
            {
                function_move(function, runtime, 2);
                function->counter++;
                break;
            }
            case MOVE32:
            {
                function_move(function, runtime, 4);
                function->counter++;
                break;
            }
            case MOVE64:
            {
                function_move(function, runtime, 8);
                function->counter++;
                break;
            }
            case ADD:
            {
                unsigned char a = stack_pop(runtime->function_stack);
                unsigned char b = stack_pop(runtime->function_stack);
                stack_push(runtime->function_stack, a + b);
                function->counter++;
                break;
            }
            case SUB:
            {
                unsigned char a = stack_pop(runtime->function_stack);
                unsigned char b = stack_pop(runtime->function_stack);
                stack_push(runtime->function_stack, a - b);
                function->counter++;
                break;
            }
            case MULT:
            {
                unsigned char a = stack_pop(runtime->function_stack);
                unsigned char b = stack_pop(runtime->function_stack);
                stack_push(runtime->function_stack, a * b);
                function->counter++;
                break;
            }
            case DIV:
            {
                unsigned char a = stack_pop(runtime->function_stack);
                unsigned char b = stack_pop(runtime->function_stack);
                stack_push(runtime->function_stack, a / b);
                function->counter++;
                break;
            }
            case CALL:
            {
                function->counter++;
                if (function_get_current(function) < 0 || function_get_current(function) >= runtime->template_count)
                {
                    printf("[Error] in %d: Function %d is not defined\n", function->template->id, function_get_current(function));
                    exit(1);
                }
                function_T* func = init_function(runtime->templates[function_get_current(function)]);

                u_int32_t stack_frame = runtime->data_stack->base_ptr;
                stack_set_frame(runtime->data_stack, runtime->data_stack->base_ptr + 1);

                function_run(func, runtime);

                stack_set_frame(runtime->data_stack, stack_frame);

                function->counter++;
                break;
            }

            default: { printf("[Error] in %d: Unknown instruction %d at %d\n", function->template->id, function_get_current(function), function->counter); exit(1); }
        }
    }
}

unsigned char function_get_current(function_T* function)
{
    return function->template->code[function->counter];
}

u_int32_t function_get_adress(function_T* function)
{
    u_int32_t adress = 0;
    function->counter++;
    adress |= function_get_current(function) << 24;
    function->counter++;
    adress |= function_get_current(function) << 16;
    function->counter++;
    adress |= function_get_current(function) << 8;
    function->counter++;
    adress |= function_get_current(function);
    return adress;
}

inline void function_push(function_T* function, runtime_T* runtime, unsigned char num_bytes)
{
    for (int i = 0; i < num_bytes; i++)
    {
        function->counter++;
        stack_push(runtime->function_stack, function_get_current(function));
    }
}

inline void function_pop(function_T* function, runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t adress = function_get_adress(function);

    for (int i = adress; i < num_bytes + adress; i++)
    {
        unsigned char data = stack_pop(runtime->function_stack);
        stack_set_value(runtime->data_stack, i, data);
    }
}

inline void function_load(function_T* function, runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t adress = function_get_adress(function);

    for (int i = adress; i < num_bytes + adress; i++)
    {
        unsigned char data = stack_get_value(runtime->data_stack, i);
        stack_push(runtime->function_stack, data);
    }
}

inline void function_move(function_T* funtion, runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t adress = function_get_adress(funtion);

    for (int i = adress; i < num_bytes + adress; i++)
    {
        funtion->counter++;
        stack_set_value(runtime->data_stack, i, function_get_current(funtion));
    }
}