LDFLAGS = -pthread -lpthread
CFLAGS = -g -Wall -Werror
main: backpropagation.o neuralnetwork.o
	$(CC) $(LDFLAGS) -o main main.o neuralnetwork.o -lm

backpropagation.o: main.c
	$(CC) $(CFLAGS) -c main.c 


neuralnetwork.o: neuralnetwork.c
	$(CC) $(CFLAGS) -c neuralnetwork.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o backprop
