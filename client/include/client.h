#ifndef CLIENT_H
#define CLIENT_H

#include "../../cs_network.h"
#include "../../models/include/video.h"
#include "../../models/include/music.h"
#include "../../models/include/photo.h"

typedef struct
{
    int server;
    union {
        video_req video_sent;
        music_req music_sent;
        photo_req photo_sent;
    } object;

} requisition;

const unsigned int VIDEO_SIZE = sizeof(video_req);
const unsigned int MUSIC_SIZE = sizeof(music_req);
const unsigned int PHOTO_SIZE = sizeof(photo_req);

bool send_message(client *cs_client, requisition *req);
void build_video(video_req *video_sent);
void build_music(music_req *music_sent);
void build_photo(photo_req *photo_sent);
void video_id(video_req *video_sent);
void music_id(music_req *music_sent);
void photo_id(photo_req *photo_sent);

#endif