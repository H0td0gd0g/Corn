#pragma once
#include <windows.h>
#include "parser.h"
#include "package.h"
#include "commandResult.h"
#include "cmdDef.h"

#define MAX_ARGS 8

typedef struct
{
    CHAR commandUUID[36]; // コマンドごとのUUID
    BYTE commandType; // コマンドの種類 
    BYTE argCount; // コマンドの引数の数
    SIZE_T argsSize[MAX_ARGS];
    PBYTE args[MAX_ARGS];
} Command, *PCommand;

BYTE getTaskCount(_In_ PParser parser);
PCommand tlvReadField(PParser parser);
BOOL tlvWriteField(PPackage package, PCmdResult result);
BOOL freeCommand(PCommand cmd);