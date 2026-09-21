#include <windows.h>
#include "../include/parser.h"
#include "../include/package.h"

// http通信 Mythicはbase64を期待しているためbase64で送る関数
PParser convertBase64(PPackage package)
{
    //convert base64
    // TODO:後で自分で実装した関数に置き換える　crypt32.dllへの依存が増えるため
    DWORD needBytes = 0;
    
    // 返される文字列を保持する単に割り当てる必要がある文字列を計算する。
    CryptBinaryToStringA(
        (const BYTE*)package->buffer,
        (DWORD)package->length,
        CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
        NULL,
        &needBytes
    );
    // メモリの確保
    LPSTR outBuf = (LPSTR)LocalAlloc(
        LPTR,
        needBytes
    );

    CryptBinaryToStringA(
        (const BYTE*)package->buffer,
        (DWORD)package->length,
        CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
        outBuf,
        &needBytes
    );
}