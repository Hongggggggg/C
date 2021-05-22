#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define MAX_BINDING_NUM 10
/*
typedef struct _Observer
{
    Object* pObject;
    void (*update)(struct _Observer* pObserver);
}Observer;

typedef struct _Object
{
    Observer* pObserverList[MAX_BINDING_NUM];
    int number;

    void (*notify)(struct _Object* pObject);
    void (*add_observer)(Observer* pObserver);
    void (*del_observer)(Observer* pObserver);
}Object;


void bind_observer_to_object(Observer* pObserver, Object* pObject)
{
    assert(NULL != pObject && NULL != pObject);

    pObserver->pObject = pObject;
    pObject->add_observer(pObserver);
    pObject->number++;
}

void unbing_observer_from_object(Observer* pObserver, Object* pObject)
{
    pObject->del_observer(pObserver);
    memset(pObserver, 0, sizeof(Observer));
}


void notify(struct _Object* pObject)
{
    Observer* pObserver;

    assert(NULL != pObject);
    for(int index = 0; index < pObject->number; index++)
    {
        pObserver = pObject->pObserverList[index];
        pObserver->update(pObserver);
    }
}
*/
typedef void (*observer_handle)(void* msg);

typedef enum
{
    ON_OFF_STATE,
    LIGHTNESS,
    WORK_MODE,
    TOPIC_MAX
}topic_e;

typedef struct
{
    observer_handle func;
    topic_e topic;
}observer_t;


typedef struct _Link_List
{
    observer_handle func;
    struct _Link_List* next;
}Observer_Node;

Observer_Node* func_head_node[TOPIC_MAX] = {NULL};

int topic_subscribe(observer_t* observer)
{
    if(observer->topic >= TOPIC_MAX || observer->func == NULL || observer == NULL) return -1;

    Observer_Node* func_link_tail = func_head_node[observer->topic];
    if(func_link_tail != NULL)
    {
        while(func_link_tail->next != NULL)
        {
            func_link_tail = func_link_tail->next;
        }
    }

    Observer_Node* observer_node = (Observer_Node*)malloc(sizeof(Observer_Node));
    if(observer_node == NULL) return -2;
    observer_node->func = observer->func;
    observer_node->next = NULL;

    if(func_link_tail == NULL)
    {
        func_head_node[observer->topic] = observer_node;
    } 
    else
    {
        func_link_tail->next = observer_node;
    }
    return 0;
}


int msg_notify(topic_e topic, void* msg)
{
    if(topic >= TOPIC_MAX) return -1;

    Observer_Node* cur_node = func_head_node[topic];
    printf("msg_notify\r\n");

    while(cur_node != NULL)
    {
        if(cur_node->func == NULL) return -1;
        cur_node->func(msg);
        cur_node = cur_node->next;
    }
}


static void turn_on_the_light(void)
{
    char led_state = 1;
    msg_notify(ON_OFF_STATE, &led_state);
}

static void observer_cb(void* msg)
{
    printf("observer callback: %d\r\n", *((char*)msg));
}

static void observer_cb1(void* msg)
{
    printf("observer callback1: %d\r\n", *((char*)msg));
}

static void observer_cb2(void* msg)
{
    printf("observer callback2: %d\r\n", *((char*)msg));
}


int main(void)
{
    observer_t observer = {.func = observer_cb, .topic = ON_OFF_STATE};
    topic_subscribe(&observer);

    observer_t observer1 = {.func = observer_cb1, .topic = ON_OFF_STATE};
    topic_subscribe(&observer1);

    observer_t observer2 = {.func = observer_cb2, .topic = ON_OFF_STATE};
    topic_subscribe(&observer2);

    printf("Hello\r\n");
    turn_on_the_light();
    turn_on_the_light();
    turn_on_the_light();
    return 0;
}
