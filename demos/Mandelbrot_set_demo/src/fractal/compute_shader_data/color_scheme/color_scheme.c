#include"color_scheme.h"

color_rgb hex_to_rgb(int hex_value) {
    color_rgb color;
    color.r = ((hex_value >> 16) & 0xFF) / 255.0;  // Extract the RR byte
    color.g = ((hex_value >> 8) & 0xFF) / 255.0;   // Extract the GG byte
    color.b = ((hex_value) & 0xFF) / 255.0;        // Extract the BB byte
    return color;
}

void fractal_color_scheme_data_create(fractal_color_scheme_data* fractal_color_scheme_data_instance) {
    // lajolla color scheme
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
    // acton color scheme
    /*
    fractal_color_scheme_data_instance->colors[0] = hex_to_rgb(0x270d3e);
    fractal_color_scheme_data_instance->colors[1] = hex_to_rgb(0x3f2e5e);  
    fractal_color_scheme_data_instance->colors[2] = hex_to_rgb(0x554d7a); 
    fractal_color_scheme_data_instance->colors[3] = hex_to_rgb(0x72628c);
    fractal_color_scheme_data_instance->colors[4] = hex_to_rgb(0x96658e);
    fractal_color_scheme_data_instance->colors[5] = hex_to_rgb(0xbe6892);
    fractal_color_scheme_data_instance->colors[6] = hex_to_rgb(0xd584a9);
    fractal_color_scheme_data_instance->colors[7] = hex_to_rgb(0xe0a9c9);
    fractal_color_scheme_data_instance->colors[8] = hex_to_rgb(0xe8cee3);
    fractal_color_scheme_data_instance->colors[9] = hex_to_rgb(0xf1e9f4);
    */
    // navia color scheme
    /*
    fractal_color_scheme_data_instance->colors[0] = hex_to_rgb(0x0b1627);
    fractal_color_scheme_data_instance->colors[1] = hex_to_rgb(0x16345c);  
    fractal_color_scheme_data_instance->colors[2] = hex_to_rgb(0x19598c); 
    fractal_color_scheme_data_instance->colors[3] = hex_to_rgb(0x29728e);
    fractal_color_scheme_data_instance->colors[4] = hex_to_rgb(0x3a8285);
    fractal_color_scheme_data_instance->colors[5] = hex_to_rgb(0x4b9379);
    fractal_color_scheme_data_instance->colors[6] = hex_to_rgb(0x66aa6a);
    fractal_color_scheme_data_instance->colors[7] = hex_to_rgb(0x98ca6e);
    fractal_color_scheme_data_instance->colors[8] = hex_to_rgb(0xd9e5a6);
    fractal_color_scheme_data_instance->colors[9] = hex_to_rgb(0xfcf5d9);
    */
    // turku color scheme
    /*
    fractal_color_scheme_data_instance->colors[0] = hex_to_rgb(0x080605);
    fractal_color_scheme_data_instance->colors[1] = hex_to_rgb(0x25231f);  
    fractal_color_scheme_data_instance->colors[2] = hex_to_rgb(0x444235); 
    fractal_color_scheme_data_instance->colors[3] = hex_to_rgb(0x605e43);
    fractal_color_scheme_data_instance->colors[4] = hex_to_rgb(0x7e7a4f);
    fractal_color_scheme_data_instance->colors[5] = hex_to_rgb(0xa99763);
    fractal_color_scheme_data_instance->colors[6] = hex_to_rgb(0xd0a47a);
    fractal_color_scheme_data_instance->colors[7] = hex_to_rgb(0xebad97);
    fractal_color_scheme_data_instance->colors[8] = hex_to_rgb(0xf9c6c1);
    fractal_color_scheme_data_instance->colors[9] = hex_to_rgb(0xfde4e4);
    */

    // get number of colors in scheme (10)
    fractal_color_scheme_data_instance->color_count = (int)(sizeof(fractal_color_scheme_data_instance->colors) / sizeof(color_rgb));
}