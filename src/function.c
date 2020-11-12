#include "include/function.h"
#include "include/codes.h"
#include <stdlib.h>
#include <stdio.h>

function_T* init_function(template_T* template, stack_T* parent)
{
    function_T* func = calloc(1, sizeof(struct FUNCTION_STRUCT));
    func->template = template;
    func->stack = init_stack(1024, parent);
    func->counter = 0;

    return func;
}

void function_run(function_T* function, runtime_T* runtime)
{
    while (function->template->code[function->counter] != FUNC && runtime->running)
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
                stack_push(function->stack, function->template->code[function->counter]);
                function->counter++;
                break;
            }

            default: { printf("[Error] Unknown instruction %d at %ld in %ld\n", function->template->code[function->counter], function->counter, function->template->id); exit(1); }
        }
    }
}