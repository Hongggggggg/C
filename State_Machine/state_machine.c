#include <stdio.h>

#include <stdbool.h>

/*链路层状态*/
typedef enum
{
    SCAN,
    READY,
    ADV,
    CONN,
    INIT,
}SM_STATE;

/*触发事件*/
typedef enum
{
    EVENT1,
    EVENT2,
    EVENT3,
    EVENT4,
    EVENT5,
    EVENT6,
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

/*就绪态*/
static void sys_ready(void)
{
    printf("READY\r\n");
}

/*扫描态*/
static void scan_state(void)
{
    printf("SCAN\r\n");
}

/*广播态*/
static void adv_state(void)
{
    printf("ADV\r\n");
}

/*连接态*/
static void conn_state(void)
{
    printf("CONN\r\n");
}

/*发起态*/
static void init_state(void)
{
    printf("INIT\r\n");
}

/*状态表*/
SM_TABLE_T state_table[] =
{
    {EVENT1, READY, SCAN, scan_state},
    {EVENT2, SCAN, READY, sys_ready},
    {EVENT3, READY, ADV, adv_state},
    {EVENT4, ADV, CONN, conn_state},
    {EVENT5, CONN, INIT, init_state},
    {EVENT6, INIT, READY, sys_ready},
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
    SM_T state_machine = {.cur_state = READY, .table = state_table, .size = (sizeof(state_table) / sizeof(SM_TABLE_T))};

    printf("Init to READY\r\n");

    SM_EVENT input_event[] = {EVENT1, EVENT2, EVENT3, EVENT4, EVENT5, EVENT6, EVENT2};

    for (char i = 0; i < sizeof(input_event) / sizeof(SM_EVENT); i++)
    {
        event_handle(input_event[i], &state_machine);
    }
}



