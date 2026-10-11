#include <windows.h>
#include "tlv.h"

PBYTE executeShell(
    _In_ PCommand cmd,
    _Out_ PSIZE_T size,
    _Out_ PBOOL success
);