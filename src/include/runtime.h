#ifndef DROP_RUNTIME_H
#define DROP_RUNTIME_H

#include "template.h"
#include <stdlib.h>

typedef struct RUNTIME_STRUCT
{
    template_T** templates;
    u_int64_t template_count;
} runtime_T;

runtime_T* init_runtime();

void runtime_push_template(runtime_T* runtime, template_T* template);

#endif