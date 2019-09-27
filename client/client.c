#include "../cs_network.h"
#include "../models/include/video.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libexplain/connect.h>

int main(int argc, const char** argv){
    client cs_client;
    int action;

    cs_client.init = init_client;
    
    if(!cs_client.init(&cs_client)){
        perror("Falha na criação do cliente.\n");
        exit(EXIT_FAILURE);
    }

    while(true){
        video_req video_sent;
        printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
        scanf("%d", &action);

        switch (action){
        case POST:
            strcpy(video_sent.name, "Tropa de Elite");
            strcpy(video_sent.director, "Não tenho ideia");
            strcpy(video_sent.gender, "Policial");
            video_sent.length = 2.0;
            video_sent.req = POST;
            break;
        
        case GET:
            video_sent.id = 0;
            video_sent.req = GET;
            break;
        }

        if ((cs_client.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
            perror("\n Socket creation error \n"); 
            exit(EXIT_FAILURE);
        }

        if (connect(cs_client.socket, (struct sockaddr *)&cs_client.socket_address[VIDEO_SERVER], cs_client.sockaddr_lenght) < 0){
            perror("Conexão falhou.\n");
            printf("%s\n", explain_connect(cs_client.socket, (struct sockaddr *)&cs_client.socket_address[VIDEO_SERVER], cs_client.sockaddr_lenght));
            return 0;
        }

        if (send(cs_client.socket, &video_sent, sizeof(video_req), 0) == -1) {
            perror("Error sending message");
        }else {
            if(!action){
                printf("\n\tMessage sent\n");
                printf("\tID: %d\n", video_sent.id);
            } else {
                printf("\n\tMessage sent\n");
                printf("\tNome: %s\n", video_sent.name);
                printf("\tDiretor: %s\n", video_sent.director);
                printf("\tGênero: %s\n", video_sent.gender);
                printf("\tDuração: %.2f\n", video_sent.length);
                printf("\tRequisição: %d\n", video_sent.req);
            }
        }

        video video_recivied;

        read(cs_client.socket, &video_recivied, sizeof(video));

        printf("\n\tObjeto recebido da requisição %d\n", video_sent.req);
        printf("\tNome        : %s\n", video_recivied.name);
        printf("\tDiretor     : %s\n", video_recivied.director);
        printf("\tGênero      : %s\n", video_recivied.gender);
        printf("\tTamanho     : %.2f\n", video_recivied.length);
        printf("\tID          : %d\n", video_recivied.id);
    }

    return 0;
}