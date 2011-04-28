#include "common/common.h"
typedef char color_t;
struct _attr
{
        struct _rbtree *left;
        struct _rbtree *right;
        struct _rbtree *parent;
        color_t color;
        void *free_addr;
};
union _val
{
        int i_val;
        double d_val;
};                   // value types to do the comparision

struct _cmp
{
        int type;
        union _val val;
};

struct _rbtree
{
        struct _attr attr;
        struct _cmp cmp;
        void *pdata;
};
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

void rbt_insert(struct _rbtree **root, struct _rbtree *node);
void rbt_insert_fixup(struct _rbtree **root, struct _rbtree *node);
void rbtree_delete_node(struct _rbtree **root, struct _rbtree *node);
void rbtree_delete_node_with_data(struct _rbtree **root, void *data_ptr);
void rbtree_delete_fixup(struct _rbtree **root, struct _rbtree *node);
void rbtree_walk(struct _rbtree *node,int i);
void rbtree_test();
