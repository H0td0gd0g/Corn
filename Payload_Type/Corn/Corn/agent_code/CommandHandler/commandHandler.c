#include "commandHandler.h"

PCmdResult dispatchCommand(PCommand cmd){
    switch (cmd->commandType[0]){
        case 0x01:
            PCmdResult result = setupCallbackuuid(cmd);
        case 0x02:
            PCmdResult result = executeCommand(cmd);
            // ! メモリ解放　(executeShell.c)
            // TODO タスクループで解放させる
            // LocalFree(result);
            // LocalFree(result->output);
            return result;
    }
}