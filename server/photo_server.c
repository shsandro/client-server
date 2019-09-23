#include "../cs_network.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, const char** argv){
    // sleep(2);
    server cs_server;

    cs_server.init = init_server;

    if(!cs_server.init(&cs_server, "./hosts/hostfile_server3")){
        printf("Falha na criação do servidor.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}