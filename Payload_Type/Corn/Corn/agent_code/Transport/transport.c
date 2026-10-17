// トランスポート層のhttp通信を担当
#include <windows.h>
#include <string.h>

#include "../include/parser.h"
#include "../include/package.h"

#include "../include/transport.h"

// sendPackage関数のwinhttpへの依存
#include <winhttp.h> // winhttpはワイド文字(unicode)のみサポートしているので注意が必要
#pragma comment (lib, "winhttp.lib")



int getStatusCode(HINTERNET hRequest){
    DWORD statusCode = 0;
    DWORD statusSize = sizeof(DWORD);
    if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusSize, WINHTTP_NO_HEADER_INDEX))
		return 0;
	return statusCode;
}


PParser makeHTTPRequest(PBYTE data, SIZE_T size)
{
    //WinHttpOpen
    HINTERNET hSession = NULL;

    //WinHttpConnect
    HINTERNET hConnect = NULL;

    //WinHttpOpenRequest
    HINTERNET hRequest = NULL;

    LPSTR encoded = NULL;

    PParser parser = NULL;

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
        goto cleanup;
    }

    hConnect = WinHttpConnect(
        hSession,
        corn_config.HostName,
        corn_config.HttpPort,
        0
    );

    if (hConnect == NULL)
    {
        goto cleanup;
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

    if (hRequest == NULL){
        goto cleanup;
    }

    // TODO:b64に変換する処理を入れる
    LPSTR encoded = encodeBase64(data, size);

    BOOL request_result = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        encoded,
        (DWORD)strlen(encoded),
        (DWORD)strlen(encoded),
        0
    );

    if (request_result == FALSE){
        goto cleanup;
    }

    // 自動的に待機してくれる関数
    if (!WinHttpReceiveResponse(hRequest,NULL))
    {
        goto cleanup;
    }

    DWORD statusCode = getStatusCode(hRequest);

    if (statusCode != 200){
        goto cleanup;
    }

    //配列名はすでにアドレス
    BYTE tmpBuffer[1024] = {0};
    PVOID responseBuffer = NULL;

    // 一回でダウンロードしたサイズ
    DWORD downloadSize = 0;
    // レスポンス全体の長さ
    DWORD responseSize = 0;
    //読み取ることができるサイズ(0になるとエラーか終了)
    DWORD dwSize = 0;

    do
    {


        if(!WinHttpQueryDataAvailable(hRequest,&dwSize)){
            goto cleanup;
        }

        if(dwSize == 0) break;
        //ローカルで動く関数なのでネットワークトラフィックは増えない
        if (!WinHttpReadData(
            hRequest,
            tmpBuffer,
            dwSize,
            &downloadSize
        )){
            goto cleanup;
        }

        responseSize += downloadSize;

        if (!responseBuffer){
            responseBuffer = LocalAlloc(LPTR, responseSize);
        } else {
            // ヌル終端のため+1
            responseBuffer = LocalReAlloc(
                responseBuffer,
                responseSize,
                LMEM_MOVEABLE | LMEM_ZEROINIT
            );
        }

        memcpy((PBYTE)responseBuffer + (responseSize - downloadSize), tmpBuffer, downloadSize);
        memset(tmpBuffer, 0, 1024);


    }while(dwSize > 0);

    // ヌル終端のため+1
    responseBuffer = LocalReAlloc(
                responseBuffer,
                responseSize + 1,
                LMEM_MOVEABLE | LMEM_ZEROINIT
            );

    parser = newParser((PBYTE)responseBuffer, responseSize);

cleanup:
    if (encoded) LocalFree(encoded);
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    // httpの結果が返ってくる
    return parser;
}

// 抽象化レイヤー、どの通信にするのか選べる
PParser sendAndReceive(PBYTE data, SIZE_T size)
{
    #ifdef HTTP_TRANSPORT
        return makeHTTPRequest(data, size);
    #endif
    // ここにほかの通信プロトコルを配置することで動作する。

    return NULL;
}