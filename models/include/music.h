#ifndef MUSIC_H
#define MUSIC_H

#include <stdbool.h>

#define MAX 64
#define GET 0
#define POST 1

typedef int auto_id;
typedef int req_type;

typedef struct{
    char name[MAX];
    char singer[MAX];
    char gender[MAX];
    float length;
    int id;
}music;

typedef struct{
    char name[MAX];
    char singer[MAX];
    char gender[MAX];
    float length;
    int id;
    req_type req;
}music_req;


typedef struct{
    music musics[MAX];
    auto_id music_id;
}music_data_base;

music_data_base music_db;

void init_music_db();
music create_music(music_req music_recieved);
music get_music(int id);

#endif