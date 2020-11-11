#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>

file_T* read_file(char* src)
{
    FILE* ptr;
    ptr = fopen(src, "rb");
    if (!ptr)
    {
        printf("[IO] File not found: %s\n", src);
        exit(1);
    }

    fseek(ptr, 0L, SEEK_END);
    size_t size = ftell(ptr);
    rewind(ptr);

    unsigned char* buffer = calloc(size, sizeof(unsigned char));

    fread(buffer, size, 1, ptr);


    file_T* file = calloc(1, sizeof(struct FILE_STRUCT));
    file->buffer = buffer;
    file->size = size;

    return file;
}

void write_file(char* src, unsigned char* buffer, size_t size)
{
    FILE* ptr;
    ptr = fopen(src, "wb");
    if (!ptr)
    {
        printf("[IO] File not found: %s\n", src);
        exit(1);
    }

    fwrite(buffer, size, 1, ptr);
}