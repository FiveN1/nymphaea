#ifndef NP_SHADER_INPUT_H
#define NP_SHADER_INPUT_H

#include"nymphaea_lib/core/data_structures/dynamic_array/dynamic_array.h"
#include"nymphaea_lib/core/data_structures/array/array.h"
#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"

#include"../shader_maker/shader_maker.h"

// #define NP_SHADER_INPUT_DEBUG

// maximální delka názvu uniformy
#define NP_UNIFORM_MAX_NAME_LENGTH 64
// druhy podporovaných uniforem
enum np_uniform_type {
    NP_UNIFORM_FLOAT = 0,
    NP_UNIFORM_VEC2,
    NP_UNIFORM_VEC3,
    NP_UNIFORM_VEC4,
    NP_UNIFORM_MAT3,
    NP_UNIFORM_MAT4,
    NP_UNIFORM_SAMPLER2D,
    NP_UNIFORM_TYPE_AMOUNT
} np_uniform_type;

// ## Shader input
// spojené s shader program v shaderu.
typedef struct np_shader_input {
    // pole všech názvů uniforem v shaderu.
    // názvy jsou seřazené podle typů a jsou po sobě.
    // musí mít ale stejnou velikost, tedy maximální velikost definovanou NP_UNIFORM_MAX_NAME_LENGTH.
    np_dynamic_array uniforms;
    // sekce v poli uniforem.
    // index je stejný jako typ uniformy, a hodnotu představuje konec sekce v poli uniforem
    // výhodou je malá velikost a jednoduchá a ryhclá iterace.
    np_array uniform_sections;
} np_shader_input;

// získeá všehny uniformy / vstupy a uloží je v shader_input.
// #### Parametry:
// - np_shader_input* shader_input -> instance shader inputu do kterého se zapíšou data o vstupu shaderu.
// - np_shader_program shader_program -> shader_program ze kterého chceme získat data.
void np_shader_input_create(np_shader_input* shader_input, np_shader_program shader_program);
// uvolí data o vstupech v shaderu.
// POZOR: předem se musí také uvolnit všechna np_shader_data která závií na tomto vstupu!
// #### Parametry:
// - - np_shader_input* shader_input -> instance shader inputu.
void np_shader_input_delete(np_shader_input* shader_input);
// vytiskne všechny uniformy a jejich sekce do konzole.
// #### Parametry:
// - - np_shader_input* shader_input -> instance shader inputu.
void np_shader_input_print(np_shader_input* shader_input);

/*
* Design sytému
*
*             16bytes          16bytes          16bytes
* uniforms : [proj_matrix\0....texture1\0.......texture2\0.......]
*                              A                                A
*                              |                                +--- konec sekce s názvy pro NP_MATERIAL_DIFFUSE_TEXTURE.
*                              +------------------------------------ konec sekce s názvy pro NP_MATERIAL_MAT4_PTR.
*
* každá uniforma má v tomto příkladě maximální délku 16. v reálu má délku definovanou NP_MATERIAL_UNIFORM_NAME_BUFFER_SIZE.
* 
* názvy jsou seřazeny tak aby jejich typy šly postupně za sebou jak sjou definované v np_material_data_type.
* - takže nejdčív jsou NP_MATERIAL_MAT4_PTR a pak NP_MATERIAL_DIFFUSE_TEXTURE atd...
*
* ========
*
* uniform_type_sections : [1, 3, 3]
*                          A  A  A
*                          |  |  +--- ...prázdný typ
*                          |  +------ NP_MATERIAL_DIFFUSE_TEXTURE.
*                          +--------- NP_MATERIAL_MAT4_PTR.
*
* toto pole má stejný počet jako počet definovaných enumu v np_material_data_type - 1.
* kde každý index náleží k jednomu typu.
*
* hodnoty určují konec sekce v poli uniforem.
* - takže první hodnota nám říká že typ NP_MATERIAL_MAT4_PTR končí na indexu 1,
*   nebo že sekce s NP_MATERIAL_DIFFUSE_TEXTURE končí na indexu 3.
*   a také že třetí typ nemá žádnou uniformu jelikož končí kde začíná.
*
* ========
*
* S tímto designem můžeme určovat pořadí processu uniforem.
* - třeba pořadí násobení matic.
*
* podle mě velmi effektivní a jednoduchý design který:
* - nezabírá mnoho místa.
* - nefragmentuje moc pamět.
* - je dynamický.
* - a snadno se do něj mohou implementovat nové data typy.
*/

/*
* Změny
*
* [05.06.2025] vytvořeno - z důvodu nemožnosti ukládání různých dat při stejném shaderu v staré implementaci materiálu.
* [06.06.2025] předěláno, obsahuje pouze shader, a 2 pole (uniformy, a section index)
* - má to samé výhody. až na takzvanou "bezpečnost"
* [07.06.2025] začištění kodu a drobné upravy v poznámkách (diagram designu).
* - také odstraněn strcpy() jelikož se data stejně kopírují. jen si nejsem jistý s bezpečností mé metody...
* - přidána delete funkce.
* [08.06.2025] drobné začištění kodu a přidány debug funkce.
* [09.06.2025] design a implementace uplně nového shader generation systému, který by měl být mnohem jednodušší a flexibilnější.
* [10.06.2025] přenesení shader gen systému do vlastní skupiny.
* [13.06.2025] přidán typ uniformy vec3. odstraněna nastavitelná velikost struct pomocí define, max velikost je ted v struct - lepší čitelnost.
* [16.06.2025] přejmenováno na np_shader_bind_point.
*   tady jsme byl uplně ztracenej,
* [23.06.2025] přejmenováno na np_shader_input.
*   pořád stracenej i po týdení pauze. (stačila pauza pouze na den nebo dva).
* [24.06.2025] moc se tady nestalo. jen jsem si to trochu ujasnil a zkopíroval kod z np_material_template.
* [25.06.2025] funkční jak jsem chtěl. teď zbývá začistit kod aby byl snadno čitelný.
* [26.06.2025] přidány poznámky. STABILNÍ
*
*
*/

#endif NP_SHADER_INPUT_H