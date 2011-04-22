#include <common/common.h>
#include <include/MyAlgo.h>
#include "queue.h"
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
int _get_queue(struct _queue *queue_name, int elem_nr, int elem_size)
{
        int size = elem_nr * elem_size;
        MALLOC_S(void, queue_name->head, size);
        queue_name->cur_head = queue_name->cur_tail = queue_name->head;
        queue_name->tail = (void *)(queue_name->head + size);
        queue_name->free_addr = queue_name;
        queue_name->elem_size = elem_size;
        queue_name->queue_size = size;
        queue_name->available_slot = elem_nr;
        return 0;
}

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
void queue_test()
{
        int i;
        char *pdata;
        char datas[] = "abcde";
        char datas2[] = "fgh";
        get_queue(que, 5, sizeof(char));
        for(i = 0; i < 5; i++)
        {
                enqueue(que, &(datas[i]));
        }
        for(i = 0; i < 3; i++)
        {
                pdata = (char *)dequeue(que);
                printf("%c dequeued\n",*pdata);
        }
        for(i = 0; i < 3; i++)
                enqueue(que, &(datas2[i]));
        enqueue(que, &(datas[i]));
        for(i = 0; i < 5; i++)
        {
                pdata = (char *)dequeue(que);
                printf("%c dequeued\n",*pdata);
        }
        pdata = (char *)dequeue(que);
}
