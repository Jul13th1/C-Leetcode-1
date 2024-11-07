#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 1234

void *receive_messages(void *socket) 
{
    int client_socket = *(int *)socket;
    char buffer[1024];

    while (1) 
    {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            printf("Connection closed.\n");
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);
    }
}

int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //创建socket
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket == -1)
    {
        perror("CreateClientError: ");
        return 1;
    }

    //设置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        perror("ConnectError:");
        close(client_socket);
        return 1;
    }

    //创建接收线程
    pthread_t recv_thread;
    pthread_create(&recv_thread,NULL ,receive_messages, (void *)&client_socket);

     while (1) 
    {
        // 发送消息
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    return 0;
}
