#ifndef NP_GUI_RESOURCES_H
#define NP_GUI_RESOURCES_H

#include"nymphaea_lib/graphics/font/font.h"
#include"nymphaea_lib/graphics/objects/shader_program/shader_program.h"

#include"nymphaea_lib/graphics/shader/shader.h"

/*
* GUI Resources
*
* Data která jsou zabudovaná v samotném programu.
* tady je to potřeba jelikož se jedná o default data knihovny které nebudou někde na disku (mimo .exe)
* proto je lepší je mít zabudované tady.
*
* je tu ProggyClean font, který je dobrý v tom že není tak velký.
* jenom je velký ten byte array co tam je napsán v source souboru. možná by bylo lepší uložit v stringu?
*
*/

void np_gui_resources_set_color_shader(np_shader_program* np_shader_program);

void np_gui_resources_set_font_proggy_clean(np_font* font);


void np_gui_resources_set_text_shader(np_shader* shader);

/* Změny
* [08.10.2025] vytvořeno, špatný postup, originálně měly být všechny data uloženy v struct.
* [09.10.2025] změněno tak aby gui elementy byly nastavovány přes funkce. což je lepší protože lifetime resourcu je jenom v funkci.
* 
*/

#endif NP_GUI_RESOURCES_H