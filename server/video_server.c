#include "../include/cs_network.h"
#include "../models/include/video.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, const char **argv)
{
    server cs_server;
    int accepted_socket;
    int pipe_fd[2];
    pid_t pid;

    init_video_db();

    cs_server.init = init_server;

    if (!cs_server.init(&cs_server, "./hosts/hostfile_server1"))
    {
        printf("Falha na criação do servidor.\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe_fd) < 0)
    {
        perror("Falha ao criar pipe.\n");
    }

    write(pipe_fd[1], &video_db, sizeof(video_data_base));

    while ((accepted_socket = accept(cs_server.socket, (struct sockaddr *)&cs_server.socket_address, &cs_server.sockaddr_lenght)) > 0)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Não foi possivel criar fork.\n");
            return false;
        }
        else if (pid == 0)
        {
            read(pipe_fd[0], &video_db, sizeof(video_data_base));
            printf("Conexão estabelecida.\n");

            video_req video_recivied;

            int v = read(accepted_socket, &video_recivied, sizeof(video_req));
            if (v >= 0)
            {
                video video_response;
                switch (video_recivied.req)
                {
                case POST:
                    video_response = create_video(video_recivied);
                    printf("\n\tPOST recebido\n");
                    printf("\tNome: %s\n", video_recivied.name);
                    printf("\tDiretor: %s\n", video_recivied.director);
                    printf("\tGênero: %s\n", video_recivied.gender);
                    printf("\tDuração: %.2f\n", video_recivied.length);
                    printf("\tRequisição: %d\n", video_recivied.req);
                    break;

                case GET:
                    video_response = get_video(video_recivied.id);
                    printf("\n\tGET recebido\n");
                    printf("\tID: %d\n", video_recivied.id);
                    break;
                }

                write(accepted_socket, &video_response, sizeof(video));
                write(pipe_fd[1], &video_db, sizeof(video_data_base));
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("Leitura da requisição falhou.\n");
                write(accepted_socket, "REQ_FAILED", 11);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (accepted_socket < 0)
    {
        perror("Requisição falhou.\n");
        return false;
    }

    shutdown(cs_server.socket, 2);

    return 0;
}