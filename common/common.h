#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int select_cmp_type(const char *type);
int valcmp(int type, void *a_addr, void *b_addr); 
void cmptest(const char *type, void *a_addr, void *b_addr);


#define MALLOC_S(type, ptr, size)               \
do                                              \
{                                               \
        ptr = (type *)malloc(size);             \
        if(!ptr)                                \
                printf("In malloc"              \
                        "Out Of Memory\n");     \
}while(0)                                       

#define CALLOC_S(type, ptr, nelem, elem_size)   \
do                                              \
{                                               \
        ptr = (type *)calloc(nelem,elem_size);  \
        if(!ptr)                                \
                printf("In calloc"              \
                        "Out Of Memory\n");     \
}while(0)                                       
