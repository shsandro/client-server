#include "../cs_network.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void *connection_handler(void *socket_desc){

}

int main(int argc, const char** argv){
    server cs_server;
    int accepted_socket;
    int pipe_fd[2];
    pid_t pid;

    cs_server.init = init_server;

    if(!cs_server.init(&cs_server, "./hosts/hostfile_server1")){
        printf("Falha na criação do servidor.\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(pipe_fd) < 0){
        perror("Falha ao criar pipe.\n");
    }

    while((accepted_socket = accept(cs_server.socket, (struct sockaddr *)&cs_server.socket_address, &cs_server.sockaddr_lenght)) > 0){
        pid = fork();
        if(pid < 0){
            perror("Não foi possivel criar fork.\n");
            return false;
        } else if(pid == 0){
            printf("Conexão estabelecida.\n");

        }
        
    }

    if(accepted_socket < 0){
        perror("Requisição falhou.\n");
        return false;
    }

    shutdown(cs_server.socket, 2);

    return 0;
}