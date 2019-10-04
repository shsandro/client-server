#include "./include/music.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_music_db()
{
    for (int i = 0; i < MAX_MUSIC; ++i)
    {
        music_db.musics[i].id = -1;
    }

    music_db.music_id = 0;

    printf("Banco de Dados de músicas inicializado.\n");
}

music create_music(music_req music_recieved)
{
    strcpy(music_db.musics[music_db.music_id].name, music_recieved.name);
    strcpy(music_db.musics[music_db.music_id].singer, music_recieved.singer);
    strcpy(music_db.musics[music_db.music_id].gender, music_recieved.gender);
    strcpy(music_db.musics[music_db.music_id].album, music_recieved.album);
    music_db.musics[music_db.music_id].length = music_recieved.length;
    music_db.musics[music_db.music_id].id = music_db.music_id;
    ++music_db.music_id;
    printf("ID = %d\n", music_db.music_id);
    return music_db.musics[music_db.music_id - 1];
}

music get_music(int id)
{
    if (music_db.musics[id].id == -1)
    {
        printf("ID não cadastrado.\n");
        exit(EXIT_FAILURE);
    }

    return music_db.musics[id];
}