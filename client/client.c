#include "../cs_network.h"
#include "../models/include/video.h"
#include "../models/include/music.h"
#include "../models/include/photo.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int server;
    union {
        video_req video_sent;
        music_req music_sent;
        photo_req photo_sent;
    } object;

} requisition;

const unsigned int VIDEO_SIZE = sizeof(video_req);
const unsigned int MUSIC_SIZE = sizeof(music_req);
const unsigned int PHOTO_SIZE = sizeof(photo_req);

bool send_message(client *cs_client, requisition *req)
{
    if ((cs_client->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }

    if (connect(cs_client->socket, (struct sockaddr *)&cs_client->socket_address, cs_client->sockaddr_lenght) < 0)
    {
        perror("Conexão falhou.\n");
        printf("%s\n", cs_client->socket, (struct sockaddr *)&cs_client->socket_address, cs_client->sockaddr_lenght);
        return 0;
    }
    printf("\n %d", req->server);

    switch (req->server)
    {
    case VIDEO_SERVER:
        if (send(cs_client->socket, &req->object.video_sent, sizeof(video_req), 0) == -1)
        {
            perror("Error sending message");
        }
        break;

    case MUSIC_SERVER:
        printf("\n enviando para a música");
        if (send(cs_client->socket, &req->object.music_sent, sizeof(music_req), 0) == -1)
        {
            perror("Error sending message");
        }
        break;
    }

    return true;
}

void build_video(video_req *video_sent)
{
    char c;
    printf("\nNome: ");
    scanf("%c\n", &c);
    fgets(video_sent->name, 32, stdin);
    printf("\nDiretor: ");
    fgets(video_sent->director, 32, stdin);
    printf("\nGênero: ");
    fgets(video_sent->gender, 32, stdin);
    printf("\nTamanho:");
    scanf("%f", &video_sent->length);
    video_sent->req = POST;
}

void build_music(music_req *music_sent)
{
    char c;
    printf("\nNome: ");
    scanf("%c\n", &c);
    fgets(music_sent->name, 32, stdin);
    printf("\nDiretor: ");
    fgets(music_sent->singer, 32, stdin);
    printf("\nGênero: ");
    fgets(music_sent->gender, 32, stdin);
    printf("\nAlbum: ");
    fgets(music_sent->album, 32, stdin);
    printf("\nTamanho:");
    scanf("%f", &music_sent->length);
    music_sent->req = POST;
}

void get_video_id(video_req *video_sent)
{
    printf("\nInsira o ID do vídeo a ser buscado: ");
    scanf("%d", &video_sent->id);
    video_sent->req = GET;
}

void get_music_id(music_req *music_sent)
{
    printf("\nInsira o ID da música a ser buscada: ");
    scanf("%d", &music_sent->id);
    music_sent->req = GET;
}

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

        requisition req;

        switch (action)
        {
        case VIDEO_SERVER:
        {
            req.server = VIDEO_SERVER;

            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
            case POST:
                build_video(&req.object.video_sent);
                break;

            case GET:
                get_video_id(&req.object.video_sent);
                break;
            }

            send_message(&cs_client, &req);

            video video_recivied;

            read(cs_client.socket, &video_recivied, sizeof(video));

            printf("\n\tObjeto recebido da requisição %d\n", req.object.video_sent.req);
            printf("\tNome        : %s\n", video_recivied.name);
            printf("\tDiretor     : %s\n", video_recivied.director);
            printf("\tGênero      : %s\n", video_recivied.gender);
            printf("\tTamanho     : %.2f\n", video_recivied.length);
            printf("\tID          : %d\n", video_recivied.id);
        }
        break;

        case MUSIC_SERVER:
        {
            req.server = MUSIC_SERVER;

            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
            case POST:
                build_music(&req.object.music_sent);
                break;

            case GET:
                get_music_id(&req.object.music_sent);
                break;
            }

            send_message(&cs_client, &req);

            music music_recivied;

            read(cs_client.socket, &music_recivied, sizeof(music));

            printf("\n\tObjeto recebido da requisição %d\n", req.object.music_sent.req);
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