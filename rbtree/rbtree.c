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
#define UNCLE(rbt) (LEFT(P(P(rbt))) == P(rbt) ? (RIGHT(P(P(rbt)))) : (LEFT(P(P(rbt)))))
#define RIGHT_UNCLE(rbt) (RIGHT(P(P(rbt))))
#define LEFT_UNCLE(rbt)  (LEFT(P(P(rbt))))
#define IS_UNCLE_LEFT(rbt) (LEFT(P(P(rbt))) == P(rbt) ? FALSE : TRUE)
#define IS_PARENT_LEFT(rbt) (LEFT(P(P(rbt))) == P(rbt) ? TRUE : FALSE)
#define IS_NODE_LEFT(rbt) (LEFT(P(rbt)) == rbt ? TRUE : FALSE)


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
/********************************************************************************************************/
/*       |                                                                                      |       */
/*      (x)                                                                                    (y)      */
/*      / \                     -----LEFT_ROTATE(x, y)--->                                     / \      */
/*     a  (y)                   <----RIGHT_ROTATE(y,x)----                                   (x)  c     */
/*        / \                                                                                / \        */
/*       b   c                                                                              a   b       */
/********************************************************************************************************/
#define LEFT_ROTATE(x, y)         \
do                                \
{                                 \
        typeof(x) _x = x;         \
        typeof(y) _y = y;         \
        if(LEFT(P(_x)) == _x)     \
                LEFT(P(_x)) = _y; \
        else                      \
                RIGHT(P(_x)) = _y;\
        RIGHT(_x) = LEFT(_y);     \
        P(_y) = P(_x);            \
        P(_x) = _y;               \
        LEFT(_y) = _x;            \
}while(0)

#define RIGHT_ROTATE(y, x)        \
do                                \
{       typeof(x) _x = x;         \
        typeof(y) _y = y;         \
        if(LEFT(P(_y)) == _y)     \
                LEFT(P(_y)) = _x; \
        else                      \
                RIGHT(P(_y)) = _x;\
        LEFT(_y) = RIGHT(_x);     \
        P(_x) = P(y);             \
        P(_y) = _x;               \
        RIGHT(_x) = _y;           \
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
                       LEFT_ROTATE(P(n), n);
                       n = LEFT(n);
               }
               else if(IS_PARENT_LEFT(n) && IS_NODE_LEFT(n))
               {
                       COLOR(P(n)) = 'B';
                       COLOR(P(P(n))) = 'R';
                       RIGHT_ROTATE(P(P(n)), P(n));
               }
               else if((!IS_PARENT_LEFT(n)) && IS_NODE_LEFT(n))/* 2 cases that 'parent of n' in the *RIGHT* of 'GRANDparent of n'*/
               {
                       RIGHT_ROTATE(P(n), n);
                       n = RIGHT(n);
               }
               else if((!IS_PARENT_LEFT(n)) && (!IS_NODE_LEFT(n)))
               {
                       COLOR(P(n)) = 'B';
                       COLOR(P(P(n))) = 'R';
                       LEFT_ROTATE(P(P(n)), P(n));
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
void rbtree_test()
{
        int datas[] = {11,1,2,14,15,7,5,4,8};
        int i = 0;
        struct _rbtree *rooot;
        struct _rbtree *rbt_new;
        struct _rbtree *pc;
        struct _rbtree **ppc;
//*        struct _rbtree *check_list[10];
        int head , tail;
        head = tail = 0;
        for( i = 0; i < 9; i++)
        {
                rbt_new = get_rbtree_node(CMP_INT,datas[i],NULL);
                printf("get new node %08x, Val = %g\n",(uint32_t)rbt_new,VAL(rbt_new));
                if(i == 0)
                        rooot = rbt_new;
                rbt_insert(&rooot, rbt_new);
                printf("new node(%c)%08x , Val = %g inserted , Par(%c) = %08x , Val = %g , root(%c) = %08x , Val = %g\n\n\n",
                        COLOR(rbt_new),(uint32_t)rbt_new, VAL(rbt_new), 
                        (COLOR(P(rbt_new))),(uint32_t)(P(rbt_new)),VAL(P(rbt_new)),
                        COLOR(rooot),(uint32_t)rooot,VAL(rooot));
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
//*                }
        get_queue(check_list, 20, sizeof(struct _rbtree *));
        pc = rooot;
        enqueue(check_list, &pc);
        for( i = 0; i < 9; i++)
        {
                ppc = dequeue(check_list);
                pc = *ppc;
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
}
