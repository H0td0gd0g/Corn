#include "executeCommand.h"
// cmd or powershell...
PCmdResult executeCommand(
    _In_ PCommand cmd
){
    PCmdResult result = executeShell(cmd);
    return result;
}

