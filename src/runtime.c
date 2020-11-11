#include "include/runtime.h"

runtime_T* init_runtime()
{
    runtime_T* runtime = calloc(1, sizeof(struct RUNTIME_STRUCT));
    runtime->template_count = 0;
    runtime->templates = 0;

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