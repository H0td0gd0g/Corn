#pragma once

#include <windows.h>
#include "commandResult.h"
#include "tlv.h"
#include <stdio.h>

PCmdResult executeShell(
    _In_ PCommand cmd // 実行するコマンド
);

