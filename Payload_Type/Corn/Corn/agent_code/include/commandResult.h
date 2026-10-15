#include <windows.h>

typedef struct
{
    PBYTE output;
    SIZE_T size;
    BOOL success;
} CmdResult, *PCmdResult;