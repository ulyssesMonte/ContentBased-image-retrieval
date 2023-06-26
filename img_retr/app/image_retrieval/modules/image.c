#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include <string.h>

struct image_file_list{

    ImageFileModule * first_image;
    ImageFileModule * last_image;
    int qtd_images;

};


struct image_file_module{

    char ** image_file;
    ImageFileModule * next_image;
    ImageFileModule * prev_image;

};

ImageFileList * list_init(){
    ImageFileList * l_image = (ImageFileList * )malloc(sizeof(ImageFileList));
    l_image->first_image = NULL;
    l_image->last_image = NULL;
    l_image->qtd_images = 0;


    return l_image;

}


void list_append(ImageFileList *l_image,char** image_file_path){

    ImageFileModule * img_module = (ImageFileModule *)malloc(sizeof(ImageFileModule));
    img_module->image_file = image_file_path;

    if(list_is_empty(l_image)){
        l_image->first_image = img_module;
        l_image->last_image = img_module;
        l_image->qtd_images += 1;
        l_image->first_image->next_image = NULL;

    }else{
       ImageFileModule * l_module_temp = l_image->last_image;
       l_image->last_image = img_module;
       l_image->last_image->prev_image = l_module_temp;
       l_image->last_image->next_image = NULL;
       l_image->qtd_images += 1;
    }

}

int list_is_empty(ImageFileList * l_image){return l_image->qtd_images==0;}

void save_image_data(char *image_path,char *path_for_save_file){
    int x_width,y_height,n_channels;
    
    /*
    0-standard channel
    1-grayscale
    2-grayscale and alpha
    3-rgb
    4-rgb and alpha
    */
    FILE * image_data_file = fopen(path_for_save_file,"w");
    stbi_uc * image_file = stbi_load(image_path,&x_width,&y_height,&n_channels,0);

    fprintf(image_data_file,"%d\n%d",x_width,y_height);


    for(int y=0;y<y_height;y++){
        for(int x=0; x<x_width;x++){
            uint8_t pixel_data = image_file[(y *x_width +x)*n_channels];
            fprintf(image_data_file,"%d ",pixel_data);
        }
        fprintf(image_data_file,"\n");
    }
    printf("Dados de pixel da imagem salvos em %s !\n",path_for_save_file);

}

/*
O compilador, ao selecionar os arquivos a serem compilados, verifica primeiramente os headers(arquivos .h), 
onde deverão ter as definições e declarações dos TADS, estruturas e funções da aplicação
*/


