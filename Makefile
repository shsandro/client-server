all: client video_server music_server photo_server

client:
	gcc -lexplain client/client.c cs_network.c models/video.c -o client.out

video_server:
	gcc -lexplain server/video_server.c cs_network.c models/video.c -o video_server.out

music_server:
	gcc -lexplain server/music_server.c cs_network.c -o music_server.out

photo_server:
	gcc -lexplain server/photo_server.c cs_network.c -o photo_server.out