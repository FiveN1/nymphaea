#include"pch.h"
#include"model_resources.h"

void np_model_resources_create_model_shader(np_shader* shader) {

    const char model_shader_vert[] = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 vert_normal;\n"
    "layout (location = 2) in vec2 vert_tex_coord;\n"

    "uniform mat4 proj_matrix;\n"

    // Output (data struktura se pošle do geometry shaderu)
    "out DATA {\n"
        "vec2 tex_coord;\n"
        "vec3 normal;\n"
        "mat4 proj_matrix;\n"
        "vec3 frag_position;\n"
    "} data_out;\n"

    "void main() {\n"

        "gl_Position = vec4(position, 1.0f);\n"

        "data_out.tex_coord = vert_tex_coord;\n"
        "data_out.normal = vert_normal;\n"
        "data_out.proj_matrix = proj_matrix;\n"
    "}\n";

    const char model_shader_geom[] =
    "#version 460 core\n"

    "layout (triangles) in;\n"
    "layout (triangle_strip, max_vertices = 3) out;\n"

    "out vec2 tex_coord;\n"
    "out vec3 normal;\n"

    "out vec3 light_dir;\n"

    "out mat3 TBN_mat;\n"

    "out vec3 frag_position;\n"

    "in DATA {\n"
        "vec2 tex_coord;\n"
        "vec3 normal;\n"
        "mat4 proj_matrix;\n"
        "vec3 frag_position;\n"
    "} data_in[];\n"

    "void main() {\n"

        "vec3 light_dr = vec3(1.0f, 0.5f, 1.0f);\n"


        //
        // TBN MATRIX 
        //
        // vypočítat předtím než dojde k transformai pozice!!
        // pokud nechceš per vertex tak vypočítat před loopem
        // https://stackoverflow.com/questions/5976349/normal-mapping-and-per-vertex-normal
        //
        "vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;\n"
        "vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;\n"
        "vec2 deltaUV0 = data_in[1].tex_coord - data_in[0].tex_coord;\n"
        "vec2 deltaUV1 = data_in[2].tex_coord - data_in[0].tex_coord;\n"

        "float inv_det = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);\n"

        "vec3 tangent = vec3(inv_det * (deltaUV1.y * edge0 - deltaUV0.y * edge1));\n"
        "vec3 bitangent = vec3(inv_det * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));\n"

        "vec3 T = normalize(tangent);\n"
        "vec3 B = normalize(bitangent);\n"
        "vec3 N = normalize(cross(edge1, edge0));\n"

        "mat3 TBN = mat3(T, B, N);\n"
        "TBN = transpose(TBN);\n"

        "for (int i = 0; i < 3; i++) {"
            "gl_Position = data_in[i].proj_matrix * gl_in[i].gl_Position;\n"
            "tex_coord = data_in[i].tex_coord;\n"
            "normal = data_in[i].normal;\n"
            "light_dir = light_dr;\n"
            "TBN_mat = TBN;\n"
            "frag_position = gl_in[i].gl_Position.xyz;\n"
            "EmitVertex();"
        "}\n"
        "EndPrimitive();\n"
    "}";

    const char model_shader_frag[] =
    "#version 460 core\n"

    "struct directional_light {\n"
        "vec3 direction;\n"
        "vec3 ambient;\n"
        "vec3 diffuse;\n"
        "vec3 specular;\n"
    "};\n"

    "struct point_light {\n"
        "vec3 position;\n"

        "vec3 ambient;\n"
        "vec3 diffuse;\n"
        "vec3 specular;\n"

        "float constant;\n"
        "float linear;\n"
        "float quadratic;\n"
    "};\n"



    "in vec2 tex_coord;\n"
    "in vec3 normal;\n"
    "in vec3 light_dir;\n"

    "in mat3 TBN_mat;\n"

    "in vec3 frag_position;\n"

    "uniform sampler2D diffuse_0;\n"

    "uniform point_light point_light_array[2];\n"

    "out vec4 output_frag_color;\n"


    "vec4 point_light_get(point_light light, vec3 frag_position) {\n"

        "float dist = length(light.position - frag_position);\n"
        // Pro nastavení světla existuje tabulka v dokumentaci na starně 167
        "float con = 1.0f;\n"
        "float lin = 0.022f;\n"
        "float qua = 0.0019f;\n"

        "float attenuation = 1.0f / (con + lin * dist + qua * (dist * dist));\n"

        // Ambient lighting
        "float ambientStrength = 0.05f;\n"
        "vec3 ambient = ambientStrength * light.ambient;\n"

        // Diffuse lighting
        "vec3 norm = normalize(normal);\n"
        "vec3 light_direction = normalize(light.position - frag_position);\n"
        "float diff = max(dot(norm, light_direction), 0.0f);\n"
        "vec3 diffuse = diff * light.diffuse;\n"

        // Konečná barva
        "return vec4((ambient * attenuation + diffuse * attenuation) * vec3(texture(diffuse_0, tex_coord)), 1.0f);\n"
        //return vec4((ambient * attenuation + diffuse * attenuation) * color, 1.0f);
    "}\n"


    "vec4 directional_light_get(vec3 light_direction, vec3 light_color) {\n"
        "vec3 lightcol = vec3(light_color);\n"

        // Ambient lighting
        "float ambientStrength = 0.2f;\n"
        "vec3 ambient = ambientStrength * lightcol;\n"

        // Diffuse lighting
        //vec3 norm = normalize(texture(normal_0, tex_coord).xyz * 2.0f - 1.0f);
        //vec3 norm = normalize(texture(normal_0, tex_coord).xyz * 2.0f - 1.0f) * TBN_mat;
        "vec3 norm = normalize(normal);\n"
        "vec3 lightDir = normalize(light_direction);\n"
        "float diff = max(dot(norm, lightDir), 0.0f);\n"
        "vec3 diffuse = diff * lightcol;\n"

        // Konečná barva
        "return vec4((ambient + diffuse) * vec3(texture(diffuse_0, tex_coord)), 1.0f);\n"
    "}\n"

    "void main() {\n"

        "point_light point_light1 = point_light(vec3(0.0f, 0.0f, 20.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.14f, 0.07f);\n"

        //output_frag_color = texture(normal_0, tex_coord);
        //output_frag_color = vec4(normal, 1.0f);

        "output_frag_color += directional_light_get(light_dir, vec3(0.9f, 0.9f, 1.0f));\n"
        "output_frag_color += point_light_get(point_light1, frag_position);\n"

        //output_frag_color = vec4(normalize(texture(normal_0, tex_coord).xyz * 2.0f - 1.0f) * TBN_mat, 1.0f);

        //output_frag_color = vec4(gl_FragCoord.xyz * 0.001f, 1.0f);


        "for (int i = 0; i < 2; i++) {\n"
            "output_frag_color += point_light_get(point_light_array[i], frag_position);\n"
        "}\n"
    "}";

    np_shader_create_source(shader, model_shader_vert, model_shader_geom, model_shader_frag);
}