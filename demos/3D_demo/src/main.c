#include"program.h"

/*
* 3D demo
*
* in developement...
* 
*
*/

int main() {

    program_data program;
    program_create(&program);
    program_run(&program);
    program_delete(&program);

    return 0;
}