#include <stdio.h>

int moving_average_filter(int x_n, int avg_last, int n)
{
    int avg = 0;

    //avg = ((n - 1) * avg_last + x_n) / n;

    avg = avg_last + (x_n - avg_last) / n;

    return avg;
}
