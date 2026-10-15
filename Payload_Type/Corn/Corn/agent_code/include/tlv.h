#pragma once
#include <windows.h>
#include "parser.h"
#include "package.h"
#include "commandResult.h"
#include "cmdDef.h"

typedef enum {
    TYPE_COMMAND_NAME = 0x01, // shell, excute_coff, etc...
    TYPE_COMMAND_ARGS = 0x02, // whoami, where curl...
} TLV_TYPE;

#define MAX_ARGS 8

typedef struct
{
    BYTE commandID;
    PBYTE args[MAX_ARGS];
    SIZE_T argsSize[MAX_ARGS];
    DWORD argCount;
} Command, *PCommand;
