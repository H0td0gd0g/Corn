#pragma once
#include <windows.h>
#include "parser.h"

#define MAX_ARGS 8

typedef struct
{
    BYTE commandID;
    PBYTE args[MAX_ARGS];
    SIZE_T argsSize[MAX_ARGS];
} Command, *PCommand;
