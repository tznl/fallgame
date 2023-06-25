CC = clang

SRC = codepoints.c main.c scenemanager.c define.c 
SRC += scene/title.c scene/world.c
CFLAGS = -std=c89 -lraylib -lGL -lm -lpthread -lX11 -lglfw -g -Wall
LIBDIRS = -L/usr/X11R6/lib/ -L/usr/local/lib/
INCDIRS = -I/usr/local/include/ -I/usr/X11R6/include/
ANDROIDDIR = ~/githubdirs/Raymob/app/src/main/
make:

	$(CC) $(SRC) -o ../run $(LIBDIRS) $(INCDIRS) $(CFLAGS)

android:

	cp -r ./* $(ANDROIDDIR)cpp
	cp -r ../assets/ $(ANDROIDDIR)
	
	rm $(ANDROIDDIR)/cpp/run.sh

clean:

	rm -rf ../assets/save
