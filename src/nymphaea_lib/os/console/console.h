#ifndef NP_CONSOLE_H
#define NP_CONSOLE_H

#include"pch.h"
//#include"console_defines.h"

typedef struct console {
    HWND window_handle;
    HANDLE std_handle; // console handle
} console;

// create console
void console_create(console* instance);


#define CONCOL_BLACK    0x0000
#define CONCOL_BLUE     0x0001
#define CONCOL_GREEN    0x0002
#define CONCOL_AQUA     0x0003
#define CONCOL_RED      0x0004
#define CONCOL_PURPLE   0x0005
#define CONCOL_YELLOW   0x0006
#define CONCOL_WHITE    0x0007

#endif NP_CONSOLE_H