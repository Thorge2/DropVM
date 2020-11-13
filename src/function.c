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
                function->counter++;
                stack_push(runtime->function_stack, function->template->code[function->counter]);
                function->counter++;
                break;
            }
            case POP:
            {
                function->counter++;
                unsigned char data = stack_pop(runtime->function_stack);
                stack_set_value(runtime->data_stack, function->template->code[function->counter], data);
                function->counter++;
                break;
            }
            case LOAD:
            {
                function->counter++;
                unsigned char data = stack_get_value(runtime->data_stack, function->template->code[function->counter]);
                stack_push(runtime->function_stack, data);
                function->counter++;
                break;
            }
            case MOVE:
            {
                function->counter++;
                u_int64_t ptr =function->template->code[function->counter];
                function->counter++;
                unsigned char data = function->template->code[function->counter];
                stack_set_value(runtime->data_stack, ptr, data);
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
                if (function->template->code[function->counter] < 0 || function->template->code[function->counter] >= runtime->template_count)
                {
                    printf("[Error] in %ld: Function %d is not defined\n", function->template->id, function->template->code[function->counter]);
                    exit(1);
                }
                function_T* func = init_function(runtime->templates[function->template->code[function->counter]]);

                u_int64_t stack_frame = runtime->data_stack->base_ptr;
                stack_set_frame(runtime->data_stack, runtime->data_stack->base_ptr + 1);

                function_run(func, runtime);

                stack_set_frame(runtime->data_stack, stack_frame);

                function->counter++;
                break;
            }

            default: { printf("[Error] in %ld: Unknown instruction %d at %ld\n", function->template->id, function->template->code[function->counter], function->counter); exit(1); }
        }
    }
}