#include "./include/video.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_video_db(){
    for(int i = 0; i < MAX; ++i){
        video_db.videos[i].id = -1;
    }

    video_db.video_id = 0;

    printf("Banco de Dados de vídeos inicializado.\n");
}

video create_video(video_req video_recieved){
    // video_db[video_id] = (video*)malloc(sizeof(video));
    strcpy(video_db.videos[video_db.video_id].name, video_recieved.name);
    strcpy(video_db.videos[video_db.video_id].director, video_recieved.director);
    strcpy(video_db.videos[video_db.video_id].gender, video_recieved.gender);
    video_db.videos[video_db.video_id].length = video_recieved.length;
    video_db.videos[video_db.video_id].id = video_db.video_id;
    ++video_db.video_id;
    return video_db.videos[video_db.video_id-1];
}

video get_video(int id){
    if(video_db.videos[id].id == -1){
        printf("ID não cadastrado.\n");
        exit(EXIT_FAILURE);
    }

    return video_db.videos[id];
}