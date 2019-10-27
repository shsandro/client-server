#include "../include/cs_network.h"
#include "../models/include/video.h"
#include "../models/include/music.h"
#include "../models/include/photo.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned int VIDEO_SIZE = sizeof(video_req);
const unsigned int MUSIC_SIZE = sizeof(music_req);
const unsigned int PHOTO_SIZE = sizeof(photo_req);

unsigned int max_size()
{
    return (VIDEO_SIZE > MUSIC_SIZE) ? (VIDEO_SIZE > PHOTO_SIZE) ? VIDEO_SIZE : PHOTO_SIZE : (MUSIC_SIZE > PHOTO_SIZE) ? MUSIC_SIZE : PHOTO_SIZE;
}

int main(int argc, const char **argv)
{
    proxy cs_proxy;
    int accepted_socket;
    pid_t pid;
    int action;

    void *req = malloc(max_size());

    cs_proxy.init = init_proxy;

    if (!cs_proxy.init(&cs_proxy))
    {
        perror("Falha na criação do proxy.\n");
        exit(EXIT_FAILURE);
    }

    while ((accepted_socket = accept(cs_proxy.socket, (struct sockaddr *)&cs_proxy.socket_address, &cs_proxy.sockaddr_lenght)) > 0)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Não foi possivel criar fork.\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            printf("Conexão estabelecida.\n");

            int req_socket;

            if ((req_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                perror("\n Socket creation error \n");
                exit(EXIT_FAILURE);
            }

            int req_size = read(accepted_socket, req, max_size());

            if (req_size == VIDEO_SIZE)
            {
                printf("\nEnviando para o servidor de vídeos\n");
                video_req video_sent;

                memcpy(&video_sent, req, VIDEO_SIZE);

                if (connect(req_socket, (struct sockaddr *)&cs_proxy.socket_server_address[VIDEO_SERVER], cs_proxy.sockaddr_lenght) < 0)
                {
                    perror("Conexão falhou.\n");
                    return 0;
                }

                if (send(req_socket, &video_sent, sizeof(video_req), 0) == -1)
                {
                    perror("Error sending message\n");
                }

                video video_recivied;

                read(req_socket, &video_recivied, sizeof(video));

                write(accepted_socket, &video_recivied, sizeof(video));
            }
            else if (req_size == MUSIC_SIZE)
            {
                printf("\nEnviando para o servidor de músicas\n");
                music_req music_sent;

                memcpy(&music_sent, req, MUSIC_SIZE);

                if (connect(req_socket, (struct sockaddr *)&cs_proxy.socket_server_address[MUSIC_SERVER], cs_proxy.sockaddr_lenght) < 0)
                {
                    perror("Conexão falhou.\n");
                    return 0;
                }

                if (send(req_socket, &music_sent, sizeof(music_req), 0) == -1)
                {
                    perror("Error sending message\n");
                }

                music music_recivied;

                read(req_socket, &music_recivied, sizeof(music));

                write(accepted_socket, &music_recivied, sizeof(music));
            }
            else if (req_size == PHOTO_SIZE)
            {
                printf("\nEnviando para o servidor de fotos\n");
                photo_req photo_sent;

                memcpy(&photo_sent, req, PHOTO_SIZE);

                if (connect(req_socket, (struct sockaddr *)&cs_proxy.socket_server_address[PHOTO_SERVER], cs_proxy.sockaddr_lenght) < 0)
                {
                    perror("Conexão falhou.\n");
                    return 0;
                }

                if (send(req_socket, &photo_sent, sizeof(photo_req), 0) == -1)
                {
                    perror("Error sending message\n");
                }

                photo photo_recivied;

                read(req_socket, &photo_recivied, sizeof(photo));

                write(accepted_socket, &photo_recivied, sizeof(photo));
            }
        }
    }

    shutdown(cs_proxy.socket, 2);

    return 0;
}