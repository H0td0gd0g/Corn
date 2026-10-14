#include "../include/commandHandler.h"

BOOL dispatchCommand(PCommand cmd){
    switch (cmd->commandID){
        case 0x01:
            PcmdResult result = executeCommand();
            // ! メモリ解放　(executeShell.c)
            // TODO タスクループで解放させる
            // LocalFree(result);
            return result;
    }
}