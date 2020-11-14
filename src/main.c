#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[30] = {
        FUNC,
        MOVE16, 0,0,0,0, 4,2,
        LOAD16, 0,0,0,0,
        END
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
    return 0;
}