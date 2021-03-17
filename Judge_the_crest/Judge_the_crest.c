#include <stdio.h>
#include <stdlib.h>
#define SAMPLE_MAX  20
#define PV_MAX      10

int Sample[SAMPLE_MAX] = {1,2,3,4,4,4,5,2,1,0,0,5,1,0,0,1,2,3,4,0};
int SampleDiff[SAMPLE_MAX] = {0};

typedef struct _tag_FindPV
{
    int Pos_Peak[PV_MAX];    //波峰位置存储
    int Pos_Valley[PV_MAX];  //波谷位置存储
    int Pcnt;                //所识别的波峰计数
    int Vcnt;                //所识别的波谷计数
}SFindPV;

SFindPV stFindPV;


void buf_print(char *str, int* data, int len)
{
    printf("[%s]: ", str);
    for(int i = 0; i < len; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\r\n");
}
/********************************************
 *  Fuction : initialFindPV
 *  Note    : 初始化相关数据 
 *******************************************/ 
void initialFindPV(void)
{
    int Index = 0;

    for(Index = 0; Index < SAMPLE_MAX; Index ++)
    {
        SampleDiff[Index] = 0;
    }

    for(Index = 0; Index < PV_MAX; Index ++)
    {
        stFindPV.Pos_Peak[Index] = -1;
        stFindPV.Pos_Valley[Index] = -1;
    }
    stFindPV.Pcnt = 0;
    stFindPV.Vcnt = 0;
}

/********************************************
 *  Fuction : FindPV
 *  Note    : 找波峰波谷 
 *******************************************/ 
void FindPV(SFindPV *pFindPV, int *Sample)
{
    int i = 0;
    buf_print("SampleDiff", Sample, SAMPLE_MAX);

    //step 1 :首先进行前向差分，并归一化
    for(i = 0; i < SAMPLE_MAX - 1; i++)
    {
        if(Sample[i + 1] - Sample[i] > 0)
        {
            SampleDiff[i] = 1;
        }
        else if (Sample[i + 1] - Sample[i] < 0)
        {
            SampleDiff[i] = -1;
        }
        else
        {
            SampleDiff[i] = 0;
        }
    }
    buf_print("SampleDiff", SampleDiff, SAMPLE_MAX);

    //step 2 :对相邻相等的点进行领边坡度处理
    for(i = 0; i < SAMPLE_MAX - 1; i++)
    {
        if(SampleDiff[i] == 0)
        {
            if(i == (SAMPLE_MAX - 2))
            {
                if (SampleDiff[i - 1] >= 0)
                    SampleDiff[i] = 1;
                else
                    SampleDiff[i] = -1;
            }
            else
            {
                if (SampleDiff[i + 1] >= 0)
                    SampleDiff[i] = 1;
                else
                    SampleDiff[i] = -1;
            }
        }
    }
    buf_print("SampleDiff", SampleDiff, SAMPLE_MAX);

    //step 3 :对相邻相等的点进行领边坡度处理
    for(i = 0; i < SAMPLE_MAX - 1; i++)
    {
        if(SampleDiff[i + 1] - SampleDiff[i] == -2) //波峰识别
        {
            pFindPV->Pos_Peak[pFindPV->Pcnt] = i + 1;
            pFindPV->Pcnt++;
        }
        else if(SampleDiff[i + 1] - SampleDiff[i] == 2) //波谷识别
        {
            pFindPV->Pos_Valley[pFindPV->Vcnt] = i + 1;
            pFindPV->Vcnt++;
        }
    }
}

/********************************************
 *  Fuction : main
 *  Note    : 模拟查找波峰波谷 
 *******************************************/ 
int main(int argc, char *argv[])
{
    int i = 0;

    initialFindPV();

    FindPV(&stFindPV, Sample);

    printf("Peak\n");
    for(i = 0 ;i< stFindPV.Pcnt;i++)
    {
        printf("-%d",stFindPV.Pos_Peak[i] + 1);  //加1是为了与上图横坐标一致 
    }

    printf("\nValley\n");
    for(i = 0 ;i< stFindPV.Vcnt;i++)
    {
        printf("-%d",stFindPV.Pos_Valley[i] + 1);
    }

    printf("\n\n");
    return 0;
}