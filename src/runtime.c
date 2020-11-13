#include "include/runtime.h"
#include "include/function.h"

runtime_T* init_runtime()
{
    runtime_T* runtime = calloc(1, sizeof(struct RUNTIME_STRUCT));
    runtime->template_count = 0;
    runtime->templates = 0;
    runtime->running = false;

    runtime->stack = init_stack(1024);
    runtime->heap = init_stack(1024);

    return runtime;
}

void runtime_push_template(runtime_T* runtime, template_T* template)
{
    if (runtime->template_count == 0)
        runtime->templates = calloc(1, sizeof(struct TEMPLATE_STRUCT*));
    else
        runtime->templates = realloc(runtime->templates, (runtime->template_count + 1) * sizeof(struct TEMPLATE_STRUCT*));

    runtime->templates[runtime->template_count] = template;
    runtime->template_count++;
}

int runtime_run(runtime_T* runtime)
{
    runtime->running = true;
    function_T* main = init_function(runtime->templates[0]);
    function_run(main, runtime);
    return stack_pop(runtime->stack);
}