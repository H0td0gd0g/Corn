#include "commandHandler.h"

PCmdResult dispatchCommand(PCommand cmd){
    switch (cmd->commandType[0]){
        default:
            return NULL;
        case 0x01:
            PCmdResult result = executeCommand(cmd);
            // ! メモリ解放　(executeShell.c)
            // TODO タスクループで解放させる
            // LocalFree(result);
            // LocalFree(result->output);
            return result;
    }
}