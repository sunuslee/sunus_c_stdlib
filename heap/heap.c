#include <stdlib.h>
#include "heap.h"
#define LEFT(i) (i<<1)
#define RIGHT(i) ((i<<1) + 1)

void max_heapify(void *array, int i, int32_t nelem, size_t elem_size, int32_t offset, int i_type)
{
        void *largest = array + i * elem_size; // if it's STRUCT,THEN largest + offset is the CMP-VALUE!
        void *pswap = malloc(elem_size);
        int new_index;
        printf("\nARGUMENT CHECK\n array = %08x\ni = %d\nnelem = %d\nelem_size = %d\noffset = %d\ni_type = %d\n",
                        (uint32_t)array,i,nelem,elem_size,offset,i_type);
        if(pswap == NULL)
                printf("%s Out Of Memory!\n",__func__);
        if((LEFT(i) < nelem) && ((valcmp(i_type, largest + offset, array + (LEFT(i)) * elem_size + offset)) < 0))
        {
                largest =  array + LEFT(i) * elem_size;
                new_index = LEFT(i);
        }
        if((RIGHT(i) < nelem) && ((valcmp(i_type, largest + offset, array + (RIGHT(i)) * elem_size + offset)) < 0))
        {
                largest =  array + RIGHT(i) * elem_size;
                new_index = RIGHT(i);
        }
        if(largest != array + i * elem_size)
        {
                memmove(pswap, largest, elem_size);
                memmove(largest, array + i * elem_size, elem_size);
                memmove(array + i * elem_size, pswap, elem_size);
                free(pswap);
                max_heapify(array, new_index, nelem, elem_size, offset, i_type);
        }
}
int build_max_heap(void *array, int32_t nelem, size_t elem_size, int32_t offset, const char *ele_type)
{
        int i = nelem/2;
        int i_type = select_cmp_type(ele_type);
        printf("\nARGUMENT CHECK\n array = %08x\nnelem = %d\nelem_size = %d\noffset = %d\nele_type = %s\n",
                        (uint32_t)array,nelem,elem_size,offset,ele_type);
        for( ; i ; i--)
                max_heapify(array, i, nelem, elem_size, offset, i_type);
        return 0;
}

int heap_sort(void *array, int32_t nelem, size_t elem_size, int32_t offset, const char *ele_type, bool build)
{
        int r;
        void *pswap = malloc(elem_size);
        int i_type = select_cmp_type(ele_type);
        if(build)
        {
                if((r = build_max_heap(array, nelem, elem_size, offset, ele_type)) < 0)
                        printf("%s error\n",__func__);
        }
        for( ; nelem > 1 ; )
        {
                memmove(pswap, array, elem_size);
                memmove(array, array + (nelem - 1) * elem_size, elem_size);
                memmove(array + (nelem - 1) * elem_size, pswap, elem_size);
                nelem--;
                max_heapify(array, 0, nelem, elem_size, offset, i_type);
        }
        free(pswap);
        return 0;
}

void test_main()
{
        int test1[] = {27,17,3,16,13,10,1,5,7,12,4,8,9,10};
        struct test_str_t
        {
                char a;
                int val;
        };
        struct test_str_t test2[14] = { [0].val=27,[1].val=17,[2].val=3,[3].val=16,[4].val=13,[5].val=10,[6].val=1,
                                      [7].val=5,[8].val=7,[9].val=12,[10].val=4,[11].val=8,[12].val=9,[13].val=10};
        int n1 = sizeof(test1)/sizeof(test1[0]);
        int n2 = sizeof(test2)/sizeof(test2[0]);
        int i;
        heap_sort((void *)test1, n1, sizeof(test1[0]), 0, "int32", TRUE);
        printf("TEST 1 CHECK :\n\n");
        for(i = 0; i < n1; i++ )
                printf("%d\n",test1[i]);
        heap_sort((void *)test2, n2, sizeof(test2[0]), OFFSET(test_str_t, val), "int32", TRUE);
        printf("TEST 2 CHECK :\n\n");
        for(i = 0; i < n2; i++ )
                printf("%d\n",test2[i].val);

}
