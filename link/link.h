#include <include/MyAlgo.h>
struct link_list
{
        struct link *plink;
        void *pdata;
};
struct link{
        struct link_list *prev;
        struct link_list *next;
};

