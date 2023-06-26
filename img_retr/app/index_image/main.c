#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "modules/image.h"
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    
    if(!(argc > 1)){
        printf("Erro. Nenhum comando adicional detectado.");
        return 1;
    }

    //char * comando1 = argv[1];
    //char * comando2 = argv[2];

    if(strcmp(argv[1],"--all")==0){
        ImageFileList * i_list = list_init();
        index_base_images(i_list);
        free(i_list);
        return 0;

    }else if(strcmp(argv[1],"--specify")==0){
        printf("Escolha a localidade:");
    }else{
        printf("Erro.");
        return 1;
    }
    //print_string(comando1);
    //save_image_histogram(comando1,comando2); 
    
    return 0;
}