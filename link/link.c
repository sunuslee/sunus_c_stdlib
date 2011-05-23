#include "link.h"
void link_test()
{
        struct link_list *phead = NULL;
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
        link_list_new_node(phead, head, flag_link_new_with_data);
        for (i = 0 ; i < 10 ; i++)
        {
                link_list_new_node(newnode, data[i], flag_link_new_with_data);
                link_list_insert_head(phead, newnode);
                printf("head %s : head NEXT : %s",(char *)phead->pdata,(char *)(link_list_get_next(phead)->pdata));
        }
        link_list_delete_head(phead, 0);
        link_list_delete_tail(phead, 0);
        printf("CHECK 1:\n\n");
        for(i = 0 ,pcheck = phead; i < 9 ; i++)
        {
                printf("Node data : %s",(char *)pcheck->pdata);
                pcheck2 = pcheck;
                pcheck = link_list_get_next(pcheck);
                if(pcheck == NULL)
                        printf("LINE 95 : pcheck == NUll!\n");
        }
        printf("CHECK 2:\n\n");
        for(i = 0 ; i < 9 ; i++)
        {
                printf("Node data : %s",(char *)pcheck2->pdata);
                pcheck2 = link_list_get_prev(pcheck2);
                if(pcheck2 == NULL)
                        printf("LINE 104 : pcheck == NUll!\n");
        }
}

