//*#include <include/MyAlgo.h>
struct link_list;
struct link{
        struct link_list *prev;
        struct link_list *next;
        struct link_list *free_addr;
};
struct link_list
{
        struct link plink;
        void *pdata;
};
void link_test();
