#include "../cs_network.h"
#include "../models/include/music.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MUSIC_FIFO "/tmp/music_fifo"

int main(int argc, const char** argv){
    server cs_server;
    int accepted_socket;
    pid_t pid;
    int fifo_fd;

    remove(MUSIC_FIFO);

    if (mkfifo(MUSIC_FIFO, 0666) < 0) {
        perror("Erro criando FIFO");
        exit(EXIT_FAILURE);
    }

    init_music_db();

    cs_server.init = init_server;

    if(!cs_server.init(&cs_server, "./hosts/hostfile_server2")){
        printf("Falha na criação do servidor.\n");
        exit(EXIT_FAILURE);
    }

    fifo_fd = open(MUSIC_FIFO, O_RDWR);

    write(fifo_fd, &music_db, sizeof(music_data_base));

    while((accepted_socket = accept(cs_server.socket, (struct sockaddr *)&cs_server.socket_address, &cs_server.sockaddr_lenght)) > 0){
        pid = fork();

        if(pid < 0){
            perror("Não foi possivel criar fork.\n");
            return false;
        } else if(pid == 0){
            printf("Conexão estabelecida.\n");

            read(fifo_fd, &music_db, sizeof(music_data_base));

            music_req music_recieved;

            int v = read(accepted_socket, &music_recieved, sizeof(music_req));
            if(v >= 0){
                music music_response;
                switch (music_recieved.req){
                case POST:
                    music_response = create_music(music_recieved);
                    printf("\n\tPOST recebido\n");
                    printf("\tNome: %s\n", music_recieved.name);
                    printf("\tCantor: %s\n", music_recieved.singer);
                    printf("\tGênero: %s\n", music_recieved.gender);
                    printf("\tDuração: %.2f\n", music_recieved.length);
                    printf("\tRequisição: %d\n", music_recieved.req);
                    break;
                
                case GET:
                    music_response = get_music(music_recieved.id);
                    printf("\n\tGET recebido\n");
                    printf("\tID: %d\n", music_recieved.id);
                    break;
                }

                write(accepted_socket, &music_response, sizeof(music));
                write(fifo_fd, &music_db, sizeof(music_data_base));
                exit(EXIT_SUCCESS);
            }else{
                perror("Leitura da requisição falhou.\n");
                write(accepted_socket, "REQ_FAILED", 11);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    if(accepted_socket < 0){
        perror("Requisição falhou.\n");
        return false;
    }

    shutdown(cs_server.socket, 2);

    return 0;
}