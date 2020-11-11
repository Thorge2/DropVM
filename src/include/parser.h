#ifndef DROP_PARSER_H
#define DROP_PARSER_H

#include <stdlib.h>
#include "runtime.h"

typedef struct PARSER_STRUCT
{
    char* code;
    size_t size;
    runtime_T* runtime;
} parser_T;

parser_T* init_parser(char* code, size_t size);

runtime_T* parser_parse(parser_T* parser);

void parser_create_template(parser_T* parser, unsigned int counter);

#endif