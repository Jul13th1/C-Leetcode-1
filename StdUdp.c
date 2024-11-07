#include "StdUdp.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct UdpServer
{
    int sock;
};

struct UdpClient
{
    int sock;
    char ServerIp[20];
    short int ServerPort;
};
/////////////////////////服务器///////////////////////////
UdpS *initUdpServer(const char *ip, short int port)
{
    UdpS *s = (UdpS*)malloc(sizeof(UdpS));
    if(s == NULL)
    {
        printf("申请空间失败！\n");
        return NULL;
    }
    //获取网络套接字
    s->sock = socket(AF_INET,SOCK_DGRAM,0);
    if(s->sock < 0)
    {
        perror("socket:");
        free(s);
        return NULL;
    }

    //套接字地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    //判断绑定地址和端口号是否成功
    if(bind(s->sock,(struct sockaddr*)&addr,sizeof(addr)) != 0)
    {
        perror("bind: ");
        free(s);
        return NULL;
    }

    return s;
}

//服务器端发送消息
void UdpServerSend(UdpS *s,const char *destIP,short int port,void *ptr,size_t size)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(destIP);
    if(sendto(s->sock,ptr,size,0,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("UdpServerSend error: ");
    }
}

void UdpServerRecv(UdpS *s, void *ptr, size_t size)
{
    struct sockaddr_in addr;
    socklen_t len;
    if(recvfrom(s->sock,ptr,size,0,(struct sockaddr*)&addr,&len) < 0)
    {
        perror("UdpServerRecv error: ");
    }
}

void UdpServerClear(UdpS *s)
{
    close(s->sock);
    free(s);
}


/////////////////////////客户端//////////////////////////
UdpC *initUdpClient(const char *ServerIP, short int ServerPort)
{
    UdpC *c = (UdpC*)malloc(sizeof(UdpC));
    if(c == NULL)
    {
        perror("malloc udpcerror: ");
        return NULL;
    }

    c->sock = socket(AF_INET,SOCK_DGRAM,0);
    if(c->sock < 0)
    {
        perror("c socketerror: ");
        free(c);
        return NULL;
    }

    strcpy(c->ServerIp,ServerIP);
    c->ServerPort = ServerPort;
    return c;
}

void UdpClientSent(UdpC *c, void *ptr, size_t size)
{
    printf("1\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(c->ServerPort);
    addr.sin_addr.s_addr = inet_addr(c->ServerIp);
    if(sendto(c->sock,ptr,size,0,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("udpclient sendto error: ");
    }
    printf("2\n");
}

void UdpClientRecv(UdpC *c, void *ptr, size_t size)
{
    printf("3\n");
    struct sockaddr_in addr;
    socklen_t len;
    if(recvfrom(c->sock,ptr,size,0,(struct sockaddr*)&addr,&len) < 0)
    {
        perror("udpclient recvfrom error: ");
    }
    printf("4\n");
}

void UdpClientClear(UdpC *c)
{
    close(c->sock);
    free(c);
}
