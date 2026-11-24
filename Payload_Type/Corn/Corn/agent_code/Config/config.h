#pragma once

// Builder replaces PLACEHOLDER values before compilation.
// IDE syntax errors on these lines are expected and harmless.

#define initUUID "%UUID%"

// === http section ===
#define hostname    L"%HOSTNAME%"
#define httpport    %PORT%
#define endpoint    L"/%ENDPOINT%"
#define httpmethod  L"%METHOD%"
#define useragent   L"%USERAGENT%"
#define isssl       %SSL%
#define proxyenabled %PROXYENABLED%
#define proxyurl    L"%PROXYURL%"
#define sleeptime   %SLEEPTIME%