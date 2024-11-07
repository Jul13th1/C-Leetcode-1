#include "StdUdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
    // printf("1\n");
    if(argc != 3)
    {
        printf("输入数字不正确！\n");
        return -1;
    }

    // printf("2\n");
    UdpC *c = initUdpClient(argv[1],atoi(argv[2]));
    // printf("3\n");
    while(1)
    {
        char temp[100] = {0};
        scanf("%s",temp);
        while(getchar() != '\n');
        UdpClientSent(c,temp,100); 
    }
    UdpClientClear(c);

    return 0;
}