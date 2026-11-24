import ipaddress
from Corntranslator.config import *

def checkin(uuid, data) -> dict:
    datajson = {
        "action"          : "checkin",
        "uuid"            : uuid,
        "ips"             : ["127.0.0.1"],
        "os"              : "Windows",
        "user"            : "unknown",
        "host"            : "unknown",
        "pid"             : 0,
        "architecture"    : "x64",
        "domain"          : "unknown",
        "integrity_level" : 2,
        "external_ip"     : "127.0.0.1"
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
        "tasking_size" : taskCount
    }
    
    return datajson

def dispatchAction(data, uuid) -> dict:
    # Mythic strips the UUID before calling the translator, so data[0] is the action byte.
    action = data[0]

    match action:
        case 0x01:
            datajson = checkin(uuid, data)
        case 0x02:
            datajson = get_tasking(uuid, data)
        case _:
            raise ValueError(f"unknown action: 0x{action:02x}")

    return datajson