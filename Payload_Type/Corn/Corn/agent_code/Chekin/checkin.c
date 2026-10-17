#include "../include/checkin.h"

// TODO:commandIDをtranlaterと一致させる。

//comandID =
/*
#define CMD_CHECKIN     0x01
#define CMD_GET_TASKING 0x04
#define CMD_RESPONSE    0x05
*/

BYTE checkinID = 0x01;

BOOL sendCheckin(VOID){
    PPackage checkin = newPackage(checkinID, TRUE);

    PParser response = sendAndReceive((PBYTE)checkin->buffer, checkin->length);
    //TODO responseを解析してuuidが返ってくるはずまだ作ってない
    freePackage(checkin);

    if(!response){
        return FALSE;
    }

    freeParser(response);
    return TRUE;    
}