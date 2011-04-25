# This make file is use to parpare my intership exams

TOP = .
CFLAGS := -Wall -std=gnu99 -g -I$(TOP)
rbtree_test: main.o rbtree.o  common.o queue.o
	gcc -o rbtree_test main.o rbtree.o common.o queue.o
rbtree.o : ./rbtree/rbtree.c ./rbtree/rbtree.h ./common/common.h
	gcc -c $(CFLAGS) ./rbtree/rbtree.c ./rbtree/rbtree.h ./common/common.h
queue.o : ./queue/queue.c ./queue/queue.h ./common/common.h
	gcc -c $(CFLAGS) ./queue/queue.c ./queue/queue.h ./common/common.h
stack.o : ./stack/stack.c ./stack/stack.h common/common.h
	gcc -c $(CFLAGS) ./stack/stack.c ./stack/stack.h common/common.h
common.o : ./common/common.c ./common/common.h
	gcc -c $(CFLAGS) ./common/common.c ./common/common.h
heap.o : ./heap/heap.c ./heap/heap.h ./common/common.h
	gcc -c $(CFLAGS) ./heap/heap.c ./heap/heap.h ./common/common.h
#main.o : ./main.c ./heap/heap.h
#	gcc -c $(CFLAGS) ./main.c ./heap/heap.h 
link.o : ./link/link.c ./link/link.h ./common/common.h
	gcc -c $(CFLAGS) ./link/link.c ./link/link.h ./common/common.h
main.o : ./main.c ./stack/stack.h
	gcc -c $(CFLAGS) ./main.c ./stack/stack.h
clean :
	rm -rf heap_test stack_test stack.o common.o heap.o main.o

