#include <common/common.h>

typedef enum _link_flags_t
{
        flag_link_new_with_data =    1 << 0,
        flag_link_delete_with_data = 1 << 1,
}link_flag;
#define link_list_new_node(head, data, flag)                                    \
do                                                                              \
{                                                                               \
                                                                                \
        CALLOC_S(struct link_list, head, 1, sizeof(struct link_list));          \
        head->plink.free_addr = head;                                           \
        head->pdata = (void *)(flag&flag_link_new_with_data  ? data : NULL) ;   \
}while(0)
/*
 *In fact, They're the same;
 */
#define link_list_get_prev(ptr)                 (ptr->plink).prev
#define link_list_get_next(ptr)                 (ptr->plink).next
#define link_list_get_data(ptr)                 (ptr->pdata)
#define link_list_delet_node(ptr)               free(((ptr->plink).free_addr))
#define link_list_delete_data(ptr)              free(ptr->pdata)

#define link_list_insert_head(old_head, new_head)                               \
do                                                                              \
{                                                                               \
        link_list_get_prev(old_head) = new_head;                                \
        link_list_get_next(new_head) = old_head;                                \
        old_head = new_head;                                                    \
}while(0)



#define link_list_insert_tail(head, new_tail)                                   \
do                                                                              \
{                                                                               \
        for(struct link_list *p = head; ;   )                                   \
        {                                                                       \
                if(link_list_next(p) == NULL)                                   \
                        {                                                       \
                                link_list_next(p) = new_tail;                   \
                                break;                                          \
                        }                                                       \
                else                                                            \
                        p = link_list_next(p)                                   \
        }                                                                       \
}while(0)

#define link_list_delete_head(head, flag)                                       \
do                                                                              \
{                                                                               \
        if(flag&flag_link_delete_with_data)                                     \
                link_list_delete_data(head);                                    \
        head = link_list_get_next(head);                                        \
        link_list_delet_node(link_list_get_prev(head));                         \
        link_list_get_prev(head) = NULL;                                        \
}while(0)

#define link_list_delete_tail(head, flag)                                       \
do                                                                              \
{                                                                               \
        for(struct link_list *p = head ; ;)                                     \
                if(link_list_get_next(p) == NULL)                               \
                        {                                                       \
                                if(flag&flag_link_delete_with_data)             \
                                        link_list_delete_data(p);               \
                                link_list_get_next(link_list_get_prev(p)) = NULL;\
                                link_list_delet_node(p);                        \
                                break;                                          \
                        }                                                       \
                else                                                            \
                        p = link_list_get_next(p);                              \
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
