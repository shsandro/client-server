#include "../cs_network.h"
#include "../models/include/video.h"
#include "../models/include/music.h"
#include "../models/include/photo.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    client cs_client;
    int action;

    cs_client.init = init_client;

    if (!cs_client.init(&cs_client))
    {
        perror("Falha na criação do cliente.\n");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        printf("\nEntre com o modelo para a requisição:\n[0] VIDEO\n[1] MUSIC\n[2] PHOTO\n");
        scanf("%d", &action);

        switch (action)
        {
        case VIDEO_SERVER:
        {
            video_req video_sent;
            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
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

            if ((cs_client.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("\n Socket creation error \n");
                exit(EXIT_FAILURE);
            }

            if (connect(cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght) < 0)
            {
                perror("Conexão falhou.\n");
                printf("%s\n", cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght);
                return 0;
            }

            if (send(cs_client.socket, &video_sent, sizeof(video_req), 0) == -1)
            {
                perror("Error sending message");
            }
            else
            {
                if (!action)
                {
                    printf("\n\tMessage sent\n");
                    printf("\tID: %d\n", video_sent.id);
                }
                else
                {
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
        break;

        case MUSIC_SERVER:
        {
            music_req music_sent;
            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
            case POST:
                strcpy(music_sent.name, "Like a Virgin");
                strcpy(music_sent.singer, "Madonna");
                strcpy(music_sent.gender, "Pop");
                strcpy(music_sent.album, "Dark side of the moon");
                music_sent.length = 3.0;
                music_sent.req = POST;
                break;

            case GET:
                music_sent.id = 0;
                music_sent.req = GET;
                break;
            }

            if ((cs_client.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("\n Socket creation error \n");
                exit(EXIT_FAILURE);
            }

            if (connect(cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght) < 0)
            {
                perror("Conexão falhou.\n");
                printf("%s\n", cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght);
                return 0;
            }

            if (send(cs_client.socket, &music_sent, sizeof(music_req), 0) == -1)
            {
                perror("Error sending message");
            }
            else
            {
                if (!action)
                {
                    printf("\n\tMessage sent\n");
                    printf("\tID: %d\n", music_sent.id);
                }
                else
                {
                    printf("\n\tMessage sent\n");
                    printf("\tNome: %s\n", music_sent.name);
                    printf("\tCantor: %s\n", music_sent.singer);
                    printf("\tGênero: %s\n", music_sent.gender);
                    printf("\tAlbum: %s\n", music_sent.album);
                    printf("\tDuração: %.2f\n", music_sent.length);
                    printf("\tRequisição: %d\n", music_sent.req);
                }
            }

            music music_recivied;

            read(cs_client.socket, &music_recivied, sizeof(music));

            printf("\n\tObjeto recebido da requisição %d\n", music_sent.req);
            printf("\tNome        : %s\n", music_recivied.name);
            printf("\tSinger      : %s\n", music_recivied.singer);
            printf("\tGênero      : %s\n", music_recivied.gender);
            printf("\tAlbum       :%s\n", music_recivied.album);
            printf("\tTamanho     : %.2f\n", music_recivied.length);
            printf("\tID          : %d\n", music_recivied.id);
        }
        break;

        case PHOTO_SERVER:
        {
            photo_req photo_sent;
            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
            case POST:
                strcpy(photo_sent.title, "A grande ficha");
                strcpy(photo_sent.color_model, "RGB");
                photo_sent.width = 1024;
                photo_sent.heigth = 720;
                photo_sent.req = POST;
                break;

            case GET:
                photo_sent.id = 0;
                photo_sent.req = GET;
                break;
            }
            if ((cs_client.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("\n Socket creation error \n");
                exit(EXIT_FAILURE);
            }

            if (connect(cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght) < 0)
            {
                perror("Conexão falhou.\n");
                printf("%s\n", cs_client.socket, (struct sockaddr *)&cs_client.socket_address, cs_client.sockaddr_lenght);
                return 0;
            }

            if (send(cs_client.socket, &photo_sent, sizeof(photo_req), 0) == -1)
            {
                perror("Error sending message");
            }
            else
            {
                if (!action)
                {
                    printf("\n\tMessage sent\n");
                    printf("\tID: %d\n", photo_sent.id);
                }
                else
                {
                    printf("\n\tMessage sent\n");
                    printf("\tTítulo: %s\n", photo_sent.title);
                    printf("\tModelo de cores: %s\n", photo_sent.color_model);
                    printf("\tLargura: %d\n", photo_sent.width);
                    printf("\tAltura: %d\n", photo_sent.heigth);
                    printf("\tRequisição: %d\n", photo_sent.req);
                }
            }

            photo photo_recivied;

            read(cs_client.socket, &photo_recivied, sizeof(photo));

            printf("\n\tObjeto recebido da requisição %d\n", photo_sent.req);
            printf("\tTítulo        : %s\n", photo_recivied.title);
            printf("\tModelo de cores      : %s\n", photo_recivied.color_model);
            printf("\tLargura     : %d\n", photo_recivied.width);
            printf("\tAltura     : %d\n", photo_recivied.heigth);
            printf("\tID          : %d\n", photo_recivied.id);
        }

        break;
        }
    }

    return 0;
}