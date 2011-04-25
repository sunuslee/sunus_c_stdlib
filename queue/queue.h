#include "common/common.h"
struct _queue
{
        void *head;
        void *tail;
        void *cur_head;
        void *cur_tail;
        int elem_size;
        int queue_size;
        int available_slot;
        struct _queue *free_addr; // Points to the struct itself;
};

int _get_queue(struct _queue *queue_name, int elem_nr, int elem_size);
void queue_test();

#define get_queue(queue_name, elem_nr, elem_size)                       \
struct _queue *queue_name;                                              \
do                                                                      \
{                                                                       \
        MALLOC_S(struct _queue, queue_name, sizeof(struct _queue));     \
        if(_get_queue(queue_name, elem_nr, elem_size) == 0)             \
                printf("get queue %s succeed!\n",#queue_name);          \
        else                                                            \
                printf("get queue %s fail!\n",#queue_name);             \
}while(0)

#define enqueue(queue_name, ele_addr)                                                           \
do                                                                                              \
{                                                                                               \
        if(queue_name->available_slot)                                                          \
        {                                                                                       \
                memmove(queue_name->cur_tail, ele_addr, queue_name->elem_size);                 \
                queue_name->cur_tail += queue_name->elem_size;                                  \
                if(queue_name->cur_tail == queue_name->tail)                                    \
                        queue_name->cur_tail = queue_name->head;                                \
                queue_name->available_slot--;                                                   \
                if(!queue_name->available_slot)                                                 \
                {                                                                               \
                        printf("enqueue %s is fulled!\n",#queue_name);                          \
                }                                                                               \
        }                                                                                       \
        else                                                                                    \
                printf("enqueue %s is fulled!,CANNOT enqueue! available_slot = %d\n",           \
                        #queue_name,queue_name->available_slot);                                \
}while(0)

#define dequeue(queue_name)                                                                     \
(queue_name->available_slot == (queue_name->queue_size / queue_name->elem_size))  ?             \
                (printf("queue %s is empty!\n",#queue_name),NULL)               :               \
                (queue_name->available_slot++,queue_name->cur_head += queue_name->elem_size,    \
                 (queue_name->cur_head == queue_name->tail ?                                    \
                (queue_name->cur_head = queue_name->head, queue_name->tail - queue_name->elem_size) :\
                 (queue_name->cur_head - queue_name->elem_size)))


