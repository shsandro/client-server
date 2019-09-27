#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>

#define MAX 64
#define GET 0
#define POST 1

typedef int auto_id;
typedef int req_type;

typedef struct{
    char name[MAX];
    char director[MAX];
    char gender[MAX];
    float length;
    int id;
}video;

typedef struct{
    char name[MAX];
    char director[MAX];
    char gender[MAX];
    float length;
    int id;
    req_type req;
}video_req;


typedef struct{
    video videos[MAX];
    auto_id video_id;
}data_base;

data_base video_db;

void init_db();
video create_video(video_req video_recieved);
video get_video(int id);

#endif