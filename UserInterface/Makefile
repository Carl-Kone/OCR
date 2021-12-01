# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl SDL_image`

all = user_interface

user_interface : user_interface.o

user_interface.o : ../display.h

clean :
	${RM} *.o
	${RM} *.d
	${RM} *#*
	${RM} *~

# END
