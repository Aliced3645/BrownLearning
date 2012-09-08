all:
	gcc -c thread_exercise.c
	gcc -o thread thread_exercise.o -lpthread
