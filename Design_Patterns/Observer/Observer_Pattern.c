#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAX_BINDING_NUM 10

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
