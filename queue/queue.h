#include "common/common.h"
typedef enum _queue_flags_t
{
        flag_queue_enqueue_with_data = 1 << 0,
        flag_queue_destory_with_data = 1 << 1,

}queue_flags;
struct _queue_elem_t
{
        void *pdata;
        struct _queue_t *queue_status;
        /* extra elements add below */
};
struct _queue_t
{
        struct _queue_elem_t *head;
        struct _queue_elem_t *tail;
        struct _queue_elem_t *cur_head;
        struct _queue_elem_t *cur_tail;
        int total_slot;
        int available_slot;
        struct _queue_t *free_queue;      // Points to the struct itself;
        void *free_queue_elem;          // Points to the head queue_elem( = head)
};


#define queue_is_empty(queue_name)      ((queue_name->available_slot) == (queue_name->total_slot) ? TRUE : FALSE)
#define queue_is_full(queue_name)       ((queue_name->available_slot) > 0 ? : FALSE)

#define queue_new(queue_name, elem_nr, data_type)                                               \
struct _queue_t *queue_name;                                                                    \
static data_type *data_##queue_name;                                                            \
do                                                                                              \
{                                                                                               \
        MALLOC_S(struct _queue_t, queue_name, sizeof(struct _queue_t));                         \
        MALLOC_S(struct _queue_elem_t, queue_name->head, sizeof(struct _queue_elem_t) * elem_nr);\
        queue_name->cur_head = queue_name->cur_tail = queue_name->head;                         \
        queue_name->tail = queue_name->head + elem_nr;                                          \
        queue_name->free_queue_elem = queue_name;                                               \
        queue_name->free_queue = queue_name;                                                    \
        queue_name->total_slot = queue_name->available_slot = elem_nr;                          \
}while(0)

#define queue_enqueue(queue_name, data)                                                         \
do                                                                                              \
{                                                                                               \
        if(!queue_is_full(queue_name))                                                          \
        {                                                                                       \
                printf("Info : queue %s is full\n",#queue_name);                                \
                break;                                                                          \
        }                                                                                       \
        queue_name->cur_tail =                                                                  \
        (queue_name->cur_tail == queue_name->tail ? queue_name->head : queue_name->cur_tail + 1);\
        (queue_name->cur_tail->pdata) = (void *)(data ? : NULL);                                 \
        queue_name->available_slot--;                                                           \
}while(0)

#define queue_dequeue(queue_name)                                                               \
({                                                                                              \
        data_##queue_name = NULL;                                                               \
        if(queue_is_empty(queue_name))                                                          \
        {                                                                                       \
                printf("Info : queue %s is empty\n",#queue_name);                               \
        }                                                                                       \
        else                                                                                    \
        {                                                                                       \
                queue_name->available_slot++;                                                   \
                queue_name->cur_head++;                                                         \
                if(queue_name->cur_head > queue_name->tail)                                     \
                        queue_name->cur_head = queue_name->head;                                \
                data_##queue_name = (queue_name->cur_head->pdata);                              \
        }                                                                                       \
        data_##queue_name == NULL ? 0 : *(data_##queue_name); /*ret val*/                       \
})



#define DESTORY_QUEUE(queue_name, flag)                                                                         \
do                                                                                                              \
{                                                                                                               \
        if(flag & flag_queue_destory_with_data)                                                                 \
        {                                                                                                       \
                for(queue_name->cur_head = queue_name->head  ; queue_name->cur_head <= queue_name->tail ; )     \
                {                                                                                               \
                        free(queue_name->cur_head->pdata);                                                      \
                        queue_name->cur_head++;                                                                 \
                }                                                                                               \
        }                                                                                                       \
        free(queue_name->free_queue_elem);                                                                      \
        free(queue_name->free_queue);                                                                           \
}while(0)
