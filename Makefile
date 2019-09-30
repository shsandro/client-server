CC=gcc
OUT=out

MODELS=models
SERVER=server
CLIENT=client

SRC_VIDEO=$(MODELS)/video.c
SRC_MUSIC=$(MODELS)/music.c
SRC_PHOTO=$(MODELS)/photo.c

SRC_CLIENT=$(CLIENT)/client.c

SRC_NETWORK=cs_network.c 

SERVER_VIDEO=$(SERVER)/video_server.c
SERVER_MUSIC=$(SERVER)/music_server.c
SERVER_PHOTO=$(SERVER)/photo_server.c

client:
	$(CC) -lexplain $(SRC_CLIENT) $(SRC_NETWORK) $(SRC_VIDEO) -o client.out

video_server:
	$(CC) -lexplain $(SERVER_VIDEO) $(SRC_NETWORK) $(SRC_VIDEO) $(SRC_MUSIC) -o video_server.out

music_server:
	$(CC) -lexplain $(SERVER_MUSIC) $(SRC_NETWORK) $(SRC_MUSIC) $(SRC_VIDEO) -o music_server.out

photo_server:
	$(CC) -lexplain $(SERVER_PHOTO) $(SRC_NETWORK) -o photo_server.out