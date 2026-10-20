#pragma once

#include <windows.h>
#include "tlv.h"
#include "cmdDef.h"
#include "executeCommand.h"
#include "commandResult.h"
#include "checkin.h"

PCmdResult dispatchCommand(PCommand cmd);