#include "tlv.h"


BYTE getTaskCount(
    _In_ PParser parser
    )
    {
    PBYTE PTaskCount = getByte(parser, 1); // マジックナンバーなので後で修正する(タスク数は1バイトでくる)
    BYTE taskCount = *PTaskCount;
    LocalFree(PTaskCount);
    
    return taskCount;
}


/*
tlvreadfieldをparserを受け取ってそのバイト数だけ読むようにしよう
今のままなら1コマンドしか実行できない

*/


// utlv ?? uuid + type length value
PCommand tlvReadField(PParser parser){
    PCommand cmd = (PCommand)LocalAlloc(LPTR, sizeof(Command));

    SIZE_T uuid = 36;
    SIZE_T szArgCount = 1;
    SIZE_T cmdType = 1; // 1byte
    SIZE_T szValueSize = 4;

    PCHAR cmdUUID = (PCHAR)getByte(parser, &uuid);
    memcpy(cmd->commandUUID, cmdUUID, 36);
    LocalFree(cmdUUID);

    PBYTE argcount = getByte(parser, &szArgCount);
    cmd->argCount = *argcount;
    LocalFree(argcount);
    

    for (BYTE i = 0; i < cmd->argCount; i++){
        PBYTE cmdtype = getByte(parser, &cmdType);
        cmd->commandType[i] = *cmdtype;
        LocalFree(cmdtype);

        PSIZE_T valueSize = (PSIZE_T)getByte(parser, &szValueSize);
        cmd->argsSize[i] = *valueSize;
        LoclaFree(valueSize);

        PBYTE args = getByte(parser, valueSize);
        cmd->args[i] = args;
    }    

    return cmd;
}


BOOL freePCommand(PCommand cmd){
    if (cmd == NULL) return FALSE;
    BYTE count = cmd->argCount;
    for(BYTE i = 0; i < count; i++){
        LocalFree(cmd->args[i]);
    }
    LocalFree(cmd);

    return TRUE;
}




// ! 呼び出し先でargsのメモリを解放する必要がある。


UINT32 commandID = 0;

PPackage tlvWriteField(PCmdResult result)
{
    PPackage Package = newPackage(commandID, TRUE);
    addByte(Package, CMD_RESULT);
    addUInt32(Package, (UINT32)result->size);
    addBytes(Package, result->output, result->size);
    
    return Package;
}