#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "common/common.h"

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
void link_test()
{
        struct link_list *phead;
        struct link_list *newnode;
        struct link_list *pcheck,*pcheck2;
        char data[][32] = 
        {
        "I AM THE DATA! 1\n",
        "I AM THE DATA! 2\n",
        "I AM THE DATA! 3\n",
        "I AM THE DATA! 4\n",
        "I AM THE DATA! 5\n",
        "I AM THE DATA! 6\n",
        "I AM THE DATA! 7\n",
        "I AM THE DATA! 8\n",
        "I AM THE DATA! 9\n",
        "I AM THE DATA! 10\n",
        };
        char *head = "I AM THE HEAD!\n";
        int i;
        get_new_link(phead, head);
        for (i = 0 ; i < 10 ; i++)
        {
                get_new_link_node(newnode, data[i]);
                link_head_insert(phead, newnode);
                printf("head %s : head NEXT : %s",(char *)phead->pdata,(char *)(link_list_next(phead)->pdata));
        }
        link_delete_head(phead);
        link_delete_tail(phead);
        printf("CHECK 1:\n\n");
        for(i = 0 ,pcheck = phead; i < 9 ; i++)
        {
                printf("Node data : %s",(char *)pcheck->pdata);
                pcheck2 = pcheck;
                pcheck = link_list_next(pcheck);
                if(pcheck == NULL)
                        printf("LINE 95 : pcheck == NUll!\n");
        }
        printf("CHECK 2:\n\n");
        for(i = 0 ; i < 9 ; i++)
        {
                printf("Node data : %s",(char *)pcheck2->pdata);
                pcheck2 = link_list_prev(pcheck2);
                if(pcheck2 == NULL)
                        printf("LINE 104 : pcheck == NUll!\n");
        }
}

