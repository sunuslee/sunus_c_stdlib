
/**************************************************************************************************************************/
/*      This is my project to prepare my internship exams                                                                 */
/*      Feature:                                                                                                          */
/*                                                                                                                        */
/*                                                                                                                        */
/**************************************************************************************************************************/
#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef int bool;
typedef uint32_t flag_t; 
#define FALSE 0
#define  TRUE !FALSE
// Macros

// Get a element's offset of it's struct
#define OFFSET(type,elem) ((int32_t)(&(((struct type *)0)->elem)))

// MISC
#define MAX(_a, _b)                     \
({                                      \
        typeof(_a) __a = (_a);          \
        typeof(_b) __b = (_b);          \
        __a >= __b ? __a : __b ;        \
})

#define MIN(_a, _b)                     \
({                                      \
        typeof(_a) __a = (_a);          \
        typeof(_b) __b = (_b);          \
        __a >= __b ? __b : __a ;        \
})




#define MALLOC_S(type, ptr, size)               \
do                                              \
{                                               \
        ptr = (type *)malloc(size);             \
        assert(ptr);                            \
}while(0)                                       

#define CALLOC_S(type, ptr, nelem, elem_size)   \
do                                              \
{                                               \
        ptr = (type *)calloc(nelem,elem_size);  \
        assert(ptr);                            \
}while(0)                                       


#define DEBUG(on, val)                                                  \
do                                                                      \
{                                                                       \
        if(on)                                                          \
                {                                                       \
                printf("Debug Info :%s , %s , %d , val = %08x\n",       \
                        __FILE__,__func__,__LINE__,(uint32_t)(val));    \
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
                printf("Debug Info :%s , %s , %d , val = %08x\n",       \
                        __FILE__,__func__,__LINE__,(uint32_t)(val));    \
                printf(info,##__VA_ARGS__);                             \
                        /* ##__VA_ARGS__ is supported by GCC ONLY!*/    \
                while(getchar() != 'c')                                 \
                        /* Press 'C' to continue */        ;            \
                }                                                       \
}while(0)

int select_cmp_type(const char *type);
int valcmp(int type, void *a_addr, void *b_addr); 
void cmptest(const char *type, void *a_addr, void *b_addr);
#endif
