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


#define DEBUG(on, val)                                                  \
do                                                                      \
{                                                                       \
        if(on)                                                          \
                {                                                       \
                printf("Debug Info :%s , %d , val = %08x\n",            \
                                __func__,__LINE__,(uint32_t)(val));     \
                while(getchar() != 'c')                                 \
                       /* Press 'C' to continue */        ;             \
                }                                                       \
}while(0)

/* SAMPLES: 
 * DEBUG_ARGS(1,val,"I ALSO WANT TO CHECK val2 = %d\n",val2);
 * Or
 * DEBUG_ARGS(1,val,"I ALSO WANT TO ADD THIS INFO");
 */
#define DEBUG_ARGS(on, val,info,...)                                    \
do                                                                      \
{                                                                       \
        if(on)                                                          \
                {                                                       \
                printf("Debug Info :%s , %d , val = %08x\n",            \
                                __func__,__LINE__,(uint32_t)(val));     \
                printf(info,##__VA_ARGS__);                             \
                        /* ##__VA_ARGS__ is supported by GCC ONLY!*/    \
                while(getchar() != 'c')                                 \
                        /* Press 'C' to continue */        ;            \
                }                                                       \
}while(0)


