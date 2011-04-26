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

#define get_queue_v2(queue_name, elem_nr, elem_type)                                    \
struct _queue *queue_name;                                                              \
static elem_type *fetch_##queue_name;                                                   \
do                                                                                      \
{                                                                                       \
        MALLOC_S(struct _queue, queue_name, sizeof(struct _queue));                     \
        MALLOC_S(elem_type, queue_name->head, sizeof(elem_type) * elem_nr);             \
        queue_name->cur_head = queue_name->cur_tail = queue_name->head;                 \
        queue_name->tail = (void *)(queue_name->head + sizeof(elem_type) * elem_nr);    \
        queue_name->free_addr = queue_name;\
        queue_name->elem_size = sizeof(elem_type);\
        queue_name->queue_size = sizeof(elem_type) * elem_nr;\
        queue_name->available_slot = elem_nr;\
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

#define name2str(name) #name
#define dequeue_v2(queue_name)                                                                          \
({                                                                                                      \
if(queue_name->available_slot == (queue_name->queue_size / queue_name->elem_size))                      \
        {                                                                                               \
                printf("queue %s is empty!\n",#queue_name);                                             \
                fetch_##queue_name = NULL;                                                              \
        }                                                                                               \
else                                                                                                    \
        {                                                                                               \
                queue_name->available_slot++;                                                           \
                queue_name->cur_head += queue_name->elem_size;                                          \
                if(queue_name->cur_head == queue_name->tail )                                           \
                {                                                                                       \
                        queue_name->cur_head = queue_name->head;                                        \
                        fetch_##queue_name = (queue_name->tail - queue_name->elem_size);                \
                }                                                                                       \
                else                                                                                    \
                        fetch_##queue_name = (queue_name->cur_head - queue_name->elem_size);            \
        }                                                                                               \
printf("val of %s = %08x\n",name2str(fetch_##queue_name),(uint32_t)fetch_##queue_name);                 \
*fetch_##queue_name;                                                                                    \
})
