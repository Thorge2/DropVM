#include "include/template.h"

template_T* init_template(unsigned char* code, u_int64_t id)
{
    template_T* temp = calloc(1, sizeof(struct TEMPLATE_STRUCT));
    temp->code = code;
    temp->id = id;

    return temp;
}