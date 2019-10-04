#ifndef MUSIC_H
#define MUSIC_H

#include <stdbool.h>

#define MAX_MUSIC 32
#define GET 0
#define POST 1

typedef int auto_id;
typedef int req_type;

typedef struct
{
    char name[MAX_MUSIC];
    char singer[MAX_MUSIC];
    char gender[MAX_MUSIC];
    char album[MAX_MUSIC];
    float length;
    int id;
} music;

typedef struct
{
    char name[MAX_MUSIC];
    char singer[MAX_MUSIC];
    char gender[MAX_MUSIC];
    char album[MAX_MUSIC];
    float length;
    int id;
    req_type req;
} music_req;

typedef struct
{
    music musics[MAX_MUSIC];
    auto_id music_id;
} music_data_base;

music_data_base music_db;

void init_music_db();
music create_music(music_req music_recieved);
music get_music(int id);

#endif