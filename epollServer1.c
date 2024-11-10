#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 10      // epoll 事件最大数
#define PORT 8090          // 服务器监听端口
#define BUF_SIZE 1024      // 缓冲区大小
#define USER_FILE "users.txt"  // 存储用户信息的文件

// 存储用户信息的结构体
typedef struct {
    int sockfd;                 // 客户端socket
    struct sockaddr_in addr;    // 客户端地址
    int logged_in;              // 登录状态
    char username[50];          // 用户名
} client_info;

client_info clients[MAX_EVENTS];  // 存储已连接的客户端信息
int client_count = 0;             // 当前连接的客户端数量

int epoll_fd;         // epoll 文件描述符
int listen_sock;      // 监听socket
struct epoll_event ev, events[MAX_EVENTS];  // epoll 事件

// 设置 socket 为非阻塞模式
void setnonblocking(int sockfd) 
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) 
    {
        perror("fcntl");
        exit(1);
    }
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

// 将客户端 socket 加入 epoll 监听
int add_client_to_epoll(int sockfd) 
{
    ev.events = EPOLLIN | EPOLLET;  // 设置事件类型为输入和边缘触发
    ev.data.fd = sockfd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ev) == -1) 
    {
        perror("epoll_ctl");
        return -1;
    }
    return 0;
}

// 创建监听 socket
int create_listen_socket() 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 5) == -1) 
    {
        perror("listen");
        exit(1);
    }

    return sockfd;
}

// 注册处理函数
void handle_client_register(int sockfd, char *msg) 
{
    char username[50], password[50];
    sscanf(msg, "register %s %s", username, password);  // 从消息中提取用户名和密码

    // 检查用户名是否已存在
    FILE *file = fopen(USER_FILE, "a+");
    if (!file) {
        perror("fopen");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) 
    {
        if (strstr(line, username)) 
        {
            send(sockfd, "Username already exists.\n", 25, 0);  // 用户名已存在
            fclose(file);
            return;
        }
    }

    // 将新用户信息写入文件
    fprintf(file, "%s %s\n", username, password);
    send(sockfd, "Registration successful.\n", 26, 0);
    fclose(file);
}

// 登录处理函数
void handle_client_login(int sockfd, char *msg, struct sockaddr_in *addr) 
{
    char username[50], password[50];
    sscanf(msg, "login %s %s", username, password);  // 从消息中提取用户名和密码

    // 检查用户名和密码是否正确
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        perror("fopen");
        return;
    }

    char line[100];
    int user_found = 0;
    while (fgets(line, sizeof(line), file)) 
    {
        char stored_username[50], stored_password[50];
        sscanf(line, "%s %s", stored_username, stored_password);

        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            user_found = 1;
            break;
        }
    }

    if (!user_found) 
    {
        send(sockfd, "Invalid username or password.\n", 30, 0);  // 用户名或密码错误
        fclose(file);
        return;
    }

    // 登录成功，检查是否已登录
    for (int i = 0; i < client_count; i++) 
    {
        if (strcmp(clients[i].username, username) == 0) 
        {
            // 如果同一用户在不同IP登录，踢掉之前的连接
            if (clients[i].addr.sin_addr.s_addr != addr->sin_addr.s_addr) 
            {
                send(clients[i].sockfd, "You have been logged out due to another login.\n", 45, 0);
                close(clients[i].sockfd);
                clients[i].logged_in = 0;
            } 
            else 
            {
                send(sockfd, "Already logged in from the same IP.\n", 35, 0);
                fclose(file);
                return;
            }
        }
    }

    // 登录成功，记录登录信息
    strcpy(clients[client_count].username, username);
    clients[client_count].logged_in = 1;
    clients[client_count].sockfd = sockfd;
    clients[client_count].addr = *addr;
    client_count++;

    send(sockfd, "Login successful.\n", 18, 0);
    fclose(file);
}

// 处理客户端的命令
void handle_client_command(int sockfd, char *msg, struct sockaddr_in *addr) 
{
    if (strncmp(msg, "register", 8) == 0) 
    {
        handle_client_register(sockfd, msg);
    } else if (strncmp(msg, "login", 5) == 0) 
    {
        handle_client_login(sockfd, msg, addr);
    } 
    else if (strncmp(msg, "exit", 4) == 0) 
    {
        send(sockfd, "Goodbye!\n", 9, 0);
        close(sockfd);
    } 
    else 
    {
        send(sockfd, "Unknown command.\n", 17, 0);
    }
}

// 服务器事件处理循环
void server_loop() 
{
    while (1) 
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) 
        {
            perror("epoll_wait");
            exit(1);
        }

        for (int i = 0; i < nfds; i++) 
        {
            if (events[i].data.fd == listen_sock) 
            {
                // 新的客户端连接
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_sockfd = accept(listen_sock, (struct sockaddr*)&client_addr, &client_len);
                if (client_sockfd == -1) 
                {
                    perror("accept");
                    continue;
                }

                //设置sockfd为非阻塞模式
                setnonblocking(client_sockfd);
                //将客户端的sockfd加入epoll进行监听
                add_client_to_epoll(client_sockfd);
                printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            } 
            else 
            {
                // 接受已连接的客户端发送消息
                char buffer[BUF_SIZE];
                int client_sockfd = events[i].data.fd;
                ssize_t len = recv(client_sockfd, buffer, sizeof(buffer), 0);
                if (len == -1) 
                {
                    perror("recv");
                    continue;
                }
                if (len == 0) 
                {
                    close(client_sockfd);
                    continue;
                }
                buffer[len] = '\0';  // 确保消息以 '\0' 结尾
                handle_client_command(client_sockfd, buffer, &((struct sockaddr_in*)&events[i].data.ptr)->sin_addr);
            }
        }
    }
}

int main() 
{
    listen_sock = create_listen_socket();  // 创建监听socket
    epoll_fd = epoll_create1(0);          // 创建epoll实例
    if (epoll_fd == -1) 
    {
        perror("epoll_create");
        exit(1);
    }

    setnonblocking(listen_sock);
    add_client_to_epoll(listen_sock);  // 将监听socket加入epoll

    server_loop();  // 启动服务器事件循环

    close(listen_sock);
    close(epoll_fd);
    return 0;
}