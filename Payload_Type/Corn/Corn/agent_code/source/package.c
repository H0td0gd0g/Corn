#include <windows.h>
#include <string.h>
#include "package.h"
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

// TODO:UUIDをデータの先頭につける処理を実装する。addInt32以外の型を追加する。
