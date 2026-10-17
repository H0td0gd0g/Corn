#include <windows.h>
#include <string.h>
#include "package.h"
#include "corn.h"
#include "parser.h"
//UUIDは36バイト固定
BOOL addUUID(PPackage package, PCHAR uuid){
    package->buffer = LocalReAlloc(package->buffer, package->size + 36, LMEM_MOVEABLE | LMEM_ZEROINIT);

    memcpy((PUCHAR)(package->buffer) + package->size, uuid, 36);
    package->size += 36;

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
    package->buffer = LocalReAlloc(package->buffer, package->size + sizeof(UINT32), LMEM_MOVEABLE | LMEM_ZEROINIT);
    addUINT32ToBuffer((PUCHAR)(package->buffer) + package->size, value);
    package->size += sizeof(UINT32); //update buffer length

    return TRUE;
}

// BYTE
BOOL addBYTEToBuffer(PUCHAR TargetAddr, BYTE value) {
    if (TargetAddr == NULL) return FALSE;
    memcpy(TargetAddr, &value, sizeof(BYTE));
    return TRUE;
}

BOOL addByte(PPackage package, BYTE value){
    package->buffer = LocalReAlloc(package->buffer, package->size + sizeof(BYTE), LMEM_MOVEABLE | LMEM_ZEROINIT);
    addBYTEToBuffer((PUCHAR)(package->buffer) + package->size, value);
    package->size += sizeof(BYTE); //update buffer length

    return TRUE;
}

BOOL addBytes(PPackage package, PBYTE data, SIZE_T length){
    package->buffer = LocalReAlloc(package->buffer, package->size + length, LMEM_MOVEABLE | LMEM_ZEROINIT);
    memcpy((PUCHAR)(package->buffer) + package->size, data, length);
    package->size += length;
    return TRUE;
}

// TODO:addInt32以外の型を追加する。

//initはagentUUIDとtaskUUIDを含めるかどうか(TRUEだと含める)

//comandID =
/*
#define CMD_CHECKIN     0x01
#define CMD_GET_TASKING 0x04
#define CMD_RESPONSE    0x05
*/

PPackage newPackage(BOOL init){
    // ! メモリを確保
    PPackage Package = (PPackage)LocalAlloc(LPTR, sizeof(*Package));

    if (!Package){
        return NULL;
    }

    // ! メモリを確保
    Package->buffer = (PVOID)LocalAlloc(LPTR, sizeof(BYTE));

    if (!Package->buffer){
        return NULL;
    }

    Package->size = 0;

    if(init){
        addUUID(Package, corn_config.AgentID); // agent uuid
    }

    return Package;
}

VOID freePackage(PPackage package){
    LocalFree(package->buffer);
    LocalFree(package);
}