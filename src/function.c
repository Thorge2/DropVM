#include "include/function.h"
#include <stdlib.h>

function_T* init_function(template_T* template, stack_T* parent)
{
    function_T* func = calloc(1, sizeof(struct FUNCTION_STRUCT));
    func->template = template;
    func->stack = init_stack(1024, parent);
    func->counter = 0;

    return func;
}

