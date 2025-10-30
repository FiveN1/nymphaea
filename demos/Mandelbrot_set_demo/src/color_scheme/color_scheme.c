#include"color_scheme.h"

color_rgb hex_to_rgb(int hex_value) {
    color_rgb color;
    color.r = ((hex_value >> 16) & 0xFF) / 255.0;  // Extract the RR byte
    color.g = ((hex_value >> 8) & 0xFF) / 255.0;   // Extract the GG byte
    color.b = ((hex_value) & 0xFF) / 255.0;        // Extract the BB byte
    return color;
}