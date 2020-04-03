GCC = gcc -Wall -Werror

.PHONY: all 

all: main

main: thread.c 
	$(GCC) thread.c -o thread -lpthread
		


