#include "cs_network.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool init_server(server* self, const char* host_path){
    self->sockaddr_lenght = (socklen_t)sizeof(self->socket_address);

    self->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(self->socket == 0){
        perror("Não foi possível criar o socket SERVER.\n");
        return false;
    }

    if(read_hostfile(host_path, &self->socket_address) == false) return false;

    printf("Socket SERVER criado.\nSocket descriptor: %d.\n", self->socket);

    if(bind(self->socket, (struct sockaddr*)&self->socket_address, self->sockaddr_lenght) < 0){
        perror("Bind SERVER falhou.\n");
        printf("%s\n", self->socket, (struct sockaddr*)&self->socket_address, self->sockaddr_lenght);
        return false;
    }

    if(listen(self->socket, 5) < 0){
         perror("Listen SERVER falhou.\n");
         return false;
    }

    printf("Servidor escutando na porta %d.\n", htons(self->socket_address.sin_port));
    return true;
}

bool init_client(client* self){
    self->sockaddr_lenght = (socklen_t)sizeof(self->socket_address);

    self->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(self->socket == 0){
        perror("Não foi possível criar o socket SERVER.\n");
        return false;
    }

    if(read_hostfile("./hosts/hostfile_server1", &self->socket_address[VIDEO_SERVER]) == false) return false;
    if(read_hostfile("./hosts/hostfile_server2", &self->socket_address[MUSIC_SERVER]) == false) return false;
    if(read_hostfile("./hosts/hostfile_server3", &self->socket_address[PHOTO_SERVER]) == false) return false;

    printf("Socket CLIENT criado.\n");

    return true;
}

bool read_hostfile(const char* path, struct sockaddr_in* connection_data){
    FILE* hostfile;
    
    char buffer[32];
    int port;

    hostfile = fopen(path, "r");

    if(!hostfile){
        printf("Hostfile não encontrado: %s\n", path);
        return false;
    }

    memset(buffer, 0, sizeof(buffer));

    if(fscanf(hostfile, "%s", buffer) == 0){
		printf("Hostfile corrompido: %s\n", path);
		return false;
    }
    connection_data->sin_addr.s_addr = inet_addr((const char*)buffer);

    if(fscanf(hostfile, "%d", &port) == 0){
		printf("Hostfile corrompido: %s\n", path);
		return false;
    }
    connection_data->sin_port = htons(port);

    connection_data->sin_family = AF_INET;

    fclose(hostfile);
    return true;
}