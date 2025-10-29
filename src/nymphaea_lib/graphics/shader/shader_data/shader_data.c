#include"pch.h"
#include"shader_data.h"
// všechny data typy které mohou být použité materiálem.
#include<nymphaea_lib/graphics/objects/texture_2d/texture_2d.h>
#include"nymphaea_lib/graphics/objects/dsa_texture_2d/dsa_texture_2d.h"
#include<nymphaea_lib/graphics/transform/transform_3d/transform_3d.h>

//
// local definice
//

// vrátí velikost dat uniformy.
size_t get_uniform_data_type_size(enum np_uniform_type uniform_type);
// pošle data do uvedené uniformy v shaderu na GPU.
void set_uniform_data(GLint uniform_location, char* uniform_name, void* uniform_data, enum np_uniform_type type, np_shader_program shader_program);

//
// implementace
//

void np_shader_data_create(np_shader_data* shader_data, np_shader_input* shader_input) {
    // odkaz na vstupy
    shader_data->shader_input = shader_input;
    // vytvoříme pole které bude obsahovat pole s daty.
    // pokud je pole jednoho typu nulové (typ není v shaderu využívan) vytvoří se nullové pole s NULL blockem.
    np_array_create(&shader_data->data, NP_UNIFORM_TYPE_AMOUNT, sizeof(np_array));
    GLuint section_begin = 0;
    for (size_t section_id = 0; section_id < np_array_get_size(&shader_data->data); section_id++) {
        // začátek a konec sekce v poli názvů uniforem
        // podle toho získáme velikost sekce kteroou použijeme pro vytvoření pole s daty uniforem v sekci
        GLuint section_end = *(GLuint*)np_array_get(&shader_data->shader_input->uniform_sections, section_id); 
        GLuint section_size = section_end - section_begin;
        // pro každý data typ určíme jeho velikost aby šlo pro něj udělat array
        size_t data_size = get_uniform_data_type_size(section_id);
        // po zjištění všech potřebných dat vytvoříme pole s daty uniforem pro danou sekci (typ)
        np_array_create((np_array*)np_array_get(&shader_data->data, section_id), (size_t)section_size, data_size);
        section_begin = section_end;
    }
    // debug
    #ifdef NP_SHADER_DATA_DEBUG
    np_debug_print_green("np_shader_data: created instance at: %p", shader_data);
    #endif
}

void np_shader_data_delete(np_shader_data* shader_data) {
    for (size_t i = 0; i < np_array_get_size(&shader_data->data); i++) {
        np_array_delete((np_array*)np_array_get(&shader_data->data, i));
    }
    np_array_delete(&shader_data->data);
    shader_data->shader_input = NULL;
    // debug
    #ifdef NP_SHADER_DATA_DEBUG
    np_debug_print_yellow("np_shader_data: deleted instance at: %p", shader_data);
    #endif
}

void* np_shader_data_get(np_shader_data* shader_data, char* uniform) {
    // získáme index (ID) uniformy v poli všech uniforem
    size_t id = 0;
    for (; id < np_dynamic_array_get_size(&shader_data->shader_input->uniforms); id++) {
        char* existing_uniform = (char*)np_dynamic_array_get(&shader_data->shader_input->uniforms, id);
        if (strcmp(existing_uniform, uniform) == 0) {
            break;
        }
    }
    // zkontrolujem zda uniforma byla nalezena, pokud ne tak vrací null.
    if (id == np_dynamic_array_get_size(&shader_data->shader_input->uniforms)) {
        // debug
        #ifdef NP_SHADER_DATA_DEBUG
        np_debug_print_yellow("np_shader_data: uniform with name \"%s\" not found.", uniform);
        #endif
        return NULL;
    }
    // zjistíme k kterému typu uniforma patří (ID) - to použijem pro získání pole s daty daného typu
    GLuint type = 0;
    GLuint section_begin = 0;
    for (; type < np_array_get_size(&shader_data->shader_input->uniform_sections); type++) {
        GLuint section_end = *(GLuint*)np_array_get(&shader_data->shader_input->uniform_sections, type);
        if (id < (size_t)section_end) {
            break;
        }
        section_begin = section_end;
    }
    // získáme pole s daty kteé obsahuje data k hledané uniformě
    np_array* uniform_data = (np_array*)np_array_get(&shader_data->data, (size_t)type);
    // vrátíme pozici dat uniformy v poli
    return np_array_get(uniform_data, id - section_begin);
}

void np_shader_data_draw_callback(np_mesh* mesh, np_shader_program shader_program, void* data) {
    // bindujem shader
    np_shader_program_use(shader_program);
    // shader_data jsou data uložená meshem
    // takže můžeme rovnou přeměnit na pointer
    np_shader_data* shader_data = (np_shader_data*)data;
    // index názvu uniformy, který je uložen v mesh template.
    // (všechny názvy uniforem jsou pohromadě v jednom poli, což je effektivní)
    size_t uniform_name_id = 0;
    // pro každá data získáme jeho název uniformy a lokaci a poté nastavíme dta na GPU pomocí gl funkcí.
    for (size_t type_id = 0; type_id < np_array_get_size(&shader_data->data); type_id++) {
        // získáme pole přiřazené k data typu definovaném enum.
        np_array* uniform_data_array = (np_array*)np_array_get(&shader_data->data, type_id);
        // z každého pole získáme data která spojíme s určenou uniformou v shaderu.
        // velmi jednoduché, malé ztráty.
        // může se stát že pole bude prázdné, takže se nic nepošle.
        for (size_t uniform_data_id = 0; uniform_data_id < np_array_get_size(uniform_data_array); uniform_data_id++, uniform_name_id++) {
            char* uniform_name = (char*)np_dynamic_array_get(&shader_data->shader_input->uniforms, uniform_name_id);
            void* uniform_data = np_array_get(uniform_data_array, uniform_data_id);
            // lokace uniformy v shaderu
            GLint uniform_location = glGetUniformLocation(shader_program, uniform_name);
            // pro každý typ uniformy použijeme jinou funkci
            set_uniform_data(uniform_location, uniform_name, uniform_data, (enum np_uniform_type)type_id, shader_program);
        }
    }
    // namalujem mesh s shaderem a daty
    np_mesh_draw(mesh);
}

//
// local implementace
//

size_t get_uniform_data_type_size(enum np_uniform_type uniform_type) {
    switch (uniform_type) {
        case NP_UNIFORM_FLOAT: return sizeof(GLfloat);
        case NP_UNIFORM_VEC2: return sizeof(vec2);
        case NP_UNIFORM_VEC3: return sizeof(vec3);
        case NP_UNIFORM_VEC4: return sizeof(vec3);
        case NP_UNIFORM_MAT3: return sizeof(mat3*);
        case NP_UNIFORM_MAT4: return sizeof(mat4*);
        // (28.10.2025) sampler rozdělen na 2 typy jelikož tu jsou 2 způsoby bindování
        case NP_UNIFORM_SAMPLER2D: return sizeof(GLuint);
        case NP_UNIFORM_SAMPLER2D_DSA: return sizeof(GLuint);
    }
    np_debug_print_yellow("np_shader_data: material data type id_%u, not implemented", (GLuint)uniform_type);
    return (size_t)0;
}

void set_uniform_data(GLint uniform_location, char* uniform_name, void* uniform_data, enum np_uniform_type type, np_shader_program shader_program) {
     switch (type) {
        case NP_UNIFORM_FLOAT:
            glUniform1f(uniform_location, *(GLfloat*)uniform_data);
            return;
        case NP_UNIFORM_VEC2:
            glUniform2fv(uniform_location, 1, *(vec2*)uniform_data);
            return;
        case NP_UNIFORM_VEC3: 
            glUniform3fv(uniform_location, 1, *(vec3*)uniform_data);
            return;
        case NP_UNIFORM_MAT3:
            if (*(mat4**)uniform_data == NULL) {
                np_debug_print_yellow("np_shader_data: uniform mat3 \"%s\" null value!", uniform_name);
                return;
            }
            glUniformMatrix3fv(uniform_location, 1, GL_FALSE, (*(mat3**)uniform_data)[0][0]);
            return;
        case NP_UNIFORM_MAT4:
            if (*(mat4**)uniform_data == NULL) {
                np_debug_print_yellow("np_shader_data: uniform mat4 \"%s\" null value!", uniform_name);
                return;
            }
            glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (*(mat4**)uniform_data)[0][0]);
            return;
        case NP_UNIFORM_SAMPLER2D: 
            np_texture_2d_bind(*(np_texture_2d*)uniform_data);
            return;
        case NP_UNIFORM_SAMPLER2D_DSA: 
            np_dsa_texture_2d_bind_sampler_unit(*(np_dsa_texture_2d*)uniform_data, shader_program, 0, uniform_name);
            return;
    }
    np_debug_print_yellow("np_shader_data: type: %u not supported", (GLuint)type);
}