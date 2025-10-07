#include"pch.h"
#include"console.h"

void console_create(console* instance) {
    // set console window handle
    instance->window_handle = GetConsoleWindow();
    // set console output handle
    instance->std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}