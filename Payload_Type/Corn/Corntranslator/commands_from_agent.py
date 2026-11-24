import ipaddress
from Corntranslator.config import *

def checkin(uuid, data) -> dict:
    datajson = {
        "action" : "checkin",
        "uuid" : uuid
    }
    
    return datajson


def get_tasking(uuid, data) -> dict:
    
    taskCount = data[1]
    
    fixedHeader = 38
    valuelen = 0
    
    for i in range(taskCount):
        taskUUID = data[fixedHeader + valuelen + 1 : fixedHeader + valuelen + 1 + 36]
    # todo ここの処理まだかけてない
    datajson = {
        "action" : "get_tasking",
        "tasking_size" : numTasks
    }
    
    return datajson

def dispatchAction(data) -> dict:
    uuid = data[:36].decode()
    data = data[36:]
    
    action = data[0]
    
    match action:
        case 0x01:
            datajson = checkin(uuid, data)
        case 0x02:
            datajson = get_tasking(uuid, data)
    
    return datajson