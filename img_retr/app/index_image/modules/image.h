#ifndef IMAGE_H
#define IMAGE_H

#define HISTOGRAM_MAX_SIZE 256

typedef struct image_file_list ImageFileList;

typedef struct image_file_module ImageFileModule;

typedef struct locality_file_list LocalityFileList;

typedef struct locality_file_module LocalityFileModule;


//Cria uma nova lista encadeada de imagens
ImageFileList * list_init();

//insere um novo elemento de imagem na lista
void list_append(ImageFileList *image_list,char *image_file_path);

void list_remove(ImageFileList *image_list, char *image_file);

void list_free(ImageFileList *image_list);

//Pega as imagens da base e organiza elas em uma lista encadeada
void index_base_images(ImageFileList * l_images);

//Lê uma imagem especificada em image path e salva os dados dos pixels no arquivo-texto em path_for_save_file
//void save_image_data(char *image_path,char *path_for_save_file);

void save_image_histogram(char *image_path, char *path_for_save_file);

int list_is_empty(ImageFileList * l_image);

void print_string(char *string);


#endif