#include "rbtree.h"
#include "queue/queue.h"
static struct _rbtree NIL = {.attr = {NULL, NULL, NULL, 'B',NULL}, .pdata = NULL}; // *NEVER* free(NIL)!!
void rbt_insert(struct _rbtree **root, struct _rbtree *node)
{
        struct _rbtree *cur_node = *root;
        if(*root == node)
        {
                COLOR(node) = 'B';
                printf("root inserted! node val = %08x\n",(uint32_t)VAL(node));
                return ;
        }
        while(1)
        {
                if(CMPTYPE(cur_node) != CMPTYPE(node))
                        printf("CURTYPE %08x and NODETYPE %08x UN-MATCHED!\n",CMPTYPE(cur_node),CMPTYPE(node));
                if(VAL(node) > VAL(cur_node))
                {
                        if(RIGHT(cur_node) == &NIL)
                        {
                                RIGHT(cur_node) = node;
                                P(node) = cur_node;
                                goto FOUND;
                        }
                        cur_node = RIGHT(cur_node);
                }
                else
                {
                        if(LEFT(cur_node) == &NIL)
                        {
                                LEFT(cur_node) = node;
                                P(node) = cur_node;
                                goto FOUND;
                        }
                        cur_node = LEFT(cur_node);
                }
        }
FOUND:
        COLOR(node) = 'R';
        rbt_insert_fixup(root,node);
}

void rbt_insert_fixup(struct _rbtree **root,struct _rbtree *node)
{
        struct _rbtree *n = node;
        struct _rbtree *uncle;
        while((COLOR(P(n)) == 'R') || (P(n) == &NIL))
        {
                if(P(n) == &NIL)
                {
                        COLOR(n) = 'B';
                        break;
                }
                uncle = UNCLE(n);
                if(COLOR(uncle) == 'R')
                {
                        COLOR(LEFT(P(P(n)))) = 'B';
                        COLOR(RIGHT(P(P(n)))) = 'B';
                        COLOR(P(P(n))) = 'R';
                        n = P(P(n));
                }
               else if(IS_PARENT_LEFT(n) && (!IS_NODE_LEFT(n))) /* 2 cases that 'parent of n' in the *LEFT* of 'GRANDparent of n'*/
               {
                       LEFT_ROTATE(P(n), n, *root);
                       n = LEFT(n);
               }
               else if(IS_PARENT_LEFT(n) && IS_NODE_LEFT(n))
               {
                       COLOR(P(n)) = 'B';
                       COLOR(P(P(n))) = 'R';
                       RIGHT_ROTATE(P(P(n)), P(n), *root);
               }
               else if((!IS_PARENT_LEFT(n)) && IS_NODE_LEFT(n))/* 2 cases that 'parent of n' in the *RIGHT* of 'GRANDparent of n'*/
               {
                       RIGHT_ROTATE(P(n), n, *root);
                       n = RIGHT(n);
               }
               else if((!IS_PARENT_LEFT(n)) && (!IS_NODE_LEFT(n)))
               {
                       COLOR(P(n)) = 'B';
                       COLOR(P(P(n))) = 'R';
                       LEFT_ROTATE(P(P(n)), P(n), *root);
               }
               else
               {
                       printf("error!");
               }
        }
        while(P(n) != &NIL)
                n = P(n);
        *root = n;
}
struct _rbtree *tree_successor(struct _rbtree *node)
{
        struct _rbtree *p = RIGHT(node);
        if(node == &NIL) 
                printf("&NIL DON't HAVE SUCCESSOR NODE!");
        if(p != &NIL)
        {
                while(LEFT(p) != &NIL)
                        p = LEFT(p);
                return p;
        }
        else    /* if node doesn't have a right-child*/
        {
                p = node;
                while((p != &NIL) && !(IS_NODE_LEFT(p)))
                        p = P(p);
                return P(p);
        }
        return NULL;
}
void rbtree_delete_node_with_data(struct _rbtree **root,void *data_ptr)
{
        struct _rbtree *search;
        get_queue_v2(node_queue, 20, struct _rbtree *);
        search = *root;
        enqueue(node_queue, &search);
        while(1)
        {
                if(IS_QUEUE_EMPTY(node_queue))
                        break;
                search = dequeue_v2(node_queue);

                if((uint32_t)data_ptr == (uint32_t)(RBT_DATA(search)))
                {
                printf("FOUND THE NODE WITH DATA %08x, VAL = %g , LEFT = %g , RIGHT = %g\n",
                        (uint32_t)(RBT_DATA(search)), VAL(search), VAL(LEFT(search)), VAL(RIGHT(search)));
                rbtree_delete_node(root, search);

                        break;
                }
                if(LEFT(search) != &NIL)
                {
                        enqueue(node_queue, &(LEFT(search)));
                }
                if(RIGHT(search) != &NIL)
                {
                        enqueue(node_queue, &(RIGHT(search)));
                }
        }
        DESTORY_QUEUE(node_queue);
}
void rbtree_delete_node(struct _rbtree **root, struct _rbtree *node)
{
        struct _rbtree *delete;
        struct _rbtree *connector ;
        printf("Now deleting the node with value %g root = %g\n",VAL(node),VAL(*root));
        if((LEFT(node) == &NIL) || (RIGHT(node) == &NIL))
                delete = node;
        else
                delete = tree_successor(node);
        
        if(LEFT(delete) != &NIL)
                connector = LEFT(delete);
        else
                connector = RIGHT(delete);

        P(connector) = P(delete);

        if(P(delete) == &NIL)
        {
                *root = connector;
        }
        else
        {
                if(IS_NODE_LEFT(delete))
                        LEFT(P(delete)) = connector;
                else
                        RIGHT(P(delete)) = connector;
        }
        
        if(delete != node)
        {
                node->cmp = delete->cmp;
                node->pdata = delete->pdata;
        }
        DELETE_NODE(delete,FALSE);
        if(COLOR(delete) == 'B')
                rbtree_delete_fixup(root, connector);
        return ;
}

void rbtree_delete_fixup(struct _rbtree **root, struct _rbtree *node)
{
        struct _rbtree *n = node;
        struct _rbtree *s;
        if(P(node) == &NIL)
                return ;
        while(COLOR(n) != 'R')
        {
                s = SIBLING(n);
                if(s == &NIL)
                        break;
                if(COLOR(s) == 'R')
                {
                        COLOR(s) = 'B';
                        COLOR(P(s)) = 'R';
                        if(IS_NODE_LEFT(n) == TRUE)
                                LEFT_ROTATE(P(s), s, *root);
                        else
                                RIGHT_ROTATE(P(s), s, *root);
                }
                else if((COLOR(s) == 'B') && (COLOR(LEFT(s)) == 'B') && (COLOR(RIGHT(s)) == 'B'))
                {
                        COLOR(s) = 'R';
                        n = P(n);
                }
                else if((COLOR(s) == 'B') && (IS_NODE_LEFT(s)))
                {
                        if(COLOR(RIGHT(s)) == 'R' && (COLOR(LEFT(s)) == 'B'))
                        {
                                COLOR(LEFT(s)) = 'B';
                                COLOR(s) = 'R';
                                LEFT_ROTATE(s, RIGHT(s), *root);
                        }
                        if(COLOR(LEFT(s)) == 'R')
                        {
                                COLOR(s) = COLOR(P(s));
                                COLOR(P(s)) = 'B';
                                COLOR(LEFT(s)) = 'B';
                                RIGHT_ROTATE(P(s), s, *root);
                        }
                }
                else if((COLOR(s) == 'B') && (!IS_NODE_LEFT(s)))
                {
                        if((COLOR(LEFT(s)) == 'R') && (COLOR(RIGHT(s)) == 'B'))
                        {
                                COLOR(LEFT(s)) = 'B';
                                COLOR(s) = 'R';
                                RIGHT_ROTATE(s, LEFT(s), *root);
                        }
                        if(COLOR(RIGHT(s)) == 'R')
                        {
                                COLOR(s) = COLOR(P(s));
                                COLOR(P(s)) = 'B';
                                COLOR(RIGHT(s)) = 'B';
                                LEFT_ROTATE(P(s),s, *root);
                        }
                }
                else
                        printf("case UNKNOW! COLOR n = %c , COLOR s = %c\n\n",COLOR(n),COLOR(SIBLING(n)));
        }
}
void rbtree_walk(struct _rbtree *node,int i)
{
        if(node != &NIL)
        {
                printf("I am node %d, Val = %g(%c) , Parent = %g(%c) , Left = %g(%c) , Right = %g(%c)\n",
                i,VAL(node),COLOR(node),VAL(P(node)),COLOR(P(node)),VAL(LEFT(node)),COLOR(LEFT(node)),VAL(RIGHT(node)),COLOR(RIGHT(node)));
        if(LEFT(node) != &NIL)
                rbtree_walk(LEFT(node), i + 1);
        if(RIGHT(node) != &NIL)
                rbtree_walk(RIGHT(node), i + 1);
        }
}
void rbtree_test()
{
        int datas[] = {12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17}; 
        int i = 0;
        struct _rbtree *rooot;
        struct _rbtree *rbt_new;
        struct _rbtree *pc;
        char p1[] = "i am data 1";
        char p2[] = "i am data 2";
        char p3[] = "i am data 3";
        for( i = 0; i < 20; i++)
        {
                if(i == 4)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],p1);
                else if(i == 11)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],p2);
                else if(i == 2)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],p3);
                else
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],NULL);
                printf("get new node %08x, Val = %g with data %08x\n",(uint32_t)rbt_new,VAL(rbt_new),(uint32_t)(RBT_DATA(rbt_new)));
                if(i == 0)
                        rooot = rbt_new;

                rbt_insert(&rooot, rbt_new);
        }
        printf("check begin!!\n\n");
//*        check_list[0] = rooot;
//*                for( i = 0; i < 9; i++)
//*                {
//*                        printf("Node %d (%c) ,Val = %02g ,Left = %02g, Right = %02g\n"
//*                                ,i,COLOR(check_list[head]),VAL(check_list[head]),VAL(LEFT(check_list[head])),VAL(RIGHT(check_list[head])));
//*                        if(LEFT(check_list[head]) != &NIL)
//*                        {
//*                                tail++;
//*                                check_list[tail] = LEFT(check_list[head]);
//*                        }
//*                        if(RIGHT(check_list[head]) != &NIL)
//*                        {
//*                                tail++;
//*                                check_list[tail] = RIGHT(check_list[head]);
//*                        }
//*                        head++;
//*                } THIS queueE ABOVE IS LAME!
        get_queue_v2(check_list, 20, struct _rbtree *);
        pc = rooot;
        enqueue(check_list, &pc);
        for( i = 0; i < 20; i++)
        {
                pc = dequeue_v2(check_list);
                printf("Node %d (%c) ,Val = %02g ,Left = %02g, Right = %02g\n"
                        ,i,COLOR(pc),VAL(pc),VAL(LEFT(pc)),VAL(RIGHT(pc)));
                if(LEFT(pc) != &NIL)
                {
                        enqueue(check_list, &(LEFT(pc)));
                }
                if(RIGHT(pc) != &NIL)
                {
                        enqueue(check_list, &(RIGHT(pc)));
                }
        }
        rbtree_delete_node_with_data(&rooot, (void *)p1);
        rbtree_delete_node_with_data(&rooot, (void *)p2);
        rbtree_delete_node_with_data(&rooot, (void *)p3);
//*        for( i = 0 ; i < 20 ; i++)
//*        {
//*                rbtree_delete_node_with_val(rooot, datas[i]);
//*                rbtree_walk(rooot, 0);
//*        }
}
