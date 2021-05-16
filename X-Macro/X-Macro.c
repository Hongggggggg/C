#include <stdio.h>

#define FUNC_IN() printf("enter %s \r\n", __FUNCTION__)

#define CMD_FUNC    \
    DEF_X(CMD_PLAY, func_cmd_play)  \
    DEF_X(CMD_PAUSE, func_cmd_pause)  \
    DEF_X(CMD_STOP, func_cmd_stop)  \


typedef enum
{
    #define DEF_X(a, b) a,
    CMD_FUNC
    #undef DEF_X
    CMD_MAX
}tCmd;

const char* str_cmd[] = 
{
    #define DEF_X(a, b) #a,
    CMD_FUNC
    #undef DEF_X
};

typedef void (*pFunc)(void* p);

void func_cmd_play(void* p)
{
    FUNC_IN();
}

void func_cmd_pause(void* p)
{
    FUNC_IN();
}

void func_cmd_stop(void* p)
{
    FUNC_IN();
}

const pFunc player_funcs[] = 
{
    #define DEF_X(a, b) b,
    CMD_FUNC
    #undef DEF_X
};

void player_cmd_handle(tCmd cmd, void* p)
{
    if(cmd < CMD_MAX)
    {
        player_funcs[cmd](p);
        printf("cmd is %s\r\n", str_cmd[cmd]);
    }
    else
    {
        printf("Cmd(%d) invalid\r\n", cmd);
    }

}


void main(void)
{
    player_cmd_handle(CMD_PAUSE, (void*)0);
    player_cmd_handle(CMD_PLAY, (void*)0);
    player_cmd_handle(CMD_STOP, (void*)0);
    player_cmd_handle(100, (void*)0);
}
