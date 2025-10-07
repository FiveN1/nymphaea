#include"pch.h"
#include"shader_maker.h"

void np_shader_maker_create(np_shader_maker* shader_maker) {
    // velikost každého blocku
    // každý block může mít 1024 - 1 písmen.
    shader_maker->block_size = 1024 * sizeof(char);
    // velikost finálního shader source kodu.
    shader_maker->source_size = 2048 * sizeof(char);
    // vytoříme pole blocků
    np_array_create(&shader_maker->blocks, _NP_SHADER_MAKE_BLOCK_AMOUNT, shader_maker->block_size);
    // allocujem pamět pro každý block
    for (size_t i = 0; i < np_array_get_size(&shader_maker->blocks); i++) {
        // pro každý block nastavíme první char jako terminátor
        ((char*)np_array_get(&shader_maker->blocks, i))[0] = '\0';
    }
    // allocate vertex shader source blocks
    shader_maker->vert_source = (char*)malloc(shader_maker->source_size);
    np_assert(shader_maker->vert_source != NULL, "np_shader_maker: vert malloc error.");
    memset(shader_maker->vert_source, 0, shader_maker->source_size);
    // allocate fragment shader source blocks
    shader_maker->frag_source = (char*)malloc(shader_maker->source_size);
    np_assert(shader_maker->frag_source != NULL, "np_shader_maker: frag malloc error.");
    memset(shader_maker->frag_source, 0, shader_maker->source_size);
}

void np_shader_maker_delete(np_shader_maker* shader_maker) {
    np_array_delete(&shader_maker->blocks);
    // free source
    free(shader_maker->vert_source);
    shader_maker->vert_source = NULL;
    free(shader_maker->frag_source);
    shader_maker->frag_source = NULL;
    //
    shader_maker->block_size = 0;
    shader_maker->source_size = 0;
}

char* np_shader_maker_get_block(np_shader_maker* shader_maker, np_shader_maker_block_type type) {
    char* block = (char*)np_array_get(&shader_maker->blocks, (size_t)type);
    np_assert(block != NULL, "np_shader_maker: invalid type: %i", type); // check
    return block;
}

void np_shader_maker_append(np_shader_maker* shader_maker, np_shader_maker_block_type type, const char* source) {
    char* block = np_shader_maker_get_block(shader_maker, type);
    strcat_s(block, shader_maker->block_size, source);
}

char* np_shader_maker_get_vertex_source(np_shader_maker* shader_maker) {
    // check
    //np_assert(strlen(np_shader_maker_get_block(shader_maker, NP_SHADER_GEN_VERT_POSITION)) != 0, "np_shader_maker: vertex position input not defined!");
    // clear
    memset(shader_maker->vert_source, 0, shader_maker->source_size);
    // build
    // version
    strcat_s(shader_maker->vert_source, shader_maker->source_size, "#version 460 core\n");
    //
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_LAYOUT));
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_UNIFORM));
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_OUTPUT_DEFINE));
    // main
    strcat_s(shader_maker->vert_source, shader_maker->source_size, "void main() {\n");
    // vertex transform - vertex output
    strcat_s(shader_maker->vert_source, shader_maker->source_size, "gl_Position = ");
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_MATRIX_MUL));
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_POSITION));
    // shader variable output
    strcat_s(shader_maker->vert_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_VERT_OUTPUT_SET));
    // main end
    strcat_s(shader_maker->vert_source, shader_maker->source_size, "}\n");
    // vrátit
    return shader_maker->vert_source;
}

char* np_shader_maker_get_fragment_source(np_shader_maker* shader_maker) {
    //
    // pre process blocks
    //
    // pokud output color není nastavený tak nastavit pouze barvu
    if (strlen(np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_FRAG_OUTPUT_COLOR)) == 0) {
        np_shader_maker_append(shader_maker, NP_SHADER_MAKE_FRAG_OUTPUT_COLOR, "vec4(0.0f, 0.0f, 1.0f, 1.0f);\n");
    }

    //
    // build blocks
    //
    // clear
    memset(shader_maker->frag_source, 0, shader_maker->source_size);
    // version
    strcat_s(shader_maker->frag_source, shader_maker->source_size, "#version 460 core\n");
    // input
    strcat_s(shader_maker->frag_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_FRAG_INPUT));
    // uniform
    strcat_s(shader_maker->frag_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_FRAG_UNIFORM));
    // output
    strcat_s(shader_maker->frag_source, shader_maker->source_size, "out vec4 frag_output_color;\n");
    // function implementation
    strcat_s(shader_maker->frag_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_FRAG_FUNCTION));
    // main
    strcat_s(shader_maker->frag_source, shader_maker->source_size, "void main() {\n");
    // ...
    strcat_s(shader_maker->frag_source, shader_maker->source_size, "frag_output_color = ");
    strcat_s(shader_maker->frag_source, shader_maker->source_size, np_shader_maker_get_block(shader_maker, NP_SHADER_MAKE_FRAG_OUTPUT_COLOR));
    // main end
    strcat_s(shader_maker->frag_source, shader_maker->source_size, "}\n");
    // return
    return shader_maker->frag_source;
}