#ifndef __STDUDP_H_
#define __STDUDP_H_
#include <stddef.h>

//服务器
struct UdpServer;
typedef struct UdpServer UdpS;
//客户端
struct UdpClient;
typedef struct UdpClient UdpC;

UdpS *initUdpServer(const char *ip,short int port);
void UdpServerSend(UdpS *s,const char *destIP,short int port,void *ptr,size_t size);
void UdpServerRecv(UdpS *s,void *ptr,size_t size);
void UdpServerClear(UdpS *s);

UdpC *initUdpClient(const char *ServerIP,short int ServerPort);
void UdpClientSent(UdpC *c,void *ptr,size_t size);
void UdpClientRecv(UdpC *c,void *ptr,size_t size);
void UdpClientClear(UdpC *c);

#endif