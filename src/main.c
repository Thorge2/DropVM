#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[30] = {
        FUNC, // declares a function 0
        MOVE, 1, 0, // moves 0 into adress 1 
        CALL, 1, // calls function 1
        LOAD, 1, // loads value from index 1 onto the stack
        END, // defines the end of function 0
        FUNC, // declares function 1
        MOVE, 1, 2, // moves value 2 into adress 1
        END, // declares end of function 1
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
    return 0;
}