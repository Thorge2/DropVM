#include "include/parser.h"
#include "include/codes.h"
#include "include/io.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[200] = {
        FUNC,

        PUSH, 4,
        PUSH32, 0,0,0,0,
        PUSH32, 0,0,0,0,
        POPS,

        PUSH32, 0,0,0,0,
        PUSH32, 0,0,0,0,
        LOADS,
        END,
    };

    write_file("./bin.dvm", src, sizeof(src));

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
}