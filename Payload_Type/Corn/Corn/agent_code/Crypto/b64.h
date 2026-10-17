#pragma once
#include <windows.h>

PBYTE encodeBase64(
    _In_  PBYTE   data,
    _In_  SIZE_T  input_size,
    _Out_ PSIZE_T out_size
);

PBYTE decodeBase64(
    _In_  PBYTE   data,
    _In_  SIZE_T  input_size,
    _Out_ PSIZE_T out_size
);