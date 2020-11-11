#ifndef DROP_TEMPLATE_H
#define DROP_TEMPLATE_H

#include <stdlib.h>

typedef struct TEMPLATE_STRUCT
{
    char* code;
    u_int64_t id;
} template_T;

template_T* init_template(char* code, u_int64_t id);

#endif