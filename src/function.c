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
            case POPS:
            {
                function_pops(runtime, 1);
                function->counter++;
                break;
            }
            case POPS16:
            {
                function_pops(runtime, 2);
                function->counter++;
                break;
            }
            case POPS32:
            {
                function_pops(runtime, 4);
                function->counter++;
                break;
            }
            case POPS64:
            {
                function_pops(runtime, 8);
                function->counter++;
                break;
            }
            case LOADS:
            {
                function_loads(runtime, 1);
                function->counter++;
                break;
            }
            case LOADS16:
            {
                function_loads(runtime, 2);
                function->counter++;
                break;
            }
            case LOADS32:
            {
                function_loads(runtime, 4);
                function->counter++;
                break;
            }
            case LOADS64:
            {
                function_loads(runtime, 8);
                function->counter++;
                break;
            }
            case CREATE_DSTACK:
            {
                runtime->data_stacks_ptr += 1;
                runtime->data_stacks = realloc(runtime->data_stacks, runtime->data_stacks_ptr * sizeof(struct STACK_STRUCT*));
                runtime->data_stacks[runtime->data_stacks_ptr] = init_stack(1024);
                function->counter++;
                break;
            }
            case DELETE_DSTACK:
            {
                u_int32_t adress = function_get_adress(function);
                if (adress > runtime->data_stacks_ptr || adress <= 0)
                {
                    printf("[Data stack delete] Cannot delete datastack: %d\n", adress);
                    exit(1);
                }
                free(runtime->data_stacks[adress]);
                if (adress == runtime->data_stacks_ptr)
                {
                    runtime->data_stacks_ptr -= 1;
                    runtime->data_stacks = realloc(runtime->data_stacks, runtime->data_stacks_ptr * sizeof(struct STACK_STRUCT*));
                }
                function->counter++;
                break;
            }
            case ADD:
            {
                function_add(runtime, 1);
                function->counter++;
                break;
            }
            case ADD16:
            {
                function_add(runtime, 2);
                function->counter++;
                break;
            }
            case ADD32:
            {
                function_add(runtime, 4);
                function->counter++;
                break;
            }
            case ADD64:
            {
                function_add(runtime, 8);
                function->counter++;
                break;
            }
            case SUB:
            {
                function_sub(runtime, 1);
                function->counter++;
                break;
            }
            case SUB16:
            {
                function_sub(runtime, 2);
                function->counter++;
                break;
            }
            case SUB32:
            {
                function_sub(runtime, 4);
                function->counter++;
                break;
            }
            case SUB64:
            {
                function_sub(runtime, 8);
                function->counter++;
                break;
            }
            case MULT:
            {
                function_mult(runtime, 1);
                function->counter++;
                break;
            }
            case MULT16:
            {
                function_mult(runtime, 2);
                function->counter++;
                break;
            }
            case MULT32:
            {
                function_mult(runtime, 4);
                function->counter++;
                break;
            }
            case MULT64:
            {
                function_mult(runtime, 8);
                function->counter++;
                break;
            }
            case DIV:
            {
                function_div(runtime, 1);
                function->counter++;
                break;
            }
            case DIV16:
            {
                function_div(runtime, 2);
                function->counter++;
                break;
            }
            case DIV32:
            {
                function_div(runtime, 4);
                function->counter++;
                break;
            }
            case DIV64:
            {
                function_div(runtime, 8);
                function->counter++;
                break;
            }
            case CALL:
            {
                u_int32_t adress = function_get_adress(function);
                if (adress < 0 || adress >= runtime->template_count)
                {
                    printf("[Error] in %d: Function %d is not defined\n", function->template->id, adress);
                    exit(1);
                }
                function_T* func = init_function(runtime->templates[adress]);

                function_run(func, runtime);

                function->counter++;
                break;
            }
            case JUMP:
            {
                u_int32_t adress = function_get_adress(function);
                function->counter = adress;
                break;
            }
            case IFE:
            {
                u_int32_t a = function_get_adress_stack(runtime);
                u_int32_t b = function_get_adress_stack(runtime);

                u_int32_t adress = function_get_adress(function);

                if (a == b)
                {
                    function->counter = adress;
                    break;
                }
                function->counter++;
                break;
            }
            case IFNE:
            {
                u_int32_t a = function_get_adress_stack(runtime);
                u_int32_t b = function_get_adress_stack(runtime);

                u_int32_t adress = function_get_adress(function);

                if (a != b)
                {
                    function->counter = adress;
                    break;
                }
                function->counter++;
                break;
            }
            case IFGT:
            {
                u_int32_t a = function_get_adress_stack(runtime);
                u_int32_t b = function_get_adress_stack(runtime);

                u_int32_t adress = function_get_adress(function);

                if (a < b)
                {
                    function->counter = adress;
                    break;
                }
                function->counter++;
                break;
            }
            case IFLT:
            {
                u_int32_t a = function_get_adress_stack(runtime);
                u_int32_t b = function_get_adress_stack(runtime);

                u_int32_t adress = function_get_adress(function);

                if (a > b)
                {
                    function->counter = adress;
                    break;
                }
                function->counter++;
                break;
            }
            case PRINT:
            {
                u_int32_t memory_adress = function_get_adress_stack(runtime);
                u_int32_t stack_adress = function_get_adress_stack(runtime);
                if (stack_adress > runtime->data_stacks_ptr)
                {
                    printf("[Print] Cannot access data stack: %d\n", stack_adress);
                    exit(1);
                }

                for (u_int32_t i = memory_adress; stack_get_value(runtime->data_stacks[stack_adress], i) != 0; i++)
                {
                    printf("%c", stack_get_value(runtime->data_stacks[stack_adress], i));
                }
                function->counter++;
                break;
            }
            case PRINTC:
            {
                unsigned char c = stack_pop(runtime->function_stack);
                printf("%c", c);
                function->counter++;
                break;
            }
            case PRINTI:
            {
                u_int32_t i = function_get_adress_stack(runtime);
                printf("%d", i);
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

u_int32_t function_get_adress_stack(runtime_T* runtime)
{
    u_int32_t adress = 0;
    for (int i = 0; i < 4; i++)
    {
        adress |= stack_pop(runtime->function_stack) << i * 8;
    }
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
    u_int32_t stack_adress = function_get_adress(function);
    if (stack_adress > runtime->data_stacks_ptr)
    {
        printf("[Pop] Cannot access data stack: %d\n", stack_adress);
        exit(1);
    }

    u_int32_t memory_adress = function_get_adress(function);

    for (int i = memory_adress; i < num_bytes + memory_adress; i++)
    {
        unsigned char data = stack_pop(runtime->function_stack);
        stack_set_value(runtime->data_stacks[stack_adress], i, data);
    }
}

inline void function_load(function_T* function, runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t stack_adress = function_get_adress(function);
    if (stack_adress > runtime->data_stacks_ptr)
    {
        printf("[Pop] Cannot access data stack: %d\n", stack_adress);
        exit(1);
    }

    u_int32_t memory_adress = function_get_adress(function);

    for (int i = memory_adress; i < num_bytes + memory_adress; i++)
    {
        unsigned char data = stack_get_value(runtime->data_stacks[stack_adress], i);
        stack_push(runtime->function_stack, data);
    }
}

inline void function_move(function_T* function, runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t stack_adress = function_get_adress(function);
    if (stack_adress > runtime->data_stacks_ptr)
    {
        printf("[Pop] Cannot access data stack: %d\n", stack_adress);
        exit(1);
    }

    u_int32_t memory_adress = function_get_adress(function);

    for (int i = memory_adress; i < num_bytes + memory_adress; i++)
    {
        function->counter++;
        stack_set_value(runtime->data_stacks[stack_adress], i, function_get_current(function));
    }
}

inline void function_pops(runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t memory_adress = function_get_adress_stack(runtime);

    u_int32_t stack_adress = function_get_adress_stack(runtime);
    if (stack_adress > runtime->data_stacks_ptr)
    {
        printf("[Pop] Cannot access data stack: %d\n", stack_adress);
        exit(1);
    }

    for (int i = memory_adress; i < num_bytes + memory_adress; i++)
    {
        unsigned char data = stack_pop(runtime->function_stack);
        stack_set_value(runtime->data_stacks[stack_adress], i, data);
    }
}

inline void function_loads(runtime_T* runtime, unsigned char num_bytes)
{
    u_int32_t memory_adress = function_get_adress_stack(runtime);

    u_int32_t stack_adress = function_get_adress_stack(runtime);
    if (stack_adress > runtime->data_stacks_ptr)
    {
        printf("[Pop] Cannot access data stack: %d\n", stack_adress);
        exit(1);
    }

    for (int i = memory_adress; i < num_bytes + memory_adress; i++)
    {
        unsigned char data = stack_get_value(runtime->data_stacks[stack_adress], i);
        stack_push(runtime->function_stack, data);
    }
}

inline void function_add(runtime_T* runtime, unsigned char num_bytes)
{
    u_int64_t a = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        a |= stack_pop(runtime->function_stack) << i * 8;
    }

    u_int64_t b = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        b |= stack_pop(runtime->function_stack) << i * 8;
    }
    
    u_int64_t data = a + b;
    for (int i = num_bytes - 1; i > -1; i--)
    {
        stack_push(runtime->function_stack, (data >> (8*i)) & 0xff);
    }
}

inline void function_sub(runtime_T* runtime, unsigned char num_bytes)
{
    u_int64_t a = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        a |= stack_pop(runtime->function_stack) << i * 8;
    }

    u_int64_t b = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        b |= stack_pop(runtime->function_stack) << i * 8;
    }
    
    u_int64_t data = a - b;
    for (int i = num_bytes - 1; i > -1; i--)
    {
        stack_push(runtime->function_stack, (data >> (8*i)) & 0xff);
    }
}

inline void function_mult(runtime_T* runtime, unsigned char num_bytes)
{
    u_int64_t a = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        a |= stack_pop(runtime->function_stack) << i * 8;
    }

    u_int64_t b = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        b |= stack_pop(runtime->function_stack) << i * 8;
    }
    
    u_int64_t data = a * b;
    for (int i = num_bytes - 1; i > -1; i--)
    {
        stack_push(runtime->function_stack, (data >> (8*i)) & 0xff);
    }
}

inline void function_div(runtime_T* runtime, unsigned char num_bytes)
{
    u_int64_t a = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        a |= stack_pop(runtime->function_stack) << i * 8;
    }

    u_int64_t b = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        b |= stack_pop(runtime->function_stack) << i * 8;
    }
    
    u_int64_t data = a / b;
    for (int i = num_bytes - 1; i > -1; i--)
    {
        stack_push(runtime->function_stack, (data >> (8*i)) & 0xff);
    }
}