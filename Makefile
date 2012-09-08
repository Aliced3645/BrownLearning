CC = gcc
DEBUGFLAGS = -g -Wall
#CFLAGS = -D_REENTRANT $(DEBUGFLAGS) -D_XOPEN_SOURCE=500
LDFLAGS = -lpthread -pthread

all: network_exercise thread_exercise server client

network_exercise: network_exercise.c
thread_exercise: thread_exercise.c
server: server.c
client: client.c

clean:
	rm -rf network_exercise thread_exercise
