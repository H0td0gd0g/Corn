#include <windows.h>

typedef struct
{
    PBYTE result;
    PSIZE_T size;
    PBOOL success;
} cmdResult, *PcmdResult;