#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include <dirent.h>

int main(int argc, char *argv[]){
    
    
    if(!(argc > 1)){
        printf("Erro. Nenhum comando adicional detectado.");
        return 1;
    }
    DIR *image_directory = opendir(argv[2]);

    if(image_directory==NULL){
        printf("Erro. Diretório de arquivo inválido.");
        return 1;
    }
    closedir(image_directory);


    ImageFileList * list_of_images = list_init();
    return 0;
}
