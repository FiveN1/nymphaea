#include"pch.h"
#include"rect.h"

void np_rect_create(np_rect* rect) {
    np_transform_2d_create(&rect->transform_2d);
    glm_vec2_zero(rect->size);
}

np_transform_2d* np_rect_get_transform_2d(np_rect* rect) {
    return &rect->transform_2d;
}

void np_rect_set_size(np_rect* rect, vec2 size) {
    glm_vec2_copy(size, rect->size);
}
// MOŽNÁ NEPOUŽÍVAT VECTOR !!??
bool np_rect_check_point(np_rect* rect, vec2 point) {
    // PŘIDAT SCALE AND ROTATION SUPPORT
    if (point[0] > rect->transform_2d.position[0] && point[0] < rect->transform_2d.position[0] + rect->size[0] && point[1] < rect->transform_2d.position[1] && point[1] > rect->transform_2d.position[1] - rect->size[1]) return true;
    return false;
}