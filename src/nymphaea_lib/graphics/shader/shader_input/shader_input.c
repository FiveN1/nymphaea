#include"pch.h"
#include"shader_input.h"

//
// local definice
//

// vytiskne všechny uniformy a jejich sekce do konzole.
void np_shader_input_print(np_shader_input* shader_input);

//
// implementace
//

void np_shader_input_create(np_shader_input* shader_input) {
    // vytvoříme všechny potřebná pole, která budou obsahovat data o vstupech. (pole s názvy uniforem je dynamické protože je třeba funkce insert())
    np_dynamic_array_create(&shader_input->uniforms, sizeof(char) * NP_UNIFORM_MAX_NAME_LENGTH);
    
    // vytvoříme pole posledních indexů sekcí.
    np_array_create(&shader_input->uniform_sections, (size_t)NP_UNIFORM_TYPE_AMOUNT, sizeof(GLuint));
    
    // debug
    #ifdef NP_SHADER_INPUT_DEBUG
    np_debug_print_aqua("np_shader_input: calling create");
    np_shader_input_print(shader_input);
    #endif
}

void np_shader_input_delete(np_shader_input* shader_input) {
    np_dynamic_array_delete(&shader_input->uniforms);
    np_array_delete(&shader_input->uniform_sections);
}

void np_shader_input_add_uniform(np_shader_input* shader_input, enum np_uniform_type type, const char* name) {
    // check zda je typ uniformy validní
    if (type >= NP_UNIFORM_TYPE_AMOUNT) {
        np_debug_print_red("np_shader_input: invalid uniform type: %llu, uniform name: %s", (size_t)type, name);
        return;
    }

    // pokud je název uniformy delší nebo stejný jako velikost bufferu tak vrátíme.
    // POZNÁMKA: musí se tam vejít terminátor charakter! -> proto se nesmí rovnat.
    if (strlen(name) >= NP_UNIFORM_MAX_NAME_LENGTH) {
        np_debug_print_red("np_shader_input: uniform name over set limit of: %llu\nunable to add uniform of name: \"%s\"", NP_UNIFORM_MAX_NAME_LENGTH, name);
        return;
    }

    // id v poli názvů uniforem, určuje poslední id sekce typu
    GLuint id = *(GLuint*)np_array_get(&shader_input->uniform_sections, (size_t)type);

    // na tuto pozici vložíme název
    np_dynamic_array_insert(&shader_input->uniforms, id, name);

    // upravíme indexy sekcí
    for (size_t i = (size_t)type; i < np_array_get_size(&shader_input->uniform_sections); i++) {
        ((GLuint*)np_array_data(&shader_input->uniform_sections))[i]++;
    }
}


//
// local impllementace
//

void np_shader_input_print(np_shader_input* shader_input) {
    np_debug_print_aqua("np_shader_input at: %p", shader_input);
    // unfiformy
    np_debug_print("\tuniforms:");
    for (size_t i = 0; i < np_dynamic_array_get_size(&shader_input->uniforms); i++) {
        np_debug_print("\t\t%s", (char*)np_dynamic_array_get(&shader_input->uniforms, i));
    }
    // velikosti sekcí
    np_debug_print("\tsection sizes:");
    GLuint section_begin = 0;
    for (size_t i = 0; i < np_array_get_size(&shader_input->uniform_sections); i++) {
        GLuint section_end = *(GLuint*)np_array_get(&shader_input->uniform_sections, i);
        np_debug_print("\t\t%u", section_end - section_begin);
        section_begin = section_end;
    }
}



/*
* Implementace automatického načítání uniforem.
* Odstraněno jelikož je to moc náročné na udržbu a není moc flexibilní.
*

// převďe OpenGL uniform enum na np uniformu
// použito pouze v 'np_shader_input_load_uniforms()'
enum np_uniform_type np_get_gl_uniform_type(GLenum uniform_type);

// získeá všehny uniformy / vstupy a uloží je v shader_input.
void np_shader_input_load_uniforms(np_shader_input* shader_input, np_shader_program shader_program) {
    // počet uniforem v shaderu
    GLint num_of_uniforms;
    glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &num_of_uniforms);

    // vytvoříme všechny potřebná pole, která budou obsahovat data o vstupech. (pole s názvy uniforem je dynamické protože je třeba funkce insert())
    np_dynamic_array_resize(&shader_input->uniforms, (size_t)num_of_uniforms);

    // každá uniforma se přidá do array
    for (GLuint i = 0; i < (GLuint)num_of_uniforms; i++) {
        // hodnoty uniformy
        char name[NP_UNIFORM_MAX_NAME_LENGTH];
        GLenum gl_type;
        GLint size;
        GLsizei length;

        // získáme data o uniformě
        glGetActiveUniform(shader_program, i, NP_UNIFORM_MAX_NAME_LENGTH, &length, &size, &gl_type, name);
    
        // přidáme uniformu
        np_shader_input_add_uniform(shader_input, np_get_gl_uniform_type(gl_type), name);
    }
}

enum np_uniform_type np_get_gl_uniform_type(GLenum uniform_type) {
    switch (uniform_type) {
        case GL_FLOAT: return NP_UNIFORM_FLOAT;
        case GL_FLOAT_VEC2: return NP_UNIFORM_VEC2;
        case GL_FLOAT_VEC3: return NP_UNIFORM_VEC3;
        case GL_FLOAT_VEC4: return NP_UNIFORM_VEC4;
        case GL_FLOAT_MAT3: return NP_UNIFORM_MAT3;
        case GL_FLOAT_MAT4: return NP_UNIFORM_MAT4;
        case GL_SAMPLER_2D: return NP_UNIFORM_SAMPLER2D; // NP_UNIFORM_SAMPLER2D_DSA jako default není
    }
    // debug
    #ifdef NP_SHADER_INPUT_DEBUG
    np_debug_print_red("np_shader_input: type: %i, not implemented", uniform_type);
    #endif
    return GL_FLOAT;
}
*/