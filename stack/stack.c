#include "stack/stack.h"
#include "common/common.h"
#define push(stack_name, ele_addr)  do                                                                                  \
{                                                                                                                       \
        if(((uint32_t)(stack_name->sp) + (uint32_t)(stack_name->elem_size)) > (uint32_t)stack_name->top)                \
        {                                                                                                               \
                printf("ERROR : sp + elem_size > top\n");                                                               \
                break;                                                                                                  \
        }                                                                                                               \
        stack_name->sp += stack_name->elem_size;                                                                        \
        memmove(stack_name->sp, (void *)ele_addr, stack_name->elem_size);                                               \
}while(0)                                                                                                               

#define pop(stack_name)                                                                                                 \
                (stack_name->sp - stack_name->elem_size) >= stack_name->button ?                                        \
        stack_name->sp -= stack_name->elem_size , (void *)(stack_name->sp + stack_name->elem_size)                      \
        :                                                                                                               \
        NULL                                                                                                            

#define stack_destory(stack_name)                                                                                       \
do                                                                                                                      \
{                                                                                                                       \
        if(stack_name->button == NULL)                                                                                  \
                printf("STACK CANNOT FREE! BUTTON == NULL\n")                                                           \
        free(stack_name->button);                                                                                       \
        if(stack_name->free == NULL)                                                                                    \
                break;                                                                                                  \
        free(stack_name->free)                                                                                          \
}while(0)

#define get_stack(stack_name, elem_nr, elem_size)                                                                       \
struct _stack *stack_name;                                                                                              \
do                                                                                                                      \
{                                                                                                                       \
MALLOC_S(struct _stack, stack_name, sizeof(struct _stack));                                                             \
if(_get_stack(stack_name, elem_nr, elem_size) == 0)                                                                     \
        printf("get stack succeed!\n");                                                                                 \
else                                                                                                                    \
        printf("get stack fail!\n");                                                                                    \
}while(0)                                                                                                               

int _get_stack(struct _stack *stack_name, int elem_nr, size_t elem_size)
{
        int size = elem_size * elem_nr;
        MALLOC_S(void, stack_name->button, size);
        stack_name->top = stack_name->button + size;
        stack_name->sp = stack_name->button;
        stack_name->elem_size = elem_size;
        stack_name->stack_size = size;
        stack_name->free_addr = stack_name;
        return 0;
}

void stack_test()
{
        int i = 0;
        int *p;
        get_stack(st,5, sizeof(int));
        for(i = 0 ; i < 5 ; i++)
        {
                push(st,&i);
        }
        for(i = 0; i < 5 ; i++)
        {
                p = (int *)(pop(st));
                printf("p = %08x\n",(uint32_t)p);
                if(p != NULL)
                        printf("*p = %d poped\n",*p);
                else
                        printf("p == NULL!\n");
        }
}
