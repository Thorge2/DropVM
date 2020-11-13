#include "include/parser.h"
#include "include/codes.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char src[20] = {
        FUNC,
        CALL, 1,
        END,
        FUNC,
        PUSH, 69,
        HALT,
        END
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
    return 0;
}