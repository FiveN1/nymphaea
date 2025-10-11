#include"pch.h"
#include"model.h"
// embeded resources
#include"resources/model_resources.h"

//
// local definice
//

// zpracuje uzel - získá jeho meshe a jeho další uzly
// usel může mít různý počet pod-uzlů a také meshů
void process_node(C_STRUCT aiNode* assimp_node, np_mia_registry* mesh_registry, const C_STRUCT aiScene* scene, np_model* model, np_dynamic_array* diffuse_texture_2d_path_array, np_camera_3d* camera_3d);
// vytvoří mesh z assimp meshe
void process_mesh(C_STRUCT aiMesh* assimp_mesh, np_mesh* mesh, const C_STRUCT aiScene* scene);
// najde texturu v poli textur pomocí její cesty.
np_texture_2d find_texture_from_path(np_dynamic_array* texture_2d_array, np_dynamic_array* texture_2d_path_array, const char* texture_path);
// načte texturu
void load_assimp_texture(C_STRUCT aiMaterial* assimp_material, enum aiTextureType type, const char* base_uniform_name, np_dynamic_array* textures, np_dynamic_array* texture_paths, char* root_directory, GLuint* texture_unit, np_shader_program shader_program);
// nastaví texturu shader dat.
void set_assimp_texture(C_STRUCT aiMaterial* assimp_material, enum aiTextureType type, const char* base_uniform_name, np_dynamic_array* textures, np_dynamic_array* texture_paths, np_shader_data* shader_data);

//
// implementace
//

np_model* np_model_create(np_scene* scene, const char* filename) {
    np_model* model = np_mia_alloc(scene->model_registry);
// debug
#ifdef NP_DEBUG_MODEL
    np_debug_print_aqua("np_model: started loading scene from: %s", filename);
#endif
    // načteme scénu
    const C_STRUCT aiScene* assimp_scene = aiImportFile(filename, aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace | aiProcess_FlipWindingOrder);
    // zkontrolujeme zda vše je v pořádku
    if (assimp_scene == NULL || assimp_scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || assimp_scene->mRootNode == NULL) {
        np_assert(false, "failed to load model from: %s\n error: %s", filename, aiGetErrorString());
    }
// debug
#ifdef NP_DEBUG_MODEL
    np_debug_print_aqua("np_model: successfully loaded scene from: %s", filename);
#endif
    // transform
    model->transform = (np_tr3*)np_mia_alloc(scene->tr3_registry);
    np_tr3_create(model->transform);
    // mesh registry set
    model->mesh_registry = scene->mesh_registry;
    // po získání scény máme potřebné informace pro iniciaci polí.
    // získáme root dir modelu - pro načítání textur
    char parent_directory[1024];
    np_get_parent_directory(parent_directory, sizeof(parent_directory), filename);
    // vytvoříme pole s odkazy na meshe vytvořeny tímto modelem
    np_id_array_create(&model->meshes, assimp_scene->mNumMeshes, sizeof(size_t));
    //
    // material uniform define & data load
    // 
    // vytvoříme pole materiálu které jsou používány v modelu
    // poté načteme assimp materiály a jejich data přeneseme do np_material
    np_array_create(&model->shaders, assimp_scene->mNumMaterials, sizeof(np_shader));
    // vytvoříme pole s všemi texturami
    np_dynamic_array_create(&model->textures, sizeof(np_texture_2d));
    // tento array obsahuje pouze cesty k souborům textur.
    // každá cesta je na stejném indexu jako daná textura v texture_2d_array
    np_dynamic_array texture_paths;
    np_dynamic_array_create(&texture_paths, sizeof(char[1024]));
    // načteme materiály
    // materiály stejne jako meshe jsou uloženy v jednom velkém poli scény
    // NOTE: všiml jsem si že né každý materiál modelu je použit meshem
    for (GLuint i = 0; i < assimp_scene->mNumMaterials; i++) {
        // TODO: vygenerovat shader? (pomocí np_shader_maker)
        np_shader* shader = (np_shader*)np_array_get(&model->shaders, i);
        // vytvoříme shader z embeded shader kodu
        // POZNÁMKA: používá se stejný shader pro všechny modely
        np_model_resources_create_model_shader(shader);
        // získame assimp materiál
        C_STRUCT aiMaterial* assimp_material = assimp_scene->mMaterials[i];
        GLuint texture_unit = 0;
        load_assimp_texture(assimp_material, aiTextureType_DIFFUSE, "diffuse", &model->textures, &texture_paths, parent_directory, &texture_unit, shader->shader_program);
    }
    // získáme hlavní uzel, a od něj načteme další uzly a jejich meshe
    struct aiNode* assimp_node = assimp_scene->mRootNode;
    process_node(assimp_node, model->mesh_registry, assimp_scene, model, &texture_paths, scene->main_camera);
    // clear
    np_dynamic_array_delete(&texture_paths);
// debug
#ifdef NP_DEBUG_MODEL
    np_debug_print_green("np_model: created model \"%s\" at: %p", assimp_scene->mName.data, model);
#endif
    return model;
}

void np_model_delete(np_model* model) {
    // delete meshes
    for (size_t i = 0; i < np_id_array_get_size(&model->meshes); i++) {
        size_t mesh_id = *(size_t*)np_id_array_get(&model->meshes, np_id_array_get_id_by_id(&model->meshes, i));
        np_mesh* mesh = (np_mesh*)np_mia_get(model->mesh_registry, mesh_id);
        np_mesh_delete(mesh);
        np_mia_free(model->mesh_registry, mesh);
    }
    // reset mesh registr pointer value
    model->mesh_registry = NULL;
    // delete material templates
    for (size_t i = 0; i < np_array_get_size(&model->shaders); i++) {
        np_shader* shader = (np_shader*)np_array_get(&model->shaders, i);
        
    }
    np_array_delete(&model->shaders);
    // delete textures
    for (size_t i = 0; i < np_dynamic_array_get_size(&model->textures); i++) {
        np_texture_2d* texture_2d = (np_texture_2d**)np_dynamic_array_get(&model->textures, i);
        np_texture_2d_delete(texture_2d);
    }
    np_dynamic_array_delete(&model->textures);
// debug
#ifdef NP_DEBUG_MODEL
    np_debug_print_yellow("np_model: deleted model at: %p", model);
#endif
}

np_tr3* np_model_get_tr3(np_model* model) {
    return &model->transform;
}

//
// local implementace
//

void process_node(C_STRUCT aiNode* assimp_node, np_mia_registry* mesh_registry, const C_STRUCT aiScene* scene, np_model* model, np_dynamic_array* diffuse_texture_2d_path_array, np_camera_3d* camera_3d) {
    // zpracová všechny meshe v uzlu
    for (GLuint i = 0; i < assimp_node->mNumMeshes; i++) {
        //
        // mesh data set
        //
        // každýuzel drží pozici meshe v jednom velkém poli meshů scény
        C_STRUCT aiMesh* assimp_mesh = scene->mMeshes[assimp_node->mMeshes[i]];
        // allocujem mesh v společném poli
        np_mesh* mesh = np_mia_alloc(mesh_registry);
        // zpracujeme assimp mesh na náš mesh
        process_mesh(assimp_mesh, mesh, scene);
        // uloží adresu meshe (!!)
        size_t mesh_id = np_id_array_get_id_by_ptr(mesh_registry, mesh);
        np_id_array_add(&model->meshes, &mesh_id);
        //
        // material data set
        //
        C_STRUCT aiMaterial* assimp_material = scene->mMaterials[assimp_mesh->mMaterialIndex];
        np_shader* shader = (np_shader*)np_array_get(&model->shaders, (size_t)assimp_mesh->mMaterialIndex);
        np_shader_data* shader_data = np_mesh_set_shader(mesh, shader);
        *(mat4**)np_shader_data_get(shader_data, "proj_matrix") = np_camera_3d_get_matrix(camera_3d);
        set_assimp_texture(assimp_material, aiTextureType_DIFFUSE, "diffuse", &model->textures, diffuse_texture_2d_path_array, shader_data);
    }
    // zpracová všechny pod-uzly v uzlu
    for (GLuint i = 0; i < assimp_node->mNumChildren; i++) {
        process_node(assimp_node->mChildren[i], mesh_registry, scene, model, diffuse_texture_2d_path_array, camera_3d);
    }
}

void process_mesh(C_STRUCT aiMesh* assimp_mesh, np_mesh* mesh, const C_STRUCT aiScene* scene) { // (!!)
    np_dynamic_array vertices;
    np_dynamic_array_create(&vertices, sizeof(GLfloat));
    np_dynamic_array_resize(&vertices, assimp_mesh->mNumVertices * 3);
    np_dynamic_array indices;
    np_dynamic_array_create(&indices, sizeof(GLuint));
    // získáme všechny vertexy
    for (GLuint i = 0; i < assimp_mesh->mNumVertices; i++) { // POMALÉ !!
        // vertexy jsou jenom pozice
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mVertices[i].x;
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mVertices[i].y;
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mVertices[i].z;
        // colors?
        // normal (!!)
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mNormals[i].x;
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mNormals[i].y;
        *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mNormals[i].z;
        // UV
        // assimp podporuje až 8 UV
        // tady se používají ale jenom ty první
        if (assimp_mesh->mTextureCoords[0]) {  // (!!)
            *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mTextureCoords[0][i].x;
            *(GLfloat*)np_dynamic_array_add(&vertices) = assimp_mesh->mTextureCoords[0][i].y;
        } else { // (!!)
            *(GLfloat*)np_dynamic_array_add(&vertices) = 0.0f;
            *(GLfloat*)np_dynamic_array_add(&vertices) = 0.0f;
        }
    }
    // získáme všechny indexy
    for (GLuint i = 0; i < assimp_mesh->mNumFaces; i++) { // POMALÉ !!
        C_STRUCT aiFace face = assimp_mesh->mFaces[i];
        // z každé strany získáme indexy
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            *(GLuint*)np_dynamic_array_add(&indices) = face.mIndices[j];
            
        }
    }
    // uložíme do meshe
    GLuint attributes[3] = {3, 3, 2};
    np_mesh_create(mesh, (np_mesh_data){(GLfloat*)np_dynamic_array_get(&vertices, 0), np_dynamic_array_get_size(&vertices) * sizeof(GLfloat), (GLuint*)np_dynamic_array_get(&indices, 0), np_dynamic_array_get_size(&indices) * sizeof(GLuint), attributes, sizeof(attributes)});
    // smažeme mesh data
    np_dynamic_array_delete(&vertices);
    np_dynamic_array_delete(&indices);
// debug
#ifdef NP_DEBUG_MODEL
    np_debug_print_purple("np_model: set mesh data for mesh \"%s\"", assimp_mesh->mName.data);
#endif
}

np_texture_2d find_texture_from_path(np_dynamic_array* texture_2d_array, np_dynamic_array* texture_2d_path_array, const char* texture_path) {
    for (size_t i = 0; i < np_dynamic_array_get_size(texture_2d_path_array); i++) {
        char* path = (char*)np_dynamic_array_get(texture_2d_path_array, i);
        if (strcmp(path, texture_path) == 0) {
            return *(np_texture_2d*)np_dynamic_array_get(texture_2d_array, i);
        }
    }
    np_debug_print_red("texture for model not found\nno texture with path%s", texture_path);
    return 0;
}

void load_assimp_texture(C_STRUCT aiMaterial* assimp_material, enum aiTextureType type, const char* base_uniform_name, np_dynamic_array* textures, np_dynamic_array* texture_paths, char* root_directory, GLuint* texture_unit, np_shader_program shader_program) {
    for (GLuint i = 0; i < aiGetMaterialTextureCount(assimp_material, type); i++, (*texture_unit)++) {
        C_STRUCT aiString texture_path;
        np_assert(aiGetMaterialTexture(assimp_material, type, i, &texture_path, NULL, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS, "failed to load model texture");
        char path[1024] = "";
        strcat_s(path, sizeof(path), root_directory);
        strcat_s(path, sizeof(path), texture_path.data);
        //
        char uniform_name[256];
        sprintf_s(uniform_name, sizeof(uniform_name), "%s_%u", base_uniform_name, i);
        // načteme texturu ze souboru
        np_texture_2d texture_2d;
        np_texture_2d_create_from_file(&texture_2d, GL_RGBA, GL_NEAREST, GL_REPEAT, path);
        np_texture_2d_bind_sampler_unit(texture_2d, shader_program, *texture_unit, uniform_name);
        // store texture id for deletion in np_model_delete
        np_dynamic_array_add_copy(textures, &texture_2d);
        np_dynamic_array_add_copy(texture_paths, &texture_path.data);
    }
}

void set_assimp_texture(C_STRUCT aiMaterial* assimp_material, enum aiTextureType type, const char* base_uniform_name, np_dynamic_array* textures, np_dynamic_array* texture_paths, np_shader_data* shader_data) {
    for (GLuint i = 0; i < aiGetMaterialTextureCount(assimp_material, type); i++) {
         C_STRUCT aiString texture_path;
        np_assert(aiGetMaterialTexture(assimp_material, type, i, &texture_path, NULL, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS, "failed to load model texture");
        // získáme uloženou texturu pomocí její cesty.
        np_texture_2d texture_2d = find_texture_from_path(textures, texture_paths, texture_path.data);
        // vytvoříme správný název uniformy
        char uniform_name[256];
        sprintf_s(uniform_name, sizeof(uniform_name), "%s_%u", base_uniform_name, i);
        // nastavíme data uniformy
        *(np_texture_2d*)np_shader_data_get(shader_data, uniform_name) = texture_2d;
    }
}