#ifndef NP_SHADER_MAKER_H
#define NP_SHADER_MAKER_H

#include"nymphaea_lib/core/data_structures/array/array.h"

// všechny druhy bloků které jsou použity pro stvoření shader source
// co je block?
// - block je jenom string. tento string je upravován a používán v ruzných částech shaderu.
typedef enum np_shader_maker_block_type {
    //
    // vert enum
    //
    NP_SHADER_MAKE_VERT_LAYOUT = 0,
    NP_SHADER_MAKE_VERT_UNIFORM,
    NP_SHADER_MAKE_VERT_OUTPUT_DEFINE,
    NP_SHADER_MAKE_VERT_MATRIX_MUL,
    NP_SHADER_MAKE_VERT_POSITION,
    NP_SHADER_MAKE_VERT_OUTPUT_SET,
    //
    // geometry enum
    //
    // ...
    //
    // frag enum
    //
    NP_SHADER_MAKE_FRAG_INPUT,
    NP_SHADER_MAKE_FRAG_UNIFORM,
    NP_SHADER_MAKE_FRAG_FUNCTION,

    // blok který drží funkci která vrací hodnotu textury na UV pozici.
    // většinou vypadá jako: 'texture(diffuse_0, tex_coord))'
    NP_SHADER_MAKE_FRAG_OUTPUT_COLOR,
    // nepoužívat. určuje počet definovaných enum
    _NP_SHADER_MAKE_BLOCK_AMOUNT,
} np_shader_maker_block_type;

//
typedef struct np_shader_maker {
    // pole s všemi bloky 
    // všechny bloky budou za sebou v tomto poli. to je možné díky tomu že každý block má stejnou velikost definovanou 'block_size'
    np_array blocks;
    // string konečného vertex source kodu
    char* vert_source;
    // string konečného fragment source kodu
    char* frag_source;
    // maximální velikost blocku
    size_t block_size;
    // velikost finálního source kodu
    size_t source_size;
} np_shader_maker;


void np_shader_maker_create(np_shader_maker* shader_generator);

void np_shader_maker_delete(np_shader_maker* shader_generator);
//
char* np_shader_maker_get_block(np_shader_maker* shader_generator, np_shader_maker_block_type type);
// append string to block
void np_shader_maker_append(np_shader_maker* shader_generator, np_shader_maker_block_type type, const char* source);

char* np_shader_maker_get_vertex_source(np_shader_maker* shader_generator);

char* np_shader_maker_get_fragment_source(np_shader_maker* shader_generator);


// 
//
//

// string struct?


/*
* Problémy
*
* moc pointerů
* - zařadit do nějakého array?
*
* Přesunout do složky s shaderem?
*
*/

/*
* Změny
*
* [09.06.2025] vytvořeno, aby v material_template nebyl takovej bordel...
* - mám v plánu na tomhle pracovat později, zatím budu psát shadery ručně.
* - ale aspon udělám polofunkční verzi.
* [13.06.2025] upravena funkce blocků, kde blocky jsou ted vedle sebe v jednom poli a nemají každý své vlastní pole - jednodušší - lepší.
* - celkem dlouho jsem byl trochu mimo jakoby oslepen a nevěděl co s tímhle projektem dělat.
* - všiml jsem si že nesmím dělat pouze jednu věc a nic jinýho, musím se rozprostřít a dělat co nejvíce věcí.
* - nemůžeš čerpat jenom z jednoho zdroje.
* - když pak vím co dělat tak je vše jednodušší. abys věděl co dělat musíš znát mnohem více věcí kolem daného tématu, 
*   stejně jako spisovatel nemůže čerpat jenom z literatury, aby napsal knížku o rybaření musí vědět něco o rybaření ne?
* - teď musím najít další cestu v tomto mračném lese. na čem bych tak pracoval? v čem vidím potencíl?
* - teď vím jak udělat dobrej shader generator system. tvorbou si to vyjasním.
* - abch si vyjasnil co chci vůbec dělat musím si to zjednodušit. vytvořím rychlý koncept a poté něj upravuji dokud není perfektní.
*   stejně jako kameník musí jendřív udělat hrubý tvar aby mohl dodělat detaily.
*
* - Přejmenováno na np_shader_maker - je to jednodušší a čitelnější a snadno pochopitelné, shader generator lze interpretovat více způsoby.
* - Tento shader maker se stává velmi užitečným, odstranuje tu nejhorší část což je tvorba souborů kvůli shaderu.
* [27.06.2025] přidán NP_SHADER_MAKE_FRAG_FUNCTION block pro definování light funkcí v budoucnu.
* - nevím jestli bych se měl od tohoto projektu oddálit?? -> rád bych zároveň tvořil něco v godot.
*/

#endif NP_SHADER_MAKER_H