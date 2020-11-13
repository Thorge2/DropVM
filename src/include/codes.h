#ifndef DROP_CODES_H
#define DROP_CODES_H

#include <stdlib.h>

enum
{
    NOOP = 0,
    HALT,

    FUNC,
    END,

    PUSH,
    POP,
    LOAD,
    MOVE,

    ADD,
    SUB,
    MULT,
    DIV,

    CALL,
    RETURN
};

#endif