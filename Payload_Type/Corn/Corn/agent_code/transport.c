// トランスポート層のhttp通信を担当
#include <windows.h>
#include "package.h"
#include "parser.h"


// 抽象化レイヤー、どの通信にするのか選べる
PParser sendAndRecive(PBYTE data, SIZE_T size)
{
    #ifdef HTTP_TRANSPORT
        return makeHTTPRequest(data, size);
    #endif

    //return nullptr;
}

// 
PParser sendPackage(PPackage package)
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

makeHttpRequest(){

}