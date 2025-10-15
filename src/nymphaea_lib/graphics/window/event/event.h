#ifndef NP_EVENT_H
#define NP_EVENT_H

/*
* event.h
*
* event is just some piece of data that will be passed to a on_event function
* anything can be an event, for example: key, mouse, window, game-tick, game-frame, or some in-game action.
*
* updates:
* 16.09.2024 written
* 21.10.2024 added key press, release, repeat events
*
*/

// event type enums
typedef enum np_event_type {
    // key events
    NP_KEY_PRESS_EVENT,
    NP_KEY_RELEASE_EVENT,
    NP_KEY_REPEAT_EVENT,
    // mouse events
    NP_MOUSE_MOVE_EVENT,
    NP_MOUSE_BUTTON_EVENT,
    NP_MOUSE_SCROLL_EVENT,
    // window events
    NP_WINDOW_CLOSE_EVENT,
    NP_WINDOW_RESIZE_EVENT,
    NP_WINDOW_MOVE_EVENT
} np_event_type;

//
// Event type structs
//

/*
* the structs below are the diffrent types of event data.
* you can get them based on the event 'type'
*/

// data about key when pressed
typedef struct np_event_key_press {
    int key;
} np_event_key_press;

// data about key when released
typedef struct np_event_key_release {
    int key;
} np_event_key_release;

// data about key when repeated
typedef struct np_event_key_repeat {
    int key;
} np_event_key_repeat;

// data about new cursor position
typedef struct np_event_mouse_move {
    double xpos;
    double ypos;
} np_event_mouse_move;

// data about mouse button press/release action
typedef struct np_event_mouse_button {
    int button;
    int action;
    int mods;
} np_event_mouse_button;

// data about mouse scroll action
typedef struct np_event_mouse_scroll {
    double xoffset;
    double yoffset;
} np_event_mouse_scroll;

// data about new window size
typedef struct np_event_window_resize {
    int width;
    int height;
} np_event_window_resize;

// data about new window position
typedef struct np_event_window_move {
    int xpos;
    int ypos;
} np_event_window_move;

//
// Event
//

/*
* an event is a piece of information holding the data of a event type and the type id
* event data is stored in a union of diffrent event types
*/
typedef struct np_event {
    // event type is one of the enums from 'np_event_types'
    np_event_type type;
    // union of event diffrent event types so an event only stores one at a time
    // unions are awesome!
    union {
        // data about key when pressed
        np_event_key_press key_press_event;
        // data about key when released
        np_event_key_release key_release_event;
        // data about key when repeated
        np_event_key_repeat key_repeat_event;
        // data about new cursor position
        np_event_mouse_move mouse_move_event;
        // data about mouse button press/release action
        np_event_mouse_button mouse_button_event;
        // data about mouse scroll action
        np_event_mouse_scroll mouse_scroll_event;
        // data about new window size
        np_event_window_resize window_resize_event;
        // data about new window position
        np_event_window_move window_move_event;
    };
} np_event;

#endif NP_EVENT_H