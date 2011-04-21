#include <include/MyAlgo.h>
#define MAX_STACK_NR 10
struct _stack
{
        void *button;
        void *top;
        void *sp;
        int elem_size;
        int stack_size;
        bool free;
}stack[MAX_STACK_NR];
stack_t get_stack(int elem_nr, size_t elem_size);
void stack_test();
