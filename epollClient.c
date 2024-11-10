#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define SERVER_ADDR "127.0.0.1"  // 服务器地址
#define SERVER_PORT 8090         // 服务器端口

// 发送消息到服务器并接收响应
void send_message(int sockfd, const char *message) 
{
    send(sockfd, message, strlen(message), 0);  // 发送消息
    char buffer[BUF_SIZE];
    ssize_t len = recv(sockfd, buffer, sizeof(buffer), 0);  // 接收服务器响应
    if (len > 0) 
    {
        buffer[len] = '\0';  // 确保字符串以'\0'结束
        printf("%s\n", buffer);  // 打印服务器响应
    } 
    else 
    {
        perror("recv");
    }
}

// 客户端程序主循环
void client_loop(int sockfd) 
{
    char command[BUF_SIZE];

    while (1) 
    {
        printf("输入命令 (register <username> <password>, login <username> <password>, exit): ");
        fgets(command, sizeof(command), stdin);  // 获取用户输入

        // 去掉输入的换行符
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "register", 8) == 0 || strncmp(command, "login", 5) == 0) 
        {
            // 注册或登录命令
            send_message(sockfd, command);
        } 
        else if (strncmp(command, "exit", 4) == 0) 
        {
            // 退出命令
            send_message(sockfd, "exit");
            close(sockfd);
            break;
        } 
        else 
        {
            printf("Unknown command. Please use register <username> <password>, login <username> <password>, or exit.\n");
        }
    }
}

int main() 
{
    // 创建 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        perror("socket");
        exit(1);
    }

    // 设置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr) <= 0) 
    {
        perror("inet_pton");
        exit(1);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        perror("connect");
        exit(1);
    }

    printf("Connected to server at %s:%d\n", SERVER_ADDR, SERVER_PORT);

    // 启动客户端交互循环
    client_loop(sockfd);

    close(sockfd);  // 关闭socket
    return 0;
}