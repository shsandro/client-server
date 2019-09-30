#ifndef PHOTO_H
#define PHOTO_H

#include <stdbool.h>

#define MAX 64
#define GET 0
#define POST 1

typedef int auto_id;
typedef int req_type;

typedef struct{
    char title[MAX];
    char color_model[MAX];
    int width;
    int heigth;
    int id;
}photo;

typedef struct{
    char title[MAX];
    char color_model[MAX];
    int width;
    int heigth;
    int id;
    req_type req;
}photo_req;


typedef struct{
    photo photos[MAX];
    auto_id photo_id;
}photo_data_base;

photo_data_base photo_db;

void init_photo_db();
photo create_photo(photo_req photo_recieved);
photo get_photo(int id);

#endif