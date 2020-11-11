#ifndef DROP_IO_H
#define DROP_IO_H

#include <stdlib.h>

typedef struct FILE_STRUCT
{
    unsigned char* buffer;
    size_t size;
} file_T;


file_T* read_file(char* src);
void write_file(char* src, unsigned char* buffer, size_t size);

#endif