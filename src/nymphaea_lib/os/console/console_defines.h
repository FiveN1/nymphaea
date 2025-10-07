#ifndef CONSOLE_DEFINES_H
#define CONSOLE_DEFINES_H

// in new file because it is used in log.h wich is included in the pre-compiled header
// this then results in self inclusion of console.h and log.h
// i think that it is much cleaner to have it seporated into two files...
// where one has the functionalities of the conole and the other macros

// color codes

#define CONCOL_BLACK    0x0000
#define CONCOL_BLUE     0x0001
#define CONCOL_GREEN    0x0002
#define CONCOL_AQUA     0x0003
#define CONCOL_RED      0x0004
#define CONCOL_PURPLE   0x0005
#define CONCOL_YELLOW   0x0006
#define CONCOL_WHITE    0x0007

#endif CONSOLE_DEFINES_H