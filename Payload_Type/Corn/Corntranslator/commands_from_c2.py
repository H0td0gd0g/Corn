import json
from Corntranslator.config import *


def dispatchCmd(cmd: str) -> bytes:
    cmd_magic = b""
    match cmd:
        case "execute_shell":
            cmd_magic = b"\x54"
    return cmd_magic


def responseCheckin(uuid):
    data = success + uuid.encode()
    return data

def responseGetTasking(tasks: dict):
    taskCount = len(tasks) 
    data = taskCount.to_bytes(1, "big") # task count
    
    for task in tasks:
        data += task["id"].encode()  # task uuid
        
        cmd_magic = dispatchCmd(task["command"]) # commandType
        data += cmd_magic
        
        
        param_obj = json.loads(task["parameters"])
        
        argCount = len(param_obj)
        data += argCount.to_bytes(1, "big")
        
        for key, val in param_obj.items():
            val_bytes = str(val).encode()
            val_len = len(val_bytes)
            data += val_len.to_bytes(4, "big")
            data += val_bytes
    
    return data