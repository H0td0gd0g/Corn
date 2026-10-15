#include "tlv.h"


// ! 呼び出し先でargsのメモリを解放する必要がある。
PCommand tlvReadField(PBYTE buffer, SIZE_T size){
    PParser parser = newParser(buffer, size);
    PCommand cmd = (PCommand)LocalAlloc(LPTR, sizeof(Command));
    
    SIZE_T totalSize = 0;
    PBYTE bodyLength = getByte(parser, &totalSize);

    SIZE_T uuidSize = 36;
    PBYTE taskid = getByte(parser, &uuidSize);


    SIZE_T typeSize = 1;
    SIZE_T lengthSize = 4;


    while(parser->length > 0){
        PBYTE type = getByte(parser, &typeSize);
        PBYTE length = getByte(parser, &lengthSize);

        SIZE_T valueLength = (SIZE_T)(*(UINT32*)length);
        PBYTE value = getByte(parser, &valueLength);

        switch (*type)
        {
            case TYPE_COMMAND_NAME:
                cmd->commandID = *value;
                LocalFree(value);
                break;
            case TYPE_COMMAND_ARGS:
                cmd->args[cmd->argCount] = value;
                cmd->argsSize[cmd->argCount] = valueLength;
                cmd->argCount++;
                break;
        }

        LocalFree(type);
        LocalFree(length);
    }
    return cmd;
}

UINT32 commandID = 0;

PPackage tlvWriteField(PCmdResult result)
{
    PPackage Package = newPackage(commandID, TRUE);
    addByte(Package, CMD_RESULT);
    addUInt32(Package, (UINT32)result->size);
    addBytes(Package, result->output, result->size);
    
    return Package;
}