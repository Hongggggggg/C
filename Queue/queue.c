#include <stdio.h>
#include <stdbool.h>

#define QUEUE_SIZE  11

typedef struct
{
    int front;
    int rear;
    int len;
    char data[QUEUE_SIZE];
}Queue_t;

Queue_t queue = {.front = 0, .rear = 0, .len = 0, .data = 0};

bool queue_is_empty(void)
{
    return queue.front == queue.rear ? true : false;
}

bool queue_is_full(void)
{
    return ((queue.rear + 1) % QUEUE_SIZE == queue.front) ? true : false;
}

void queue_push(char data)
{
    if(queue_is_full())
    {
        printf("Queue is full\r\n");

        return;
    }
    queue.data[queue.rear] = data;

    queue.rear = (queue.rear + 1) % QUEUE_SIZE;

    queue.len++;
}

void queue_pop(char* data)
{
    if(NULL == data)
    {
        printf("POINT NULL\r\n");

        return;
    }

    if(queue_is_empty())
    {
        printf("Queue is empty\r\n");

        return;
    }
    *data = queue.data[queue.front];

    queue.front = (queue.front + 1) % QUEUE_SIZE;

    queue.len--;
}

void queue_print(void)
{
    printf("Len: %d\r\n", queue.len);

    for(int i = 0; i < QUEUE_SIZE; i++)
    {
        printf("[%d]: %d ", i, queue.data[i]);
    }
}

void main(void)
{
    for (char i = 1; i < 12; i++)
    {
        queue_push(i);
    }
    printf("rear: %d, front: %d\r\n", queue.rear, queue.front);

    queue_print();
}
