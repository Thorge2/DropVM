#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[30] = {
        FUNC,
        PUSH16, 1,2,
        ADD,
        END
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
    return 0;
}