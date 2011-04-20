/**************************************************************************************************************************/
/*      This is my project to prepare my intership exams                                                                  */
/*      Feature:                                                                                                          */
/*                                                                                                                        */
/*                                                                                                                        */
/**************************************************************************************************************************/


#include <stdio.h>
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef int bool;
typedef int stack_t;
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


