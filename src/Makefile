CC = gcc

SRC = main.c scenemanager.c
SRC += scene/title.c
CFLAGS = -std=c99 -lraylib -lGL -lm -lpthread -lX11 -lglfw -g -Wall
LIBDIRS = -L/usr/X11R6/lib/ -L/usr/local/lib/
INCDIRS = -I/usr/local/include/ -I/usr/X11R6/include/

make:
	$(CC) $(SRC) -o ../fallgame/run $(LIBDIRS) $(INCDIRS) $(CFLAGS) 
