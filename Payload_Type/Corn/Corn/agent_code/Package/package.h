#pragma once
#include <windows.h>

#ifndef PACKAGE_H
#define PACKAGE_H

// パッケージの大きさと実際の中身を伝える。
typedef struct {
    PBYTE buffer;
    SIZE_T size; // bufferのサイズ
} Package, *PPackage;

BOOL addBytes(PPackage package, PBYTE data, SIZE_T length);
BOOL addByte(PPackage package, BYTE value);
BOOL addUInt32(PPackage package, UINT32 value);

PPackage newPackage(BOOL init);
VOID freePackage(PPackage package);
#endif