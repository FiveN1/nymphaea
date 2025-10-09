# Nymphaea

Nymphaea is C a library designed for creating programmable art.

Nymphaea is powerful yet easy to understand.

Use this library as you like!

<img style="float: right;" src="https://github.com/FiveN1/nymphaea/blob/main/res/lion_demo_screenshot1.png" alt="Nymphaea 3D screenshot" width="512"/>

## 🌸About
- Nymphaea makes it easy to write C programs.
- Nymphaea is data oriented.
- Nymphaea also does not use any global variables (almost) so you can easily understand the flow of your programs data.
- Nymphaea is simple yet powerful.
- Most of the comments are in Czech since im from Czechia (sorry!)

## 🌸Hello World Example
This simple example will create a window with the text `Hello World!` in the middle.
You can check out the demo [here at demos/hello_world_demo](demos/hello_world_demo)

<img src="https://github.com/FiveN1/nymphaea/blob/main/demos/hello_world_demo/res/hello_world_example_result.png" alt="Hello World example result" width="512"/>

```c
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<nymphaea_lib/graphics/graphics.h>

// data of this demo
typedef struct program_data {
    bool is_running;
    np_window window;
    np_gui_context gui_context;
} program_data;

// set program data
void program_create(program_data* program) {
    // program will run by default
    program->is_running = true;

    // initilize the renderer (GLFW)
    np_renderer_create();

    // create window
    np_window_create(&program->window, program, 800, 800, "Hello world example!");
    np_window_bind_event_callback(&program->window, &program_on_event); // also bind the window callback so we can close the window!

    // create GUI
    np_gui_create(&program->gui_context);
    np_gui_enable(&program->gui_context, NP_GUI_TEXT, 8);

    // add text
    np_gui_text_create(&program->gui_context, "Hello World!");
}

// iterate on program data
void program_run(program_data* program) {
    // main loop
    while(program->is_running) {

        // update (draw) GUI
        np_gui_update(&program->gui_context, &program->window);

        // update window
        np_window_update(&program->window);
    }

}

// free program data
void program_free(program_data* program) {
    // free GUI data
    np_gui_delete(&program->gui_context);

    // free window data
    np_window_delete(&program->window);

    // delete renderer
    np_renderer_delete();
}

// process program data on event
void program_on_event(np_event event, void* data) {
    // cast input data to program
    program_data* program = (program_data*)data;

    // close window
    if (event.type == NP_WINDOW_CLOSE_EVENT) {
        program->is_running = false;
        np_window_close(&program->window);
    }
}

int main() {

    program_data program;
    program_create(&program);
    program_run(&program);
    program_free(&program);

    return 0;
}

```

You can see the application/program is split into 3 stages.
- **Create.** In this stage sets the data of the program.
- **Run.** In here the data is iterated upon.
- **Delete.** here the data of the program is released and the program is discarded.

This approach is very simple and you can see some similarities to the touring machine. Where the program data is the tape, that is set in the create function, and is iterated upon in the run function.

## 🌸How to use
You can just link this library to your project using premake or you can build it and include the compiled files.

### Use as linked library:
> [!NOTE]
> This requieres you to use premake in your project.

Simply include the `nymphaea.lua` in your premake5.lua file and link it by adding `"nymphaea"` to your `links {}`.
To use the header files of this library (and its dependencies) you will need to run `build.bat` and type `include` to create the `include/` directory that you will need to include in your project.

### Use as compiled library:
run `build.bat` and type `compile_d` (or `compile_r` for release configuration) to build this library.

> [!NOTE]
> theese commands use vs2022 project files for building!
> use any of the premake commands (type `help` to get a list of them) to generate the project files you want to use for building this library.

then you shoud find the compiled library in `bin/*configuration-system-architecture*/nymphaea.lib`.

type `include` (still in `build.bat`) to create the `include/` directory that you will need to include in your project.

## 🌸More?
This library will be in developement for a long time, since i will use it in my future projects.

Contact me if you have any suggestions for this library!

