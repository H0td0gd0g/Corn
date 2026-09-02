#include <windows.h>

typedef struct 
{
    PCHAR AgentID; //uuid
    PWCHAR HostName;
    DWORD HttpPort;
    PWCHAR EndPoint;
    PWCHAR HttpMethod;
    PWCHAR UserAgent;
    BOOL IsSSL;
    BOOL IsProxyEnabled;
    PWCHAR ProxyURL;
    UINT32 SleepTime;
} CONFIG_CORN, *PCONFIG_CORN;

extern CONFIG_CORN corn_config;

