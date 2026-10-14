#include "executeCommand.h"

PBYTE executeCommand(
    _In_ PCommand cmd,
    _Out_ PSIZE_T size,
    _Out_ PBOOL success
){
    PBYTE output = executeShell(cmd, size, success);
    return output;
}