# Nymphaea
*(repo under construction!)*

A C Library for creating C applications.
Data oriented, low level, flexible library.

## About
- Nymphaea is data oriented.
- Nymphaea also does not use any global variables (almost) so you can easily understand the flow of your programs data.
- Nymphaea thies to be as simple and abstract as possible. so you can youe its functions in many cases.

## Hello World Example:
This simple example will create a window with the text `Hello World!` in the middle.
You can find this demo in `demos/HelloWorld_damo`.

<img src="https://github.com/FiveN1/nymphaea/blob/main/demos/HelloWorld_demo/res/hello_world_example_result.png" alt="Hello World example result" width="512"/>

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

This approach is very abstract and you can see the similarities of the touring machine emerging. Where the program data is the tape, that is iterated upon in the run function.

## How to use?
to use this library in your project you have two options: pre-compile the whole library or use it as is.

#### Use as linked library:
> [!NOTE]
> This requieres you to use premake in your project.

Simply include the `nymphaea.lua` in your premake5.lua file and link it by adding `"nymphaea"` to your `links {}`.
To use the headers of this library you will need to run `build.bat` and type `gen_include` to create the `include/` directory that you will need to include in your project.
You will also need to include the include files of this library dependencies (will automate this later).

#### Use as compiled library:
run `build.bat` and type `compile`.
- this will compile the library into `nymphaea.lib` file found in the newly generated `bin/` folder.
then type 'gen_include' also in 'build.bat'.
- this will create an include directory that you can paste in your included files folder of your project.
