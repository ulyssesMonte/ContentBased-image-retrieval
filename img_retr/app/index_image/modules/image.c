#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include <string.h>
#include <dirent.h>
#include <unistd.h>

struct image_file_list{

    ImageFileModule * first_image;
    ImageFileModule * last_image;
    int qtd_images;

};


struct image_file_module{

    char * image_file;
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


void list_append(ImageFileList *l_image,char* image_file_path){

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

void index_base_images(ImageFileList *image_list){

    char * base_img_path = "../../base/img/";

    if(chdir(base_img_path)==0){

        DIR *base_dir;
        struct dirent *entry;
        
        base_dir = opendir(base_img_path);
        if (base_dir == NULL){
            printf("Erro: Diretório inexistente.");
        }else{
            while((entry = readdir(base_dir)) != NULL){
                DIR *image_dir;
                struct dirent *entry_img;
                
                
                

                if(strcmp(entry->d_name,"..")==0 || strcmp(entry->d_name,".")==0){
                    continue;
                }else{
                    int temp_len = strlen(base_img_path)+strlen(entry->d_name);
                    char * locality_path = calloc(temp_len,sizeof(char));
                    strcat(locality_path,base_img_path);
                    strcat(locality_path,entry->d_name);

                    image_dir = opendir(locality_path);
                    while((entry_img = readdir(image_dir)) != NULL){
                        
                        //printf("%s\n",entry_img->d_name);
                        if(strcmp(entry_img->d_name,"..")==0||strcmp(entry_img->d_name,".")==0){
                            continue;
                        }else{
                            //"../../base/img/<loc>/<img>"
                            //"../../base/img/ dog / dog1.jpg"
                            int str_size = strlen(base_img_path)+strlen(entry->d_name)+strlen("/")+strlen(entry_img->d_name);

                            char *temp = calloc(str_size,sizeof(char));

                            strcat(temp,base_img_path);
                            strcat(temp,entry->d_name);
                            strcat(temp,"/");
                            strcat(temp,entry_img->d_name);

                            
                            list_append(image_list,temp);
                            printf("Caminho '%s' adicionado na lista. Total de %d imagens indexadas\n\n",image_list->last_image->image_file,image_list->qtd_images);
                            free(temp);
                        }
                        
                    }

                    closedir(image_dir);
                    free(locality_path);
                }
                
                
            }
        }
        closedir(base_dir);

    }else{
        printf("Não foi possível acessar o diretório.");
    }

    
    
}

int list_is_empty(ImageFileList * l_image){return l_image->qtd_images==0;}


 void save_image_histogram(char *image_path,char *path_for_save_file) {

    FILE * image_data_file = fopen(path_for_save_file,"w");
    int x_width,y_height,n_channels;
    
    // Carrega a imagem
    stbi_uc * image_file = stbi_load(image_path,&x_width,&y_height,&n_channels,0);

    // Inicializa um vetor para os valores de histograma
    int histogram[HISTOGRAM_MAX_SIZE];

    // Inicializa o histograma com zeros
    for (int i = 0; i < HISTOGRAM_MAX_SIZE; i++) {
        histogram[i] = 0;
        //fprintf(image_data_file,"%d ",histogram[i]);
    }

    // Calcula o histograma em escala de cinza
    for (int y = 0; y < y_height; y++) {
        for (int x = 0; x < x_width; x++) {
            
            //Se a imagem não tiver 3 canais de cor(RGB):
            if(n_channels == 1){
                uint8_t gray = image_file[(y * x_width +x) *n_channels];
           
                // Incrementa a contagem no histograma para a escala de cinza

                if (gray==256)
                    histogram[gray-1]++;
                else
                    histogram[gray]++;
            }else if(n_channels == 3){ 
                uint8_t red = image_file[(y * x_width + x) * n_channels];
                uint8_t green = image_file[(y * x_width + x) * n_channels+1];
                uint8_t blue = image_file[(y*x_width+x) *n_channels+2];

                uint8_t gray = (red+green+blue)/3;

                if (gray==256)
                    histogram[gray-1]++;
                else
                    histogram[gray]++;
            }
        }
    }
    
    stbi_image_free(image_file);

    // Salva cada um dos valores de intensidade das escalas de cinza em um arquivo de texto
    

    for(int v=0; v<HISTOGRAM_MAX_SIZE ;v++){
        fprintf(image_data_file,"%d\n",histogram[v]);
    }
    fclose(image_data_file);
    printf("Dados de histograma salvos em '%s'!",path_for_save_file);
}

/*
O compilador, ao selecionar os arquivos a serem compilados, verifica primeiramente os headers(arquivos .h), 
onde deverão ter as definições e declarações dos TADS, estruturas e funções da aplicação
*/


