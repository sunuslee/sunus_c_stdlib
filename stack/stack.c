#include "stack/stack.h"
#include "common/common.h"

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
