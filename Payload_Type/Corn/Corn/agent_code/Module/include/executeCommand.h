#pragma once

#include <windows.h>
#include "commandResult.h"
#include "tlv.h"
#include "executeShell.h"

PCmdResult executeCommand(_In_ PCommand cmd);
VOID freeCmdResult(PCmdResult result);