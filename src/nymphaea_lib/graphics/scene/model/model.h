#ifndef NP_MODEL_H
#define NP_MODEL_H

// assimp library
#include<assimp/config.h>
#include<assimp/cimport.h> // c varianta "Import.hpp"
#include<assimp/scene.h>
#include<assimp/postprocess.h>
// core include
#include<nymphaea_lib/core/mia/mia.h>
#include<nymphaea_lib/core/data_structures/array/array.h>
#include<nymphaea_lib/core/file/file/file.h>
// graphics include
#include<nymphaea_lib/graphics/mesh/mesh.h>
#include<nymphaea_lib/graphics/program/shader_program/shader.h>
#include<nymphaea_lib/graphics/scene/scene.h>
#include<nymphaea_lib/graphics/transform/transform_3d/transform_3d.h>
// ostatní
#include<nymphaea_lib/graphics/objects/texture_2d/texture_2d.h>
#include<nymphaea_lib/graphics/camera/camera_3d/camera_3d.h>


#define NP_DEBUG_MODEL

/*
* ## Model
* load any model using the assimp library.
*
*
*/
typedef struct np_model {
    // pole s id na meshe uložené někde registru
    np_id_array meshes; // np_array?
    // jelikož je effektivnější aby všechny meshe byly v jednom array, načtené meshe se uloží do jednoho společného pole
    np_mia_registry* mesh_registry;
    // všechny materiály používány modelem.
    // jejich pozice je stejná jako pozice assimp materiálu při načítání.
    np_array shaders;
    // array všech textur použitých modelem
    np_dynamic_array textures; // textures
    // model transform
    np_tr3* transform;

    //np_scene* scene;
} np_model;

// načte jakýkoliv model do scény.
// #### Parameters
// - np_scene* scene -> instance scény do které bude model načten.
// - const char* filename -> cesta k souboru modelu.
np_model* np_model_create(np_scene* scene, const char* filename);

void np_model_delete(np_model* model);

np_tr3* np_model_get_tr3(np_model* model);

// vytvořit scene třídu?
// + bude držet kamery, světla, skyboxy atd...
// + bude passnuta do modelu
// model bude zavislej na scéně.
// což asi kdykoli bude protože kde jinde by se použil model?


// model se bude vracet z create funkce stejne jako np_gui_text_create
// proč je ve scéně?
// -> aby jes šlo shadovat světly ze scény...
// stejně bude skoro vždy pod scenou tak je to asi jedno...
// ale jinak by šla vytvořit custom funkce proto aby nebyl pod scénou.

// ruzné funkce pro nastavení shaderu?
// -> scene shader callback, custom shader callback?


/*
* Problémy
*
* Všechny meshe mají stejný layout. (optimalozace)
*
* může se stát že vznikne víc material template než je potřeba. (optimalozace)
*
* neuplná delete funkce
*
* nastavení custom shaderů není podprované.
* https://stackoverflow.com/questions/59721374/loading-models-and-their-materials-in-assimp-robustly-with-opengl
* asi nejdřív přidat funkci pro získání meshe.
*
*/

/*
* Reference
*
* assimp:                           https://github.com/assimp/assimp
* assimp documentation:             https://assimp-docs.readthedocs.io/en/latest/
* c compile:                        https://stackoverflow.com/questions/39602131/how-to-link-c-program-with-assimp-mingw-w64, https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html
* compile assimp as static library: https://stackoverflow.com/questions/75698181/how-to-build-assimp-as-a-static-lib-mt
* sestavení pomocí CMake:           https://www.youtube.com/watch?v=XpBGwZNyUh0&t=4s
*
* Pro linkování statické knihovny (.lib) je třeba v CMake vypnout všechny IMPORT/EXPORT definice jelikož to jde pouze v (.dll)
*
* Podle tohoto tutoriálu se mi to podařilo rozjet : https://stackoverflow.com/questions/45928202/assimp-model-loading-library-install-linking-troubles
* Poznámka: Také jsem musel zaškrtnout 'USE_STATIC_CRT' aby to fungovalo.
*
* Pro Android. V budoucnu se možná bude hodit: https://stackoverflow.com/questions/49941203/assimp-with-android-port-error-import-obj-file
*
* Sponza model: https://www.intel.com/content/www/us/en/developer/topic-technology/graphics-research/samples.html
*
*/

/*
* Změny
*
* [31.05.2025] vytvořeno
* [02.06.2025] assimp knihovna funguje (je v .lib a c). také nějaká základy načítání modelu.
* [03.06.2025] funkční načítání meshe. 
* [04.06.2025] přidány materiály, funkční načítání textur.
* [06.06.2025] přidán nový material system, napůl funkční implementace, neoptimalizované
* [07.06.2025] přidán texture system kde vššchny textury budou v jednom poli aby se nemuseli načítat vícekrát.
* - uděláno čitelné, čisté.
* - spraveny transformace meshů.
* - přidány debug print funkce.
* - přidána delete funkce
* [10.06.2025] přidáno osvětlení, pokus o implementaci normal map. - mapa se načítá ale v problém s shaderem
* [11.06.2025] normal mapy ted plně fungují.
* [12.06.2025] odebrané normal mapy protože by byla těžká implementace a je mi to k hovnu, winding order preprocess přidán.
* [13.06.2025] model ted bude závislý na np_scene. Jednodušší ale méně flexibilní. stejně mimo scénu nebude používán.
* [26.06.2025] předěláno pro nový systém np_shader (starý np_material, np_material_template byl smazán)
* [11.10.2025] default_model_shader zabudován do source kodu. odstraněn np_model_material struct.
*/

#endif NP_MODEL_H