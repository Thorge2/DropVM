#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[30] = {
        FUNC, // declared function 0
        PUSH, 2, // pushes 2 onto the function stack
        PUSH, 4, // pushen 4 onto the function stack
        ADD, // adds the last two numbers on the function stack
        END, // return the value ontop of the function stack
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
    return 0;
}