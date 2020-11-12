#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char src[10] = {
        FUNC, PUSH, 0, HALT
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    runtime_run(runtime);

    return 0;
}