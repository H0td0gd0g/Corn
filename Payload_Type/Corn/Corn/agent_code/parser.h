#include <windows.h>

#pragma once

#ifndef PARSER_H
#define PARSER_H

typedef struct
{
    PBYTE original;
    PBYTE buffer; // メモリを読む位置
    SIZE_T length; // 読むメモリの長さ
    SIZE_T originalLength;
} Parser, *PParser;

#endif