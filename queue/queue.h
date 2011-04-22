struct _queue
{
        void *head;
        void *tail;
        void *cur_head;
        void *cur_tail;
        int elem_size;
        int queue_size;
        int available_slot;
        struct _queue *free_addr; // Points to the struct itself;
};
int _get_queue(struct _queue *queue_name, int elem_nr, int elem_size);
void queue_test();
