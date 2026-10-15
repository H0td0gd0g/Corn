#include "executeShell.h"

PCmdResult executeShell(
    _In_ PCommand cmd // 実行するコマンド
)
{
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE};
    CreatePipe(&hRead, &hWrite, &sa, 0);


    STARTUPINFOA si = {0};
    si.cb          = sizeof(si);
    si.hStdOutput  = hWrite;
    si.hStdError   = hWrite;
    si.dwFlags     = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi = { 0 };

    char cmdline[512];
    snprintf(cmdline, sizeof(cmdline), "cmd.exe /c %s", cmd->args);

    BOOL success;

    if(!CreateProcessA(
        NULL,
        cmdline,
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    )){
        CloseHandle(hRead);
        CloseHandle(hWrite);
        success = FALSE;
        return NULL;
    }
    // 親側のhWriteを閉じる
    CloseHandle(hWrite);

    PBYTE output = NULL;
    SIZE_T size = 0;
    BYTE buf[4096];
    DWORD bytesRead;

    while (ReadFile(hRead, buf, sizeof(buf), &bytesRead, NULL) && bytesRead > 0)
    {
    // ! メモリ確保　変数 output
    if (size == 0)
    {
        output = (PBYTE)LocalAlloc(LMEM_FIXED, bytesRead);
    }
    else
    {
        output = (PBYTE)LocalReAlloc(output, size + bytesRead, LMEM_MOVEABLE);
    }
    memcpy(output + size, buf, bytesRead);
    size += bytesRead;    
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    success = (exitCode == 0) ? TRUE : FALSE;

    PCmdResult result = (PCmdResult)LocalAlloc(LMEM_FIXED, sizeof(CmdResult));
    result->output = output;
    result->size = size;
    result->success = success;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hRead);

    return result;
}