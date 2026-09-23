#pragma once

#ifndef PARSER_H
#define PARSER_H
#include <windows.h>

typedef struct
{
    PBYTE original;
    PBYTE buffer; // メモリを読む位置
    SIZE_T length; // 読むメモリの長さ
    SIZE_T originalLength;
} Parser, *PParser;


UINT32 getUInt32(PParser parser);
PBYTE  getBytes(PParser parser, PSIZE_T size);
PParser newParser(PBYTE buffer, SIZE_T size);
VOID freeParser(PParser parser);

#endif
