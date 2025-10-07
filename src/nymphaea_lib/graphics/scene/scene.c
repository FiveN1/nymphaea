#include"pch.h"
#include"scene.h"

#include<nymphaea_lib/graphics/mesh/mesh.h>
#include<nymphaea_lib/graphics/transform/transform_3d/transform_3d.h>
#include"model/model.h"

void np_scene_create(np_scene* scene) {
    np_mia_create(&scene->mia, 16);
    // registry mimo nebo v scéně?
    scene->mesh_registry = np_mia_registry_create(&scene->mia, 1024, sizeof(np_mesh));
    scene->tr3_registry = np_mia_registry_create(&scene->mia, 1024, sizeof(np_tr3));
    scene->model_registry = np_mia_registry_create(&scene->mia, 64, sizeof(np_model));
    scene->main_camera = NULL;
}

void np_scene_draw(np_scene* scene) {
    // draw meshes
    for (size_t i = 0; i < np_mia_registry_get_size(scene->mesh_registry); i++) {
        np_mesh* mesh = (np_mesh*)np_mia_get_by_id(scene->mesh_registry, i);
        np_mesh_call_draw(mesh);
    }
}

//void np_scene_set_material_template(np_scene* scene, np_material_template* material_template) {
    // pro každé světlo
    
    
    // jak udělat dobrý automatický sender?
    // co chceme vůbec posílat?

    // co třeba tak automaticky určit uniformu z shader source kodu?
    // + jednodušší pro uživatele
    // + méně chyb
    // + nemusíš se starat o tolik věcí
    // - těžká implementace (tohle bude super)
    // - hodně typů.
//}

void np_scene_shader_make(np_scene* scene, np_shader_maker* shader_maker) {

    // nastavit uniformy světel...


}

void np_get_shader_uniforms(const char* vertex_source, size_t vertex_source_size) {
    // check zda se najde slovo "uniform"
    // pokud ano tak získáme typ a jméno.
    // to uložíme do pole.
    



}

void np_scene_set_shader_data_lights(np_scene* scene, np_shader_data* shader_data) {

    // název array...
    // počet sevětel.
    for (GLuint i = 0; i < 2; i++) {

    }



}