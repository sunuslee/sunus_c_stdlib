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


void rbt_insert(struct _rbtree **root, struct _rbtree *node);
void rbt_insert_fixup(struct _rbtree **root, struct _rbtree *node);
void rbtree_delete_node(struct _rbtree **root, struct _rbtree *node);
void rbtree_delete_node_with_data(struct _rbtree **root, void *data_ptr);
void rbtree_delete_fixup(struct _rbtree **root, struct _rbtree *node);
void rbtree_walk(struct _rbtree *node,int i);
void rbtree_test();
