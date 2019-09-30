#include "./include/photo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_photo_db(){
    for(int i = 0; i < MAX; ++i){
        photo_db.photos[i].id = -1;
    }

    photo_db.photo_id = 0;

    printf("Banco de Dados de fotos inicializado.\n");
}

photo create_photo(photo_req photo_recieved){
    strcpy(photo_db.photos[photo_db.photo_id].title, photo_recieved.title);
    strcpy(photo_db.photos[photo_db.photo_id].color_model, photo_recieved.color_model);
    photo_db.photos[photo_db.photo_id].width = photo_recieved.width;
    photo_db.photos[photo_db.photo_id].heigth = photo_recieved.heigth;
    photo_db.photos[photo_db.photo_id].id = photo_db.photo_id;
    ++photo_db.photo_id;
    return photo_db.photos[photo_db.photo_id-1];
}

photo get_photo(int id){
    if(photo_db.photos[id].id == -1){
        printf("ID não cadastrado.\n");
        exit(EXIT_FAILURE);
    }

    return photo_db.photos[id];
}