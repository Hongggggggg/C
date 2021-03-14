#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    void* pData;
}data_t;

void* get_data()
{
    static data_t* pData = NULL;
    if(NULL != pData) //只允许存在一种实例
    {
        return pData;
    }
    pData = (data_t*)malloc(sizeof(data_t));
    assert(NULL != pData);
    return (void*)pData;
}
