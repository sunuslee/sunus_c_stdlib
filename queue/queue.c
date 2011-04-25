#include <stdio.h>
#include  "queue.h"
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
