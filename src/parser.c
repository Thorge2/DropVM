#include "include/parser.h"
#include "include/codes.h"
#include "include/runtime.h"
#include <stdio.h>

parser_T* init_parser(unsigned char* code, size_t size)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->code = code;
    parser->size = size;
    parser->runtime = init_runtime();

    return parser;
}

runtime_T* parser_parse(parser_T* parser)
{
    unsigned int counter = 0;
    while (counter < parser->size)
    {
        if (parser->code[counter] == FUNC)
        {
            parser_create_template(parser, ++counter);
            while (parser->code[counter] != END)
            {
                counter++;
            }
        }
        counter++;
    }
    
    return parser->runtime;
}

void parser_create_template(parser_T* parser, unsigned int counter)
{
    template_T* template = init_template(parser->code + counter, parser->runtime->template_count);
    runtime_push_template(parser->runtime, template);
}