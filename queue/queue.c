#include <stdio.h>
#include  "queue.h"

/* Compare to queue_test, v2 is way better!
 * So use queue_test_v2!
 */

/* No More V2*
 * i re-write them all
 */
void queue_test_v2()
{
        int i;
        char ppdata;
        char datas[] = "abcde";
        char datas2[] = "fgh";
        queue_new(que, 5, char);
        for(i = 0; i < 5; i++)
        {
                queue_enqueue(que, &(datas[i]));
                printf("%c enqueued\n",datas[i]);
        }
        for(i = 0; i < 3; i++)
        {
                ppdata = queue_dequeue(que);
                printf("%c dequeued\n",ppdata);
        }
        for(i = 0; i < 3; i++)
        {
                queue_enqueue(que, &(datas2[i]));
                printf("%c enqueued\n",datas2[i]);
        }
        queue_enqueue(que, &(datas[i]));
        printf("%c enqueued\n",datas[i]);
        for(i = 0; i < 5; i++)
        {
                ppdata = queue_dequeue(que);
                printf("%c dequeued\n",ppdata);
        }
        ppdata = queue_dequeue(que);
        printf("%c dequeued\n",ppdata);
        ppdata = queue_dequeue(que);
        printf("%c dequeued\n",ppdata);

        queue_new(otherque, 5, char);
        for(i = 0; i < 5; i++)
        {
                queue_enqueue(otherque, &(datas[i]));
                printf("%c enqueued\n",datas[i]);
        }
        for(i = 0; i < 3; i++)
        {
                ppdata = queue_dequeue(otherque);
                printf("%c dequeued\n",ppdata);
        }
        for(i = 0; i < 3; i++)
        {
                queue_enqueue(otherque, &(datas2[i]));
                printf("%c enqueued\n",datas2[i]);
        }
        queue_enqueue(otherque, &(datas[i]));
        printf("%c enqueued\n",datas[i]);
        for(i = 0; i < 5; i++)
        {
                ppdata = queue_dequeue(otherque);
                printf("%c dequeued\n",ppdata);
        }
        ppdata = queue_dequeue(otherque);
        printf("%c dequeued\n",ppdata);
        ppdata = queue_dequeue(otherque);
        printf("%c dequeued\n",ppdata);
}

