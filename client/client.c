#include "./include/client.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool send_message(client *cs_client, requisition *req)
{
    if ((cs_client->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("\n Socket creation error \n");
        return false;
    }

    if (connect(cs_client->socket, (struct sockaddr *)&cs_client->socket_address, cs_client->sockaddr_lenght) < 0)
    {
        perror("Conexão falhou.\n");
        printf("%s\n", cs_client->socket, (struct sockaddr *)&cs_client->socket_address, cs_client->sockaddr_lenght);
        return false;
    }

    switch (req->server)
    {
    case VIDEO_SERVER:
        if (send(cs_client->socket, &req->object.video_sent, sizeof(video_req), 0) == -1)
        {
            perror("Error sending message");
            return false;
        }
        break;

    case MUSIC_SERVER:
        if (send(cs_client->socket, &req->object.music_sent, sizeof(music_req), 0) == -1)
        {
            perror("Error sending message");
            return false;
        }
        break;

    case PHOTO_SERVER:
        if (send(cs_client->socket, &req->object.photo_sent, sizeof(photo_req), 0) == -1)
        {
            perror("Error sending message");
            return false;
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

void build_photo(photo_req *photo_sent)
{
    char c;
    printf("\nTítulo: ");
    scanf("%c\n", &c);
    fgets(photo_sent->title, 32, stdin);
    printf("\nModelo de cor: ");
    fgets(photo_sent->color_model, 32, stdin);
    printf("\nWidth: ");
    scanf("%d", &photo_sent->width);
    printf("\nHeigth: ");
    scanf("%d", &photo_sent->heigth);
    photo_sent->req = POST;
}

void video_id(video_req *video_sent)
{
    printf("\nInsira o ID do vídeo a ser buscado: ");
    scanf("%d", &video_sent->id);
    video_sent->req = GET;
}

void music_id(music_req *music_sent)
{
    printf("\nInsira o ID da música a ser buscada: ");
    scanf("%d", &music_sent->id);
    music_sent->req = GET;
}

void photo_id(photo_req *photo_sent)
{
    printf("\nInsira o ID do vídeo a ser buscado: ");
    scanf("%d", &photo_sent->id);
    photo_sent->req = GET;
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
                video_id(&req.object.video_sent);
                break;
            }

            if (!send_message(&cs_client, &req))
            {
                perror("\nFalha no envio da mensagem.");
                exit(EXIT_FAILURE);
            }

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
                music_id(&req.object.music_sent);
                break;
            }

            if (!send_message(&cs_client, &req))
            {
                perror("\nFalha no envio da mensagem.");
                exit(EXIT_FAILURE);
            }

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
            req.server = PHOTO_SERVER;

            printf("\nEntre com a requisição:\n[0] GET\n[1] POST\n");
            scanf("%d", &action);

            switch (action)
            {
            case POST:
                build_photo(&req.object.photo_sent);
                break;

            case GET:
                photo_id(&req.object.photo_sent);
                break;
            }

            if (!send_message(&cs_client, &req))
            {
                perror("\nFalha no envio da mensagem.");
                exit(EXIT_FAILURE);
            }

            photo photo_recivied;

            read(cs_client.socket, &photo_recivied, sizeof(photo));

            printf("\n\tObjeto recebido da requisição %d\n", req.object.photo_sent.req);
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