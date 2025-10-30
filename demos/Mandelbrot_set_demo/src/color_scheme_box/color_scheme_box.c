#include"color_scheme_box.h"

void mbs_color_scheme_box_create(mbs_color_scheme_box* color_scheme_box, np_mia_registry* mesh_registry, np_shader* texture_shader) {



    // array vertexu
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
	};

    GLuint attributes[] = {3, 2};

}