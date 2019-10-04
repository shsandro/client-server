#ifndef CS_NETWORK_H
#define CS_NETWORK_H

#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define VIDEO_SERVER 0
#define MUSIC_SERVER 1
#define PHOTO_SERVER 2

typedef struct client
{
    int socket;
    socklen_t sockaddr_lenght;
    struct sockaddr_in socket_address;
    bool (*init)(struct client *);
} client;

typedef struct server
{
    int socket;
    socklen_t sockaddr_lenght;
    struct sockaddr_in socket_address;
    bool (*init)(struct server *, const char *);
} server;

typedef struct proxy
{
    int socket;
    socklen_t sockaddr_lenght;
    struct sockaddr_in socket_address;
    struct sockaddr_in socket_server_address[3];
    bool (*init)(struct proxy *);
} proxy;

bool init_server(server *self, const char *host_path);
bool init_client(client *self);
bool init_proxy(proxy *self);
bool read_hostfile(const char *path, struct sockaddr_in *connection_data);

#endif