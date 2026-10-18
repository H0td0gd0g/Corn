#pragma once

#ifndef CORN_H
#define CORN_H

#include <windows.h>

typedef struct 
{
    CHAR AgentID[36]; // コンパイル時に設定されるuuid どのバイナリか判定する。
    CHAR callBackuuid[36]; // チェックイン後に返されるuuid
    WCHAR HostName;
    DWORD HttpPort;
    WCHAR EndPoint;
    WCHAR HttpMethod;
    WCHAR UserAgent;
    BOOL IsSSL;
    BOOL IsProxyEnabled;
    WCHAR ProxyURL;
    UINT32 SleepTime;
} CONFIG_CORN, *PCONFIG_CORN;

extern CONFIG_CORN corn_config;

#endif