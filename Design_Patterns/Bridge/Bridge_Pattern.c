#include <stdio.h>

enum
{
    MEAT_TYPE = 0,
    NORMAL_TYPE = 1,
};


typedef struct _MeatDumpling
{
    void (*make)();
}MeatDumpling;


typedef struct _NormalDumpling
{
    void (*make)();
}NormalDumpling;


typedef struct  _DumplingRequest
{
    int type;
    void* pDumpling;
}DumplingRequest;


void buy_dumpling(DumplingRequest* pDumplingRequest)
{
    assert(NULL != pDumplingRequest);
    if(MEAT_TYPE == pDumplingRequest->type)
        return (MeatDumpling*)(pDumplingRequest->pDumpling)->make();
    else
        return (NormalDumpling*)(pDumplingRequest->pDumpling)->make();
}
