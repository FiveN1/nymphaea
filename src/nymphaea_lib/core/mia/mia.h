#ifndef NP_MIA_H
#define NP_MIA_H

#include"nymphaea_lib/core/data_structures/id_array/id_array.h"

// mia.h by FiveN

/*
* ## Multi Indexed Array (MIA)
*
* An indexed array wich holds other indexed arrays. (np_id_array)
* Database for any components you like to store!
*
* #### Why store data in MIA?
* Main use is for fast iteration over every element in the registry.
* To not fragment the memory with all of the small data stored everywhere. it is better to have same data types close together, if you for example plan on iterating over them.
* And you dont need to keep track of variables that you dont plan to use.
*
* #### Why use ID array (Indexed Array)? 
* Because the location of data is preserved even after modifying other data in the array.
* This is important because MIA gives pointers to data in the array wich need to stay in a same place.
* ID array allows for fast data modification!
* This is both efficient and easy to use!
*
* #### MIA & ECS
* The diffrence between MIA & ECS is that most of ECS stuff like Entities and systems arise naturaly in MIA.
* Entities arise from links.
* And Systems are user defined.
* MIA is overall faster, simpler and more flexible.
* This is what im going for in Nymphaea.
*
* ## Registry
* A registry is an array (np_id_arry to be specific) that holds any data of set type.
* MIA allows to have multiple registries of same data type.
* Registries are not dynamic. (to not mess with set pointers) so you have to set correct registry size you want to use.
* Maximum amount of registries is set by 'registry_count' variable in the 'np_mia_create' function
* All data in a registry will be deleted upon 'np_mia_registry_delete' or when deleting MIA with 'np_mia_delete'.
*
* ## Data
* Data is stored in registries of the registered data type.
* You can easily loop for every data in a registry.
* All data in a registry will be deleted when calling 'np_mia_registry_delete'
*
* ## Order
* The order in wich data has been added is preserved. 
* By using 'np_mia_get_by_id' function you will get the data in the correct order.
* Order is preserved  even after removing data from a registry.
*
* ## Link
* Entity is defined by the links between components (data) in MIA. Like links between neurons in your brain create your consciousness.
* This alows components to be shared between each other.
* 
* ## Related Functions
* - np_mia_create
* - np_mia_delete
* - np_mia_registry_create
* - np_mia_registry_delete
* - np_mia_registry_get_size
* - np_mia_alloc
* - np_mia_free
* - np_mia_get_by_id
*/
typedef np_id_array np_mia;
/*
* ## MIA Registry
*
* An indexed array holding only one type of specific data.
* every registry can have its own size.
*
* ## Related Functions
* - np_mia_registry_create
* - np_mia_registry_delete
* - np_mia_registry_get_size
*/
typedef np_id_array np_mia_registry;

// create MIA and set how many types of components (registries) it can hold
void np_mia_create(np_mia* mia, size_t registry_count);
// clear MIA data
void np_mia_delete(np_mia* mia);
// register data type to MIA
// returns pointer to created registry. 
// NOTE: the registry pointer never changes (unless its deleted)
// because of this feature it cant be resized!
np_mia_registry* np_mia_registry_create(np_mia* mia, size_t size, size_t type_size);
// deregister data type from MIA
void np_mia_registry_delete(np_mia* mia, np_mia_registry* registry);
// get currend number of elements stored in a registry
size_t np_mia_registry_get_size(np_mia_registry* registry);
// allocate memory for data with registry 'type_size' in a mia registry and get a pointer to that data
void* np_mia_alloc(np_mia_registry* registry);
// remove data in mia registry
void np_mia_free(np_mia_registry* registry, void* data);
// get data from mia registry
void* np_mia_get(np_mia_registry* registry, size_t id);
// get data in registry via id. id goes from 0 to current size of registry
void* np_mia_get_by_id(np_mia_registry* registry, size_t id);

//
// UNDER CONSTRUCTION
//

// data budou v mia a odkazy v editoru...
// odkazy v array?
// + jednoduše se určí velikost registru
// - neznáš jména


/*
* ## Update log:
*
* #### 04.08.2024
* Created basic ECS implementation
*
* #### 05.08.2024
* Added all ECS functions
*
* #### 05.08.2024 - 22.09.2024
* Experimented with diffrent architectures.
*
* #### 22.09.2024
* Created the MIA architecture
* Translated comments to english
*
* #### 05.11.2024
* Finnished MIA core architecture after experimenting with a non-MIA approach.
*
* #### 09.11.2024
* Removed the need for passing mia to every functions by defining registries with a pointer rather than an id.
* This simplified the whole system even more and removed the mess. also removed 'np_mia_registry_get' function since there is no need for that
*
* #### 07.06.2025
* přidána funkce np_mia_get()
*
*/

#endif NP_MIA_H