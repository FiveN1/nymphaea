#ifndef NP_DELTA_TIME_H
#define NP_DELTA_TIME_H

// nastav předchozí / minulý čas snímku aby se mohl použít k získání delta_time pomocí funkce np_delta_time_get()
// vrací pouze konkrétní čas pomocí np_get_time()
double np_delta_time_set_previous_time();
// získeá delta_time neboli rozdíl času od minulého snímku.
// delta_time je v milisekundách a je velmi přesný.
// #### Parametry:
// double* previous_time -> pointer na hodnotu minulého času nastavenou funkcí np_delta_time_set_previous_time()
double np_delta_time_get(double* previous_time);
// převede delta time na fps
// #### Parametry:
// double delta_time -> hodnota delta_time
unsigned int np_delta_time_to_fps(double delta_time);

/*
* Změny
*
* [12.06.2025] vytvořeno aby šlo snadno získat delta time. - k tomu je ale třeba vědět předchozí čas takže je potřeba struct.
*
*/

#endif NP_DELTA_TIME_H