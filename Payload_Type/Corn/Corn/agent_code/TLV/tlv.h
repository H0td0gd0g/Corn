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
    // ! UUIDはすくなくともBYTEではない
    CHAR commandUUID[36]; // コマンドごとのUUID
    BYTE argCount; // コマンドの引数の数
    BYTE commandType[MAX_ARGS]; // コマンドの種類 
    SIZE_T argsSize[MAX_ARGS];
    PBYTE args[MAX_ARGS];
} Command, *PCommand;

PCommand tlvReadField(PParser parser);
PBYTE tlvWriteField(PPackage package, PCmdResult result);
BOOL freeCommand(PCommand cmd);