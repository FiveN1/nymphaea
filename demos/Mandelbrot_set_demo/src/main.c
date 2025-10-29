#include"program.h"

// Mandelbrot set demo with the Nymphaea library!
//
// this demo demonstrates the use of compute shaders and buffer objects in Nymphaea.
//
// NOTE: this demo is in developement and may not be as refined!

int main() {
    program_data program;
    program_create(&program);
    program_run(&program);
    program_free(&program);
    return 0;
}