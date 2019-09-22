#include "cs_network.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libexplain/bind.h>

bool init(){
    connection = (cs_connection*)malloc(sizeof(cs_connection));

    connection->sockaddr_lenght = (socklen_t)sizeof(connection->client);

    connection->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(connection->client_socket == 0){
        perror("Não foi possível criar o socket CLIENT.\n");
        return false;
    }

    connection->servers_sockets[VIDEO_SERVER] = socket(AF_INET, SOCK_STREAM, 0);
    if(connection->servers_sockets[VIDEO_SERVER] == 0){
        perror("Não foi possível criar o socket VIDEO_SERVER.\n");
        return false;
    }

    connection->servers_sockets[MUSIC_SERVER] = socket(AF_INET, SOCK_STREAM, 0);
    if(connection->servers_sockets[MUSIC_SERVER] == 0){
        perror("Não foi possível criar o socket MUSIC_SERVER.\n");
        return false;
    }

    connection->servers_sockets[PHOTO_SERVER] = socket(AF_INET, SOCK_STREAM, 0);
    if(connection->servers_sockets[PHOTO_SERVER] == 0){
        perror("Não foi possível criar o socket PHOTO_SERVER.\n");
        return false;
    }

    if(read_hostfile("./hosts/hostfile_server1", &connection->servers[VIDEO_SERVER]) == false) return false;

    if(read_hostfile("./hosts/hostfile_server2", &connection->servers[MUSIC_SERVER]) == false) return false;

    if(read_hostfile("./hosts/hostfile_server3", &connection->servers[PHOTO_SERVER]) == false) return false;

    printf("Sockets client e servers criados.\n");

    if(bind(connection->servers_sockets[VIDEO_SERVER], (struct sockaddr*)&connection->servers[VIDEO_SERVER], connection->sockaddr_lenght) < 0){
        perror("Bind VIDEO_SERVER falhou.\n");
        printf("%s\n", explain_bind(connection->servers_sockets[VIDEO_SERVER], (struct sockaddr*)&connection->servers[VIDEO_SERVER], connection->sockaddr_lenght));
        return false;
    }

    if(bind(connection->servers_sockets[MUSIC_SERVER], (struct sockaddr*)&connection->servers[MUSIC_SERVER], connection->sockaddr_lenght) < 0){
        perror("Bind MUSIC_SERVER falhou.\n");
        printf("%s\n", explain_bind(connection->servers_sockets[MUSIC_SERVER], (struct sockaddr*)&connection->servers[MUSIC_SERVER], connection->sockaddr_lenght));
        return false;
    }

    if(bind(connection->servers_sockets[PHOTO_SERVER], (struct sockaddr*)&connection->servers[PHOTO_SERVER], connection->sockaddr_lenght) < 0){
        perror("Bind PHOTO_SERVER falhou.\n");
        printf("%s\n", explain_bind(connection->servers_sockets[PHOTO_SERVER], (struct sockaddr*)&connection->servers[PHOTO_SERVER], connection->sockaddr_lenght));
        return false;
    }

    printf("Servidores escutando nas portas %d, %d e %d.\n", htons(connection->servers[VIDEO_SERVER].sin_port), htons(connection->servers[MUSIC_SERVER].sin_port), htons(connection->servers[PHOTO_SERVER].sin_port));

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

    return true;
}