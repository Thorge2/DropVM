#include "include/parser.h"
#include "include/codes.h"
#include "include/io.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[200] = {
        FUNC,

        // setup memory
        MOVE64, 0,0,0,0, 0,0,0,0, 'H','e','l','l','o',',',' ','w',
        MOVE64, 0,0,0,0, 0,0,0,8, 'o','r','l','d','!','\n','\0','\0',
        CREATE_DSTACK,
        MOVE, 0,0,0,1, 0,0,0,0, 0,

        CALL, 0,0,0,1,
        PUSH, 0,

        END,

        FUNC,

        LOAD, 0,0,0,1, 0,0,0,0,
        PUSH, 1,
        ADD,
        POP, 0,0,0,1, 0,0,0,0,

        PUSH32, 0,0,0,0,
        PUSH32, 0,0,0,0,
        PRINT,

        PUSH16, 0,0,
        PUSH, 0,
        LOAD, 0,0,0,1, 0,0,0,0,
        PUSH32, 0,0,0,10,
        IFLT, 0,0,0,0,

        END,
    };

    write_file("./bin.dvm", src, sizeof(src));

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
}