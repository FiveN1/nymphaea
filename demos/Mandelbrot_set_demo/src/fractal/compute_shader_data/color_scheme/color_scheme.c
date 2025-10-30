#include"color_scheme.h"

color_rgb hex_to_rgb(int hex_value) {
    color_rgb color;
    color.r = ((hex_value >> 16) & 0xFF) / 255.0;  // Extract the RR byte
    color.g = ((hex_value >> 8) & 0xFF) / 255.0;   // Extract the GG byte
    color.b = ((hex_value) & 0xFF) / 255.0;        // Extract the BB byte
    return color;
}

void fractal_color_scheme_data_create(fractal_color_scheme_data* fractal_color_scheme_data_instance) {
    // lajolla scheme
    fractal_color_scheme_data_instance->colors[0] = hex_to_rgb(0x1f1e0f);
    fractal_color_scheme_data_instance->colors[1] = hex_to_rgb(0x332312);  
    fractal_color_scheme_data_instance->colors[2] = hex_to_rgb(0x5b2f22); 
    fractal_color_scheme_data_instance->colors[3] = hex_to_rgb(0x91403c);
    fractal_color_scheme_data_instance->colors[4] = hex_to_rgb(0xc94e4a);
    fractal_color_scheme_data_instance->colors[5] = hex_to_rgb(0xe1714d);
    fractal_color_scheme_data_instance->colors[6] = hex_to_rgb(0xe8914f);
    fractal_color_scheme_data_instance->colors[7] = hex_to_rgb(0xefb553);
    fractal_color_scheme_data_instance->colors[8] = hex_to_rgb(0xf7dd79);
    fractal_color_scheme_data_instance->colors[9] = hex_to_rgb(0xfcf9cb);

    // get number of colors in scheme (10)
    fractal_color_scheme_data_instance->color_count = (int)(sizeof(fractal_color_scheme_data_instance->colors) / sizeof(color_rgb));
}