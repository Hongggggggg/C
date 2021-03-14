#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEATHER_TYPE    0x01
#define RUBBER_TYPE     0x02

typedef struct _Shoe
{
    int type;
    void (*print_shoe)(struct _Shoe* pShoe);
}Shoe;


void print_leather_shoe(struct _Shoe* pShoe)
{
    printf("This is a leather shoe!\r\n");
    printf("Type is %d\r\n", pShoe->type);
}


void print_rubber_shoe(struct _Shoe* pShoe)
{
    printf("This is a rubber shoe!\r\n");
    printf("Type is %d\r\n", pShoe->type);
}


Shoe* manufacture_new_shoe(int type)
{
    Shoe* pShoe = (Shoe*)malloc(sizeof(Shoe));
    memset(pShoe, 0, sizeof(Shoe));
    if(LEATHER_TYPE == type)
    {
        pShoe->type = LEATHER_TYPE;
        pShoe->print_shoe = print_leather_shoe;
    }
    else
    {
        pShoe->type = RUBBER_TYPE;
        pShoe->print_shoe = print_rubber_shoe;
    }
    return pShoe;
}


void main(void)
{
    Shoe* pShoe = manufacture_new_shoe(LEATHER_TYPE);
    pShoe->print_shoe(pShoe);
    pShoe = manufacture_new_shoe(RUBBER_TYPE);
    pShoe->print_shoe(pShoe);
}

