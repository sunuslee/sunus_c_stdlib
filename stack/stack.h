#include <include/MyAlgo.h>
#define MAX_STACK_NR 10
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
