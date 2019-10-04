#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>

#define MAX_VIDEO 64
#define GET 0
#define POST 1

typedef int auto_id;
typedef int req_type;

typedef struct
{
    char name[MAX_VIDEO];
    char director[MAX_VIDEO];
    char gender[MAX_VIDEO];
    float length;
    int id;
} video;

typedef struct
{
    char name[MAX_VIDEO];
    char director[MAX_VIDEO];
    char gender[MAX_VIDEO];
    float length;
    int id;
    req_type req;
} video_req;

typedef struct
{
    video videos[MAX_VIDEO];
    auto_id video_id;
} video_data_base;

video_data_base video_db;

void init_video_db();
video create_video(video_req video_recieved);
video get_video(int id);

#endif