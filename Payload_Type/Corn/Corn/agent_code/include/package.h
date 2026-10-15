#include <windows.h>

#pragma once

#ifndef PACKAGE_H
#define PACKAGE_H

// パッケージの大きさと実際の中身を伝える。
typedef struct {
    PVOID buffer; // 任意の型のポインタ
    SIZE_T length; // ポインタが指すことができる最大バイト数
} Package, *PPackage;

BOOL addBytes(PPackage package, PBYTE data, SIZE_T length);
BOOL addByte(PPackage package, BYTE value);
BOOL addUInt32(PPackage package, UINT32 value);

PPackage newPackage(BYTE taskiUUID, BOOL init);
VOID freePackage(PPackage package);
#endif