#include "../cs_network.h"
#include "../models/include/video.h"
#include "../models/include/music.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int max_size(){
    int video_req_size = sizeof(video_req);
    int music_req_size = sizeof(music_req);

    return (video_req_size > music_req_size)
}

int main(int argc, const char** argv){
    proxy cs_proxy;
    int action;

    cs_proxy.init = init_proxy;

    if(!cs_proxy.init(&cs_proxy)){
        perror("Falha na criação do proxy.\n");
        exit(EXIT_FAILURE);
    }

    const unsigned int MAX_REQ_SIZE = sizeof(func_req);
}