# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -fsanitize=address -Wl,-V
LDLIBS= `pkg-config --libs sdl SDL_image` -lm

all: main

main : pixel_operations.o display.o remove_color.o main.o gaussian_filter.o sobel_filter.o hough.o

remove_color.o : pixel_operations.h
gaussian_filter.o : pixel_operations.h
solbel_filter.o : pixel_operations.h
hough.o : pixel_operations.h display.h
main.o : display.h remove_color.h gaussian_filter.h sobel_filter.h hough.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} image2.jpg
	${RM} *~

# END
