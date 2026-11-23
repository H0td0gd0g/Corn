import json
from Corntranslator.config import *


def dispatchCmd(cmd: str):
    match cmd:
        case 


def responseCheckin(uuid):
    data = success + uuid.encode()
    return data

def responseGetTasking(tasks: dict):
    taskCount = len(tasks)
    data = taskCount.to_bytes(1, "big")
    
    for task in tasks:
        data += task["id"].encode()
        data += len(task["parameters"]).to_bytes(1, "big")
        
        for i in range():
            if i == 0:
                data += 
    