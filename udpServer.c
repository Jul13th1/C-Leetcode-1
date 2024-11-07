#include "StdUdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg,char *argv[])
{
    if(arg != 3)
    {
        printf("请输入合法数字！\n");
        return -1;
    }

    UdpS *s = initUdpServer(argv[1],atoi(argv[2]));
    while(1)
    {
        char temp[100] = {0};
        UdpServerRecv(s,temp,100);
        printf("收到来自客户端的消息：%s\n",temp);
    }
    UdpServerClear(s);
    return 0;
}