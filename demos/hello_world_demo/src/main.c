#include"program.h"

int main() {

    program_data program;
    program_create(&program);
    program_run(&program);
    program_free(&program);

    return 0;
}