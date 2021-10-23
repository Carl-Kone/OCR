LDFLAGS = -pthread -lpthread
CFLAGS = -g -Wall -Werror
main: neuralnetwork.o
	$(CC) $(LDFLAGS) -o main main.o neuralnetwork.o -lm

neuralnetwork.o: neuralnetwork.c main.c
	$(CC) $(CFLAGS) -c neuralnetwork.c main.c 

clean:
	rm *.o main
