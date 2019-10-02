#include "../cs_network.h"
#include "../models/include/photo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

const unsigned int db_size = sizeof(photo_data_base);

int main(int argc, const char** argv){
    server cs_server;
    int accepted_socket;
    pid_t pid;

    init_photo_db();
    cs_server.init = init_server;

    if(!cs_server.init(&cs_server, "./hosts/hostfile_server3")){
        printf("Falha na criação do servidor.\n");
        exit(EXIT_FAILURE);
    }
    key_t key = ftok("shmfile",65); 
    if(key < 0 ){
        perror("Erro no ftok");
        exit(EXIT_FAILURE);
    }
    int shmid = shmget(key, db_size , 0666 | IPC_CREAT);
    if(shmid < 0){
        perror("Erro shmid");
        exit(EXIT_FAILURE);
    }
    photo_data_base *shared_memory_photo = (photo_data_base*) shmat(shmid,NULL, 0);

    memcpy(shared_memory_photo, &photo_db, sizeof(photo_data_base)); //escrevo o do db pra memória compartilhada

    while((accepted_socket = accept(cs_server.socket, (struct sockaddr *)&cs_server.socket_address, &cs_server.sockaddr_lenght)) > 0){
        pid = fork();
        if(pid < 0){
            perror("Não foi possivel criar fork.\n");
            return false;
        } else if(pid == 0){
            printf("Conexão estabelecida.\n");
            photo_req photo_recieved;
            
            memcpy(&photo_db, shared_memory_photo, sizeof(photo_data_base));  //leio tudo que está na memoria compartilhada pro bd
            
            int v = read(accepted_socket, &photo_recieved, sizeof(photo_req));
            if(v >= 0){
                photo photo_response;
                switch (photo_recieved.req){
                case POST:
                    photo_response = create_photo(photo_recieved);
                    printf("\n\t POST Recebido");
                    printf("\tTítulo: %s\n", photo_recieved.title);
                    printf("\tModelo de cor: %s\n", photo_recieved.color_model);
                    printf("\tLargura: %d\n", photo_recieved.width);
                    printf("\tAltura: %d\n", photo_recieved.heigth);
                    printf("\tRequisição: %d\n", photo_recieved.req);
                    break;
                
                case GET:
                    photo_response = get_photo(photo_recieved.id);
                    printf("\n\tGet recebido");
                    printf("\tID: %d\n", photo_recieved.id);
                    break;

                }
                write(accepted_socket, &photo_response, sizeof(photo));
            } else {
                perror("Leitura da requisição falhou.\n");
                write(accepted_socket, "REQ_FAILED", 11);
                exit(EXIT_FAILURE);
            }
            memcpy(shared_memory_photo, &photo_db, sizeof(photo_data_base)); //escrevo o do db pra memória compartilhada
            exit(EXIT_SUCCESS);
        }
    }

    if(accepted_socket < 0){
        perror("Requisição falhou.\n");
        return false;
    }
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}