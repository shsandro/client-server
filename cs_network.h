#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#define VIDEO_SERVER 0
#define MUSIC_SERVER 1
#define PHOTO_SERVER 2

typedef struct{
    int servers_sockets[3];
    int client_socket;
    socklen_t sockaddr_lenght;
    struct sockaddr_in client;
    struct sockaddr_in servers[3];
}cs_connection;

cs_connection* connection;

bool init(void);
bool read_hostfile(const char* path, struct sockaddr_in* connection_data);