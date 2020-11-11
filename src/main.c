#include "include/parser.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char src[100] = {
        2, 1, 4, 5, 6, 2, 4, 5, 8
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    for (int i = 0; i < runtime->template_count; i++)
    {
        printf("Template id: %d\n", runtime->templates[i]->id);
        for (int n = 0; n < strlen(runtime->templates[i]->code); n++)
        {
            if (runtime->templates[i]->code[n] == 2)
                break;
            printf("%d\n", runtime->templates[i]->code[n]);
        }
        printf("\n");
    }

    return 0;
}