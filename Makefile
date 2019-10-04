CC=gcc
OUT=out

MODELS=models
SERVER=server
CLIENT=client
PROXY=proxy

SRC_VIDEO=$(MODELS)/video.c
SRC_MUSIC=$(MODELS)/music.c
SRC_PHOTO=$(MODELS)/photo.c

SRC_CLIENT=$(CLIENT)/client.c
SRC_NETWORK=cs_network.c 
SRC_PROXY=$(PROXY)/proxy.c

SERVER_VIDEO=$(SERVER)/video_server.c
SERVER_MUSIC=$(SERVER)/music_server.c
SERVER_PHOTO=$(SERVER)/photo_server.c

all: client proxy video_server music_server photo_server

client:
	$(CC) $(SRC_CLIENT) $(SRC_NETWORK) $(SRC_VIDEO) $(SRC_MUSIC) $(SRC_PHOTO) -o client.out

proxy:
	$(CC) $(SRC_PROXY) $(SRC_NETWORK) $(SRC_VIDEO) $(SRC_MUSIC) $(SRC_PHOTO) -o proxy.out

photo_server:
	$(CC) $(SERVER_PHOTO) $(SRC_NETWORK) $(SRC_PHOTO) -o photo_server.out

video_server:
	$(CC) $(SERVER_VIDEO) $(SRC_NETWORK) $(SRC_VIDEO) -o video_server.out

music_server:
	$(CC) $(SERVER_MUSIC) $(SRC_NETWORK) $(SRC_MUSIC) -o music_server.out


.PHONY: client proxy