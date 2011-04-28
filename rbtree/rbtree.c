#include "rbtree.h"
#include "queue/queue.h"
/*      Use VAL_Int Or VAL_DOUBLE as 'type' parameter      */
#define VAL_INT                 i_val
#define VAL_DOUBLE              d_val

/*      do NOT use those two!!    */
#define CMP_INT 0x4
#define CMP_DOUBLE 0x12

#define COLOR(rbt)              ((struct _rbtree *)rbt)->attr.color
#define LEFT(rbt)               ((struct _rbtree *)rbt)->attr.left
#define RIGHT(rbt)              ((struct _rbtree *)rbt)->attr.right
#define P(rbt)                  ((struct _rbtree *)rbt)->attr.parent
#define FREE_ADDR(rbt)          ((struct _rbtree *)rbt)->attr.free_addr
#define RBT_DATA(rbt)           (((struct _rbtree *)rbt)->pdata)
#define UNCLE(rbt)              (LEFT(P(P(rbt))) == P(rbt) ? (RIGHT(P(P(rbt)))) : (LEFT(P(P(rbt)))))
#define RIGHT_UNCLE(rbt)        (RIGHT(P(P(rbt))))
#define LEFT_UNCLE(rbt)         (LEFT(P(P(rbt))))
#define IS_UNCLE_LEFT(rbt)      (LEFT(P(P(rbt))) == P(rbt) ? FALSE : TRUE)
#define IS_PARENT_LEFT(rbt)     (LEFT(P(P(rbt))) == P(rbt) ? TRUE : FALSE)
#define IS_NODE_LEFT(rbt)       (LEFT(P(rbt)) == rbt ? TRUE : FALSE)
#define SIBLING(rbt)            ((IS_NODE_LEFT(rbt)) ? RIGHT(P(rbt)) : LEFT(P(rbt)))

#define CMPTYPE(rbt)            ((struct _rbtree *)rbt)->cmp.type
#define CMP(a,op,c,type)        ((((struct _rbtree *)a)->cmp.val.type op ((struct _rbtree *)c)->cmp.val.type) ? 1 : 0)

/*      Some Value Operations Marcos */
/*      VAL(brt) use to do the comparision ONLY e.g : if(VAL(rbt1) > VAL(rbt2)) ......  */
#define VAL(rbt)                ({CMPTYPE(rbt) == CMP_INT ?                             \
                                ((struct _rbtree *)rbt)->cmp.val.i_val :                \
                                ((struct _rbtree *)rbt)->cmp.val.d_val;})
/*      GET_VAL use to assign dst with rbt's value,Use VAL_Int Or VAL_DOUBLE 3rd parameterOnly! */
#define GET_VAL(dst, rbt,type)      dst = ((struct _rbtree *)rbt)->cmp.val.type


#define SET_VAL_WITH_TYPE(rbt, val, type)  ((struct _rbtree *)rbt)->cmp.val.type = (val)
#define SET_VAL(rbt, Val)                                                               \
do                                                                                      \
{                                                                                       \
        if((CMPTYPE(rbt)) == CMP_INT)                                                   \
                ((struct _rbtree *)rbt)->cmp.val.i_val = (Val);                         \
        else                                                                            \
                ((struct _rbtree *)rbt)->cmp.val.d_val = (Val);                         \
}while(0)

static struct _rbtree NIL = {.attr = {NULL, NULL, NULL, 'B',NULL}, .pdata = NULL}; // *NEVER* free(NIL)!!
#define get_rbtree_node(cmptype, _Val, data_addr)                                       \
({                                                                                      \
        struct _rbtree *name;                                                           \
        name = NULL;                                                                    \
        CALLOC_S(struct _rbtree, name, 1, sizeof(struct _rbtree));                      \
        name->attr.left = name->attr.right = name->attr.parent = (&NIL);                \
        name->attr.color = 'R';                                                         \
        name->cmp.type = cmptype;                                                       \
        if(name->cmp.type == CMP_INT)                                                   \
                name->cmp.val.i_val = (_Val);                                           \
        else if(name->cmp.type == CMP_DOUBLE)                                           \
                name->cmp.val.d_val = (_Val);                                           \
        else                                                                            \
                printf("Error : Unknown cmp type %08x\n",(unsigned int) cmptype);       \
        name->pdata = (void *)data_addr;                                                \
        FREE_ADDR(name) = name;                                                         \
        name;                                                                           \
})


#define get_rbtree_node_with_name(name, cmptype, _Val, data_addr)                       \
({                                                                                      \
        struct _rbtree *name;                                                           \
        name = NULL;                                                                    \
        CALLOC_S(struct _rbtree, name, 1, sizeof(struct _rbtree));                      \
        name->attr.left = name->attr.right = name->attr.parent = (&NIL);                \
        name->attr.color = 'R';                                                         \
        name->cmp.type = cmptype;                                                       \
        if(name->cmp.type == CMP_INT)                                                   \
                name->cmp.val.i_val = (_Val);                                           \
        else if(name->cmp.type == CMP_DOUBLE)                                           \
                name->cmp.val.d_val = (_Val);                                           \
        else                                                                            \
                printf("Error : Unknown cmp type %08x\n",(unsigned int) cmptype);       \
        name->pdata = (void *)data_addr;                                                \
        FREE_ADDR(name) = name;                                                         \
        name;                                                                           \
})
/*if data == TRUE,it will free pdata as well*/
/* if FREE_ADDR(node) == FALSE,then that node is NIL and can not be freed!*/
#define  DELETE_NODE(node , data)               \
do                                              \
{                                               \
        if(FREE_ADDR(node) != NULL)             \
        {                                       \
                if(data == TRUE)                \
                        free(RBT_DATA(node));   \
                free((void *)FREE_ADDR(node));  \
        }                                       \
}while(0)
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
        rbtree_walk(*root, 0);
        rbt_insert_fixup(root,node);
}
/********************************************************************************************************/
/*       |                                                                                      |       */
/*      (x)                                                                                    (y)      */
/*      / \                     -----LEFT_ROTATE(x, y)--->                                     / \      */
/*     a  (y)                   <----RIGHT_ROTATE(y,x)----                                   (x)  c     */
/*        / \                                                                                / \        */
/*       b   c                                                                              a   b       */
/********************************************************************************************************/
/* 
 * Pay special attention to this cases : if the new y , or new x is new "ROOT",we must manual change the val
 * of root,that why we added the 3rd parameter,root
 */
#define LEFT_ROTATE(x, y, root)   \
do                                \
{                                 \
        typeof(x) _x = x;         \
        typeof(y) _y = y;         \
        if(P(_x) != &NIL)         \
        {                         \
        if(LEFT(P(_x)) == _x)     \
                LEFT(P(_x)) = _y; \
        else                      \
                RIGHT(P(_x)) = _y;\
        }                         \
        else                      \
                root = _y;        \
        P(LEFT(_y)) = _x;         \
        RIGHT(_x) = LEFT(_y);     \
        P(_y) = P(_x);            \
        LEFT(_y) = _x;            \
        P(_x) = _y;               \
}while(0)

#define RIGHT_ROTATE(y, x, root)  \
do                                \
{       typeof(x) _x = x;         \
        typeof(y) _y = y;         \
        if(P(_y) != &NIL)         \
        {                         \
        if(LEFT(P(_y)) == _y)     \
                LEFT(P(_y)) = _x; \
        else                      \
                RIGHT(P(_y)) = _x;\
        }                         \
        else                      \
                root = _x;        \
        P(RIGHT(_x)) = _y;        \
        LEFT(_y) = RIGHT(_x);     \
        P(_x) = P(_y);            \
        RIGHT(_x) = _y;           \
        P(_y) = _x;               \
}while(0)                       

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
#define rbtree_delete_node_with_val(root, val)                          \
do                                                                      \
{                                                                       \
        struct _rbtree *search = root;                                  \
        while((VAL(search) != val) && (search != &NIL))                 \
        {                                                               \
                printf("cmp %g with %d\n",VAL(search),val);             \
                if(VAL(search) > (double)val)                           \
                        search = LEFT(search);                          \
                else if(VAL(search) < (double)val)                      \
                        search = RIGHT(search);                         \
                else                                                    \
                {                                                       \
                        break;                                          \
                }                                                       \
        }                                                               \
        if(search != &NIL)                                              \
                rbtree_delete_node(&root, search);                      \
        else                                                            \
                printf("Node with val = %g NOT FOUND!\n",val);          \
}while(0) 
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
        if(search != NULL)
        {
                printf("FOUND THE NODE WITH DATA %08x, VAL = %g , LEFT = %g , RIGHT = %g\n",
                        (uint32_t)(RBT_DATA(search)), VAL(search), VAL(LEFT(search)), VAL(RIGHT(search)));
                rbtree_delete_node(root, search);
        }
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
        char *p = "hello 11";
        struct _rbtree *rooot;
        struct _rbtree *rbt_new;
        struct _rbtree *pc;
        int head , tail;
        head = tail = 0;
        for( i = 0; i < 20; i++)
        {
                if(i == 4)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],0xdeadbeaf);
                else if(i == 11)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],0x11111111);
                else if(i == 2)
                        rbt_new = get_rbtree_node(CMP_INT,datas[i],0x22222222);
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
        rbtree_delete_node_with_data(&rooot, (void *)(0x11111111));
        rbtree_delete_node_with_data(&rooot, (void *)(0x22222222));
        rbtree_delete_node_with_data(&rooot, (void *)(0xdeadbeaf));
        for( i = 0 ; i < 20 ; i++)
        {
                rbtree_delete_node_with_val(rooot, datas[i]);
                rbtree_walk(rooot, 0);
        }
}
