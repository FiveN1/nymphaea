#ifndef NP_SCENE_H
#define NP_SCENE_H

#include<nymphaea_lib/core/mia/mia.h>

#include<nymphaea_lib/graphics/camera/camera_3d/camera_3d.h>

#include<nymphaea_lib/graphics/shader/shader.h>
#include<nymphaea_lib/graphics/shader/shader_maker/shader_maker.h>

//
// !! UNDER DEVELOPEMENT !!
//

// #### Scene
// v scene se nachází componenty které jsou závislé na scéně.
//
typedef struct np_scene {
    np_mia mia;
    np_mia_registry* mesh_registry;

    np_mia_registry* tr3_registry;
    
    np_mia_registry* point_light_registry;
    // directional light(s)?

    np_mia_registry* model_registry;

    // camera...
    // spíše view matrix?
    np_camera_3d* main_camera;

    // light...

} np_scene;

void np_scene_create(np_scene* scene);

void np_scene_delete(np_scene* scene);

void np_scene_draw(np_scene* scene);

// možná v material_template.h??
//void np_scene_set_material_template(np_scene* scene, np_material_template* material_template);

void np_scene_shader_make(np_scene* scene, np_shader_maker* shader_maker);

void np_get_shader_uniforms(const char* vertex_source, size_t vertex_source_size);


void np_scene_set_shader_data_lights(np_scene* scene, np_shader_data* shader_data);

/*
* Tohle už není moc abstraktní. použije se pro tvoření mesh scén.
*
* Cíl scény:
* - postarat se o renderování meshů a tvorbu meshových prostorů.
* - světla, kamery, atd...
* - scéna je jako kontext pro meshové objekty malované rasterizací.
*
* flags? - draw wirefame flag...
*
* Nějaká scene material funkce?
* 
*
*/

/*
* ## Změny
*
* #### 10.06.2025 
* vytvořeno - aby bylo možné podávat data o světě do materiálu pomocí nějakého kontejneru.
*
* #### 13.06.2025
* přidány nějaké zakladní funkce.
*
* #### 14.06.2025
* přemýšlím jak udělat flexibilní uniform send system...
*
* #### 11.10.2025
* menší začištění.
*/


#endif NP_SCENE_H