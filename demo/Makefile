CC=gcc
CFLAGS=-I../

all: demo

demo:
	$(CC) $(CFLAGS) -o demo ../pthread_barrier.c demo.c -lpthread

clean:
	rm demo
