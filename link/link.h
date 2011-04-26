#include <common/common.h>
#define get_new_link(head, data)                                                \
do                                                                              \
{                                                                               \
        CALLOC_S(struct link_list, head, 1, sizeof(struct link_list));          \
        head->plink.free_addr = head;                                           \
        head->pdata = (void *)(data ? data : NULL) ;                            \
}while(0)

/*
 *In fact, They're the same;
 */
#define get_new_link_node(pnode, data)  get_new_link(pnode, data)      

#define link_list_prev(ptr)         (ptr->plink).prev                
#define link_list_next(ptr)         (ptr->plink).next
#define link_list_free_node(ptr)        free((ptr->plink).free_addr)

#define link_head_insert(old_head, new_head)                                    \
do                                                                              \
{                                                                               \
        link_list_prev(old_head) = new_head;                                    \
        link_list_next(new_head) = old_head;                                    \
        old_head = new_head;                                                    \
}while(0)



#define link_tail_insert(head, new_tail)                                        \
do                                                                              \
{                                                                               \
        for(struct link_list *p = head; ;   )                                   \
                if(link_list_next(p) == NULL)                                   \
                        {                                                       \
                                link_list_next(p) = new_tail;                   \
                                break;                                          \
                        }                                                       \
                else                                                            \
                        p = link_list_next(p)                                   \
}while(0)

#define link_delete_head(head)                                                  \
do                                                                              \
{                                                                               \
        head = link_list_next(head);                                            \
        free((head->plink.prev)->plink.free_addr);                              \
        link_list_prev(head) = NULL;                                            \
}while(0)

#define link_delete_tail(head)                                                  \
do                                                                              \
{                                                                               \
        for(struct link_list *p = head ; ;)                                     \
                if(link_list_next(p) == NULL)                                   \
                        {                                                       \
                                ((link_list_prev(p))->plink).next = NULL;       \
                                link_list_free_node(p);                         \
                                break;                                          \
                        }                                                       \
                else                                                            \
                        p = link_list_next(p);                                  \
}while(0)
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
