#include "../include/b64.h"

PBYTE encodeBase64(
    _In_ PBYTE data, 
    _In_ SIZE_T input_size, 
    _Out_ PSIZE_T out_size) //エンコード後のサイズを返す
    {
        const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        // 出力サイズ計算
        *out_size = ((input_size + 2) / 3) * 4;
        // 1グループ = 3バイトずつ切りだす
        // + 2は四捨五入みたいなもん
        // 1グループ(3バイト)は4文字になるというルール

        PBYTE outBuffer = (PBYTE)LocalAlloc(LPTR, *out_size + 1); // null終端
        if (!outBuffer) return NULL;


        PBYTE src = data;
        PBYTE dst = outBuffer;
        SIZE_T remaining = input_size;

        while(remaining > 0)
        {
            // アドレスを一つずつ取得
            BYTE a = (remaining > 0) ? *src++ :0; // src読んでインクリメント
            BYTE b = (remaining > 1) ? *src++ :0;
            BYTE c = (remaining > 2) ? *src++ :0;

            *dst++ = base64_table[a>>2]; // 右に2つビットをずらす
            *dst++ = base64_table[((a & 0x03) << 4) | (b >> 4)];
            *dst++ = (remaining > 1) ? base64_table[((b & 0x0F) << 2) | (c >> 6)] : '=';
            *dst++ = (remaining > 2) ? base64_table[c & 0x3F] : '=';

            remaining -= (remaining >= 3) ? 3 : remaining;
        }
        *dst = '\0';
        return outBuffer;
    }