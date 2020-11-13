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
    while (function->template->code[function->counter] != FUNC && function->template->code[function->counter] != RETURN && runtime->running)
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
                stack_push(runtime->stack, function->template->code[function->counter]);
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
                function_run(func, runtime);
                function->counter++;
                break;
            }

            default: { printf("[Error] in %ld: Unknown instruction %d at %ld\n", function->template->id, function->template->code[function->counter], function->counter); exit(1); }
        }
    }
}