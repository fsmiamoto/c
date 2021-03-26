#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_EMPTY INT_MIN

typedef struct
{
    int *values;
    int head, tail, num_entries, size;
} queue;

void init_queue(queue *q, int max_size)
{
    q->size = max_size;
    q->values = (int *)malloc(sizeof(int) * q->size);
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;
}

bool queue_empty(queue *q)
{
    return (q->num_entries == 0);
}

bool queue_full(queue *q)
{
    return (q->num_entries == q->size);
}

void queue_destroy(queue *q)
{
    if (q->values == NULL)
        return;
    free(q->values);
    q->values = NULL;
}

bool enqueue(queue *q, int value)
{
    if (queue_full(q))
        return false;
    q->values[q->tail] = value;
    q->num_entries++;
    q->tail = (q->tail + 1) % q->size;

    return true;
}

int dequeue(queue *q)
{
    int result;

    if (queue_empty(q))
    {
        return QUEUE_EMPTY;
    }
    result = q->values[q->head];
    q->head = (q->head + 1) % q->size;
    q->num_entries--;

    return result;
}

int main()
{
    queue q1;

    init_queue(&q1, 5);

    enqueue(&q1, 5);
    enqueue(&q1, 8);
    enqueue(&q1, 9);
    enqueue(&q1, 1);

    return 0;
}
