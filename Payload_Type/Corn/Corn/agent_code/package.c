#include <windows.h>
#include <string.h>

typedef struct {
    PVOID buffer; // 任意の型のポインタ
    SIZE_T length; // ポインタが指すことができる最大バイト数
} Package, *PPackage;

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



