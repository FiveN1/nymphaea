#ifndef NP_SHADER_DATA_H
#define NP_SHADER_DATA_H

#include"shader_input.h"

#include<nymphaea_lib/core/data_structures/array/array.h>
#include<nymphaea_lib/core/data_structures/dynamic_array/dynamic_array.h>
#include<nymphaea_lib/graphics/mesh/mesh.h>

#define NP_SHADER_DATA_DEBUG

// ## Shader data
// data která využívá shader.
// data budou autamaticky nastavována každý snímek.
typedef struct np_shader_data {
    // pole polí dat která jsou využívána shaderem.
    // některá pole která nejsoou používána budou mít nulovou velikost.
    //
    // np_shader_data.data = [array.[NP_UNIFORM_FLOAT], array.[NP_UNIFORM_VEC2], array.[NP_UNIFORM_VEC3], ...]
    //                       id_0                       id_1                     id_2
    np_array data;
    // odkaz na vstupy shaderu na které se budou bindovat data.
    np_shader_input* shader_input;
} np_shader_data;

// vytvoří shader data. většinou data už budou vytvořena v funkci np_mesh_set_shader() a budou jenom vrácena pro nastavení dat.
// #### Parametry:
// - np_shader_data* shader_data -> instance dat shaderu.
// - np_shader_input* shader_input -> data s vstupy shaderu.
void np_shader_data_create(np_shader_data* shader_data, np_shader_input* shader_input);
// uvolní shader data.
// #### Parametry:
// - np_shader_data* shader_data -> instance dat shaderu.
void np_shader_data_delete(np_shader_data* shader_data);
// #### Parametry:
// vrací odkaz na adresu ve které budou uložena data uniformy.
// POZOR: o maticích se ukádá pouze odkaz.
// - np_shader_data* shader_data -> instance dat shaderu.
// - char* uniform -> název uniformy do které chceme nastavit data.
void* np_shader_data_get(np_shader_data* shader_data, char* uniform);
// draw callback používán pro odesílání uniforem a malování meshe.
void np_shader_data_draw_callback(np_mesh* mesh, np_shader_program shader_program, void* data);

/*
* Problémy
* 
* některé uniformy není potřeba updatovat každý frame.
*
* z draw callbacku by šla vyjmout funkce pouze pro nastavování uniforem, pro větší customizaci.
*/

/*
* Změny
*
* [04.06.2025] vytvořeno za učelem jednoduchého načítání materiálu modelu v np_model.
* - bindování s meshem
* - dynamické compilování shaderů
* - podpora diffuzních textur
* - podpora mat4
* - funkční
* [06.06.2025] předěláno od základů.
* - tvořeno pomocí np_material_template.
* - používá se 2D pole pro všechny data. (velmi effektivní pro pamět).
* - všechny názvy uniforem jsou v jednom poli v template (velmi effektivní).
* - jednoduchost přidávání data typů.
* - ale ted je vše data orientované a jednoduché až na některé systémy.
* - nevýhoda je ta komplexita některých systémů, ale to snad ještě zjednoduším do nějakých funkcí.
* - výhoda méně funkcí.
* [08.06.2025] drobné začištění kodu a poznámek.
* [13.06.2025] přidán typ uniformy vec3.
* - Pořád jsem zaseklej na tomto problému s 'materiál' sytémem.
*   jako vše má tento material systém své výhody a nevýhody.
*   Není moc flexibilní, jsou je dobrý pro rychlou tvorbu.
*   -> proto je dobré že tady fungují jako nadstavba nad mým předchozím 'material' systémem, který je absolutně jednoduchý
*      a skvělý. 
*   Tak kde chci tento systém použít?
*   -> při tvorbě her.
*   Chci ho ale používat třeba při renderování textu?
*   -> Ano protože je jednoduchý a snadno čitelný.
*   -> Ne protože při dalších změnách tohoto systému se vše může posrat.
*   Je tedy něco mezi tím?
*   -> Teď me napadlo že při renderování textu můžu použít mesh generator systém a ten základní shader data system.
*      Výhody v tomto případě: Nemusí se načítat soubory. shader generátor systém asi zůstane jak je jelikož je skvělý.
*           Taky je to rychlé a snadno čitelné a stabilní.
*      Nevýhody: musím používat nějakou custom shader callback funkci pro každý shader.
*   Všimni si jak jsem se najednou stal produktivní, Je to tím že je 22:00 a v tuto dobu jsem nejvíc kreativní z nejakého důvodu?
*   Nebo prostě jsem si sedl a vyjasnil jsem si problém.
*   -> Je dobré si napsat výhody a nevýhody.
* [16.06.2025] přejmenováno na np_shader_data
* [25.06.2025] funkční, rozděleno do funkcí pro snadnou čitelnost a přidáváná podpory dalších uniforem v budoucnu.
* [26.06.2025] přidány poznámky.
* [27.06.2025] přidány debug funkce. STABILNÍ
*
*/

#endif NP_SHADER_DATA_H