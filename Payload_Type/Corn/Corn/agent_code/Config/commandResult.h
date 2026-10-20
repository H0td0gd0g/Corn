#pragma once

#include <windows.h>

typedef struct
{
    CHAR commandUUID[36];
    BOOL success;
    PBYTE output;
    SIZE_T size;
} CmdResult, *PCmdResult;