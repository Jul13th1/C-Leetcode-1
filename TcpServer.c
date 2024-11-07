#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 1234 //设置端口号
#define MAX_CLIENTS 2 //最大客户端连接数量

int clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg)
{
    int client_socket = *(int *)arg;
    char buffer[1024];

    while(1)
    {
        int bytes_received = recv(client_socket,buffer,sizeof(buffer) - 1,0);
        if(bytes_received < 0)
        {
            break;
        }
        //转发消息给其他客户端
        pthread_mutex_lock(&clients_mutex);
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            if(clients[i] != 0 && clients[i] != client_socket)
            {
                send(clients[i],buffer,bytes_received,0);
            }
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    //清理资源
    close(client_socket);
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        if(clients[i] == client_socket)
        {
            clients[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    return NULL;
}

int main()
{
    int server_socket,client_socket;
    struct sockaddr_in server_addr,client_addr;

    socklen_t addrlen = sizeof(client_addr);

    //初始化客户端数组
    memset(clients,0,sizeof(clients));

    //创建socket
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket == -1)
    {
        perror("ServerCreateError: ");
        return 1;
    }

    //设置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //绑定socket
    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        perror("ServerBindError: ");
        close(server_socket);
        return 1;
    }

    //开始监听
    if(listen(server_socket,MAX_CLIENTS) < 0)
    {
        perror("ListenServerError: ");
        close(server_socket);
        return 1;
    }
    printf("Server listening on port %d\n",PORT);

    while(1)
    {
        //接收客户端连接
        printf("addlen = %d\n",addrlen);
        client_socket = accept(server_socket,(struct sockaddr*)&client_addr,&addrlen);
        printf("appect %d\n",client_socket);
        if(client_socket < 0)
        {
            sleep(3);
            perror("ClinetAcceptError: ");
            sleep(5);
            continue;
        }

        //将客户端加入到数组里面
        pthread_mutex_lock(&clients_mutex);
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            if(clients[i] == 0)
            {
                clients[i] = client_socket;
                break;
            }
        }
        pthread_mutex_unlock(&client_socket);

        //创建线程处理客户端
        pthread_t thread_id;
        pthread_create(&thread_id,NULL,handle_client,(void *)&client_socket);
    }

    

    close(server_socket);
    return 0;
}