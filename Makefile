GCC = gcc -Wall -Werror

.PHONY: all 

all: main1 main2

main1: thread.c 
	$(GCC) thread.c -o thread -lpthread
		
main2: thread_shop.c 
	$(GCC) thread_shop.c -o thread_shop -lpthread


