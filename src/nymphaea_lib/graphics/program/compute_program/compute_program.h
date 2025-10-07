#ifndef NP_COMPUTE_PROGRAM_H
#define NP_COMPUTE_PROGRAM_H

#include<glad/glad.h>

/*
* ## Compute Program
*
* A program that runs on the GPU using all of the advantages of parallel processing.
*
* ### Related Functions
* - np_compute_program_create
* - np_compute_program_load
* - np_compute_program_delete
* - np_compute_program_use
*/
typedef GLuint np_compute_program;

// create a compute program with its source code
void np_compute_program_create(np_compute_program* compute_program, const char* compute_shader_source);
// create a compute program with its source code stored in a file
void np_compute_program_load(np_compute_program* compute_program, const char* compute_shader_source_dir);
// delete compute program data
void np_compute_program_delete(np_compute_program* compute_program);
// run the compute program on the GPU
void np_compute_program_use(np_compute_program compute_program, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);


//void np_compute_program_get_max_work_groups();


#endif NP_COMPUTE_PROGRAM_H