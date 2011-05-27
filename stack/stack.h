#include "common/common.h"
struct _stack
{
        void *button;
        void *top;
        void *sp;
        int elem_size;
        int stack_size;
        void *free_addr;
};

#define stack_push(stack_name, ele_addr)                                                                        \
do                                                                                                              \
{                                                                                                               \
        if(((uint32_t)(stack_name->sp) + (uint32_t)(stack_name->elem_size)) > (uint32_t)stack_name->top)        \
        {                                                                                                       \
                printf("ERROR : sp + elem_size > top\n");                                                       \
                break;                                                                                          \
        }                                                                                                       \
        stack_name->sp += stack_name->elem_size;                                                                \
        memmove(stack_name->sp, (void *)ele_addr, stack_name->elem_size);                                       \
}while(0)


#define stack_pop(stack_name)                                                                                   \
        ((stack_name->sp - stack_name->elem_size) >= stack_name->button ?                                       \
        (stack_name->sp -= stack_name->elem_size , (void *)(stack_name->sp + stack_name->elem_size)): NULL)



#define stack_destory(stack_name)                                                                               \
do                                                                                                              \
{                                                                                                               \
        assert(stack_name->button);                                                                             \
        free(stack_name->button);                                                                               \
        if(stack_name->free_addr == NULL)                                                                       \
                break;                                                                                          \
        free(stack_name->free_addr);                                                                            \
}while(0)

#define stack_new(stack_name, n, size)                                  \
struct _stack *stack_name;                                              \
do                                                                      \
{                                                                       \
        MALLOC_S(struct _stack, stack_name, sizeof(struct _stack));     \
        stack_name->stack_size = n * size;                              \
        MALLOC_S(char,  stack_name->button, stack_name->stack_size);    \
        stack_name->top = stack_name->button + n * size;                \
        stack_name->sp = stack_name->button - size;                     \
        stack_name->elem_size = size;                                   \
}while(0)
void stack_test();
