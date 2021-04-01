#include <stdio.h>

typedef struct _DATA
{
    struct _DATA* (*copy)(struct _DATA* pData);
}DATA;


struct _DATA* data_copy_A(struct _DATA* pData)
{
    DATA* pResult = (DATA*)malloc(sizeof(DATA));
    assert(NULL != pResult);
    memmove(pResult, pData, sizeof(DATA));
    return pResult;
}

DATA data_A = {data_copy_A};

struct _DATA* clone(struct _DATA* pData)
{
    return pData->copy(pData);
}
