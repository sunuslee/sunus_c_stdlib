#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define push(stack_t, ele_addr)  do                                                                                     \
{                                                                                                                       \
        if(((uint32_t)stack[stack_t].sp + (uint32_t)(stack[stack_t].elem_size)) > (uint32_t)stack[stack_t].top)         \
        {                                                                                                               \
                printf("ERROR : sp + elem_size > top\n");                                                               \
                break;                                                                                                  \
        }                                                                                                               \
        stack[stack_t].sp += stack[stack_t].elem_size;                                                                  \
        memmove(stack[stack_t].sp, (void *)ele_addr, stack[stack_t].elem_size);                                         \
}while(0)

#define pop(stack_t)                                                                                                    \
                (stack[stack_t].sp - stack[stack_t].elem_size) >= stack[stack_t].button ?                               \
        stack[stack_t].sp -= stack[stack_t].elem_size , (void *)(stack[stack_t].sp + stack[stack_t].elem_size)          \
        :                                                                                                               \
        NULL                                                                                                            

#define stack_destory(stack_t)                                                                                          \
do                                                                                                                      \
{                                                                                                                       \
        if(stack[stack_t].free == TRUE)                                                                                 \
                break;                                                                                                  \
        free(stack[stack_t].button);                                                                                    \
        stack[stack_t].free = TRUE;                                                                                     \
}while(0)
void stack_init(int nr)
{
        int i;
        for(i = 0; i < nr; i++)
                stack[i].free = TRUE;
}
stack_t get_stack(int elem_nr, size_t elem_size)
{
        int i;
        int size = elem_size * elem_nr;
        for(i = 0; i < MAX_STACK_NR; i++)
        {
                if(stack[i].free == TRUE)
                {
                        stack[i].button = malloc(size);
                        if(stack[i].button == NULL)
                                printf("%s ERROR : Out Of Memory!\n",__func__);
                        stack[i].top = stack[i].button + size;
                        stack[i].sp = stack[i].button;
                        stack[i].elem_size = elem_size;
                        stack[i].stack_size = size;
                        stack[i].free = FALSE;
                        return i;
                }
        }
        printf("%s ERROR : No Free Stack Left!\n",__func__);
        return -1;
}
void stack_test()
{
        int i = 0;
        int *p;
        int st ;
        stack_init(MAX_STACK_NR);
        st = get_stack(5, sizeof(int));
        if(st != -1)
        {
                for(i = 0 ; i < 6 ; i++)
                {
                        push(st,&i);
                }
                for(i = 0; i < 6 ; i++)
                {
                        p = (int *)pop(st);
                        printf("p = %08x\n",(uint32_t)p);
                        if(p != NULL)
                                printf("*p = %d poped\n",*p);
                        else
                                printf("p == NULL!\n");
                }
        }

}
