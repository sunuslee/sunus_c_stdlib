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

struct _stack
{
        void *button;
        void *top;
        void *sp;
        int elem_size;
        int stack_size;
        struct _stack *free_addr;
};
int _get_stack(struct _stack *stack_name, int elem_nr, size_t elem_size);
void stack_test();
