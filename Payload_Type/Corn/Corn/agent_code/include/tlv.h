#pragma once
#include <windows.h>
#include "parser.h"

typedef enum {
    TYPE_COMMAND_NAME = 0x01,
    TYPE_COMMAND_ARGS = 0x02,
} TLV_TYPE;

#define MAX_ARGS 8

typedef struct
{
    BYTE commandID;
    PBYTE args[MAX_ARGS];
    SIZE_T argsSize[MAX_ARGS];
    DWORD argCount;
} Command, *PCommand;
