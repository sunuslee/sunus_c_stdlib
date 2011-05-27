#include "stack/stack.h"
#include "common/common.h"

void stack_test()
{
        int i = 0,j = 0;
        int *p;
        stack_new(intstack, 5, sizeof(int));
        for(i = 0 ; i < 5 ; i++)
        {
                stack_push(intstack,&i);
                printf("%d pushed\n",i);
        }
        stack_new(newstack, 10, sizeof(int));
        for(i = 0x1234567; j < 10; i++,j++)
        {
                stack_push(newstack,&i);
                printf("%d pushed\n",i);
        }
        for(i = 0; i < 5 ; i++)
        {
                p = (int *)(stack_pop(intstack));
                printf("p = %08x\n",(uint32_t)p);
                if(p != NULL)
                        printf("*p = %d poped\n",*p);
                else
                        printf("p == NULL!\n");
        }
        stack_destory(intstack);
}
