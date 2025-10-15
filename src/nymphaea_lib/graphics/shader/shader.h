#ifndef NP_SHADER_H
#define NP_SHADER_H

#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"
#include"shader_input/shader_input.h"
#include"shader_data/shader_data.h"

#include<nymphaea_lib/graphics/mesh/mesh.h>

// #### Shader
// abstrakce od manualního nastavování uniforem.
// jednoduše získá všechny uniformy z source kodu a automaticky je updatuje.
//
// shader se potom nabinduje na mesh pomocí 'np_mesh_set_shader()'.
// funkce pak vrátí jenom data která je třeba nastavit pro automatické posílání dat do shaderu.
typedef struct np_shader {
    np_shader_program shader_program;
    np_shader_input shader_input;
} np_shader;

// vytvoř shader z souborů s source kody.
// #### Parametry:
// - np_shader* shader -> instance shaderu.
// - const char* vs_filename -> cesta k souboru s vertex source.
// - const char* gs_filename -> cesta k souboru s geometry source.
// - const char* fs_filename -> cesta k souboru s fragment source.
void np_shader_create_file(np_shader* shader, const char* vs_filename, const char* gs_filename, const char* fs_filename);

// vytvoř shader přímo z string s source kodem.
// #### Parametry:
// - np_shader* shader -> instance shaderu.
// - const char* vs -> vertex source.
// - const char* gs -> geometry source.
// - const char* fs -> fragment source.
void np_shader_create_source(np_shader* shader, const char* vs, const char* gs, const char* fs);

// uvolni data shaderu.
// POZOR: všehcny np_shader_data vytvořena z tohoto shaderu musí být předem odstraněna jelikož drží odkaz na np_shader_input.
// #### Parametry:
// - np_shader* shader -> instance shaderu.
void np_shader_delete(np_shader* shader);

// nastav shader meshe.
// vrací np_shader_data* pomocí kterého pak lze nastavit data uniforem pomocí funkce np_shader_data_get()
// #### Parametry:
// - np_mesh* mesh -> mesh bude využívat shader.
// - np_shader* shader -> instance shaderu užita k shadovaní meshe.
np_shader_data* np_mesh_set_shader(np_mesh* mesh, np_shader* shader);

/*
* ## Změny
*
* #### 24.06.2025
* vytvořeno pro abstrakci od sraní s shadery
*
* #### 25.06.2025
* implementace, plně funkční a snadno použitelné. (snad už finální podoba)
*
* #### 26.06.2025
* přidána delete funkce a poznámky. také přidána funkce pro načítání shaderu z source (string). STABILNÍ
*
*/
#endif NP_SHADER_H