#include <stdio.h>

#include <stdbool.h>

/*状态机所有状态*/
typedef enum
{
    SYS_NORMAL,
    SYS_OTHER,
    SYS_FAC,
}SM_STATE;

/*触发事件*/
typedef enum
{
    EVENT1,
    EVENT2,
    EVENT3,
    EVENT4,
}SM_EVENT;

/*回调*/
typedef void (*state_cb)(void);

/*状态表*/
typedef struct
{
    SM_EVENT event;
    SM_STATE cur_state;
    SM_STATE next_state;
    state_cb cb;
}SM_TABLE_T;

/*产测状态*/
void fac_state(void)
{
    printf("===FAC\r\n");
}

/*其他状态*/
void other_state(void)
{
    printf("===OTHER\r\n");
}

/*正常状态*/
void normal_state(void)
{
    printf("===NORMAL\r\n");
}

/*状态表*/
SM_TABLE_T state_table[] =
{
    {EVENT1,  SYS_NORMAL ,SYS_FAC    ,fac_state    },
    {EVENT2,  SYS_FAC    ,SYS_OTHER  ,other_state  },
    {EVENT3,  SYS_OTHER  ,SYS_NORMAL ,normal_state },
    {EVENT4,  SYS_NORMAL ,SYS_OTHER  ,other_state  },
};

/*状态机*/
typedef struct
{
    SM_STATE cur_state;
    SM_TABLE_T* table;
    int size;
}SM_T;

/*事件处理及状态切换*/
void event_handle(SM_EVENT event, SM_T* sm)
{
    if (sm == NULL || sm->table == NULL)
    {
        printf("POINT NULL");
        return;
    }

    bool find_flag = false;
    for (unsigned char i = 0; i < sm->size; i++)
    {
        if(sm->table[i].event == event && sm->table[i].cur_state == sm->cur_state)
        {
            sm->cur_state = sm->table[i].next_state;
            sm->table[i].cb();
            find_flag = true;
            break;
        }
    }

    if(!find_flag)
    {
        printf("Event wrong!\r\n");
    }
}

void main(void)
{
    SM_T state_machine = {.cur_state = SYS_NORMAL, .table = state_table, .size = (sizeof(state_table) / sizeof(SM_TABLE_T))};

    SM_EVENT input_event[] = {EVENT1, EVENT2, EVENT3, EVENT4, EVENT1};

    for (char i = 0; i < sizeof(input_event) / sizeof(SM_EVENT); i++)
    {
        event_handle(input_event[i], &state_machine);
    }
}



