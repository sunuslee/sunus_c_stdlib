# This make file is use to parpare my intership exams

TOP = .
CFLAGS := -Wall -std=gnu99 -g -I$(TOP)
link_test: main.o link.o queue.o common.o
	gcc -o link_test main.o link.o queue.o common.o
queue_test: main.o queue.o common.o
	gcc -o queue_test main.o queue.o common.o
stack_test: main.o stack.o common.o
	gcc -o stack_test main.o stack.o common.o
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
link.o : ./link/link.c ./link/link.h ./common/common.h
	gcc -c $(CFLAGS) ./link/link.c ./link/link.h ./common/common.h
main.o : ./main.c ./link/link.h ./queue/queue.h
	gcc -c $(CFLAGS) ./main.c ./link/link.h ./queue/queue.h
clean :
	rm -rf rbtree_test heap_test stack_test *.o cscope* `find . -name *.gch`

