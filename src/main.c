#include "include/parser.h"
#include "include/codes.h"
#include "include/io.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned char src[100] = {
        FUNC,
        CREATE_DSTACK, // creates a new data stack, default is 0, each added becomes the next index
        MOVE64, 0,0,0,1, 0,0,0,0, 'H','e','l','l','o',',',' ','w', // moves the bytes for "Hello, w" onto data stack 1 in index 0
        MOVE64, 0,0,0,1, 0,0,0,8, 'o','r','l','d','!','\n','\0','\0', // moves the bytes for "orld!\n\0\0" onto datastack 1 in index 8
        PUSH32, 0,0,0,1, //pushes 1 onto the functin stack, this is the index for the datastack
        PUSH32, 0,0,0,0, //pushes 0 onto the function stack, this is the index from wich will be printed
        PRINT, // now prints "Hello, world!\n"
        PUSH, 0, // pushes 0 onto the function stack, because when main ends it returns the top of the function stack
        END 
    };

    parser_T* parser = init_parser(src, sizeof(src));
    runtime_T* runtime = parser_parse(parser);

    return runtime_run(runtime);
}