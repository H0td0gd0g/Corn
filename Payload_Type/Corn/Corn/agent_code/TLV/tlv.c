#include "tlv.h"

// 何個のコマンドが入っているか確認
BYTE getTaskCount(
    _In_ PParser parser
    )
    {
    PBYTE PTaskCount = getByte(parser, 1); // マジックナンバーなので後で修正する(タスク数は1バイトでくる)
    BYTE taskCount = *PTaskCount;
    LocalFree(PTaskCount);
    
    return taskCount;
}


// 一つのコマンドバイナリデータを解析する関数
// ! freeCommand関数で使用後にメモリを解放する。
PCommand tlvReadField(PParser parser){
    PCommand cmd = (PCommand)LocalAlloc(LPTR, sizeof(Command));

    SIZE_T uuid = 36;
    SIZE_T szArgCount = 1;
    SIZE_T cmdType = 1; // 1byte
    SIZE_T szValueSize = 4;

    PCHAR taskUUID = (PCHAR)getByte(parser, &uuid);
    memcpy(cmd->commandUUID, taskUUID, 36);
    LocalFree(taskUUID);

    PBYTE argcount = getByte(parser, &szArgCount);
    cmd->argCount = *argcount;
    LocalFree(argcount);

    for (BYTE i = 0; i < cmd->argCount; i++){
        PBYTE cmdtype = getByte(parser, &cmdType);
        cmd->commandType[i] = *cmdtype;
        LocalFree(cmdtype);

        PSIZE_T valueSize = (PSIZE_T)getByte(parser, &szValueSize);
        cmd->argsSize[i] = *valueSize;

        PBYTE args = getByte(parser, valueSize);
        cmd->args[i] = args;

                LocalFree(valueSize);
    }    

    return cmd;
}


BOOL freeCommand(PCommand cmd){
    if (cmd == NULL) return FALSE;
    BYTE count = cmd->argCount;
    for(BYTE i = 0; i < count; i++){
        LocalFree(cmd->args[i]);
    }
    LocalFree(cmd);

    return TRUE;
}


PPackage tlvWriteField(PPackage package, PCmdResult result)
{
    addUUID(package, result->commandUUID); //cmd uuid  NO! agentUUID
    addByte(package, result->success); // true or false
    addUInt32(package, (UINT32)result->size);
    addBytes(package, result->output, result->size); // result value
}

