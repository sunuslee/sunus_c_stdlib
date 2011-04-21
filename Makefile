# This make file is use to parpare my intership exams

TOP = .
CFLAGS := -Wall -std=c99 -g -I$(TOP)
link_test :  common.o link.o main.o
	gcc -o link_test common.o link.o main.o
stack_test: stack.o main.o
	gcc -o stack_test stack.o main.o
stack.o : ./stack/stack.c ./stack/stack.h
	gcc -c $(CFLAGS) ./stack/stack.c ./stack/stack.h
common.o : ./common/common.c ./common/common.h ./include/MyAlgo.h
	gcc -c $(CFLAGS) ./common/common.c ./common/common.h ./include/MyAlgo.h
heap.o : ./heap/heap.c ./heap/heap.h ./common/common.h
	gcc -c $(CFLAGS) ./heap/heap.c ./heap/heap.h ./common/common.h
#main.o : ./main.c ./heap/heap.h
#	gcc -c $(CFLAGS) ./main.c ./heap/heap.h 
link.o : ./link/link.c ./link/link.h ./common/common.h
	gcc -c $(CFLAGS) ./link/link.c ./link/link.h ./common/common.h
main.o : ./main.c ./link/link.h
	gcc -c $(CFLAGS) ./main.c ./link/link.h
clean :
	rm -rf heap_test stack_test stack.o common.o heap.o main.o
tags :
	ctags -R
	cscope -Rbq
