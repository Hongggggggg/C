#include <stdio.h>
#include <string.h>
#include <time.h>

char str[] = {"abababababcadef"};

char tar_str[] = {"abababca"};

int brute_force(char* s, char* t)
{
    int i = 0;  //主串位置
    int j = 0;  //模式串位置

    while(i < strlen(s) && j < strlen(t))
    {
        if(s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    return (j == strlen(t)) ? (i - j) : -1;
}

int next[8];

void getNext(char * p, int * next)
{
	next[0] = -1;

	int i = 0, j = -1;

	while (i < strlen(p))
	{
		if (j == -1 || p[i] == p[j])
		{
			++i;
			++j;
			next[i] = j;
		}	
		else
        {
            j = next[j];
        }
	}
}

int KMP(char * s, char * t) 
{
	int i = 0;

	int j = 0;

	while(i < strlen(s) && j < strlen(t))
	{
		if(j == -1 || s[i] == t[j]) 
		{
			i++;
            j++;
		}
	 	else
        {
            j = next[j];
        }
    }
    return (j == strlen(t)) ? (i - j) : -1;
}

void main(void)
{
    getNext(tar_str, next);

    int pos = 0;

    clock_t start = clock();

    for (int i = 0; i < 100000; i++)
    {
        pos = KMP(str, tar_str);
    }
    clock_t end = clock();
        
    printf("pos: %d, time: %d\r\n", pos, end - start);
}
