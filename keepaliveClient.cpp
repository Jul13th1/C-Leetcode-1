#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080

// 发送心跳包
void heartbeat_sender(int sock) 
{
    const char* heartbeat = "HEARTBEAT";
    while (true) 
    {
        // 发送心跳包
        ssize_t sent = send(sock, heartbeat, strlen(heartbeat), 0);
        if (sent == -1) 
        {
            // 如果 send 返回 -1，检查 errno
            if (errno == EPIPE || errno == ECONNRESET)
            {
                std::cerr << "Connection closed by server or connection reset\n";
                break;  // 连接断开，退出循环
            } 
            else 
            {
                std::cerr << "Error in sending data: " << strerror(errno) << "\n";
                break;  // 发生其他错误，退出循环
            }
        } 
        else 
        {
            std::cout << "Sent heartbeat (" << sent << " bytes)\n";
        }

        // 每 5 秒发送一次心跳包
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    // 退出时关闭套接字
    close(sock);
}

// 接收消息
void receive_messages(int sock) 
{
    char buffer[1024];
    while (true) 
    {
        int len = recv(sock, buffer, sizeof(buffer), 0);
        if (len > 0) 
        {
            buffer[len] = '\0';  // 确保接收到的消息是以空字符结尾
            std::cout << "Received message: " << buffer << std::endl;
        } 
        else 
        {
            std::cout << "连接丢失或者收到空数据....\n";
            break;
        }
    }
}

int main() 
{
    // 创建客户端套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    // 服务器地址信息
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr) <= 0) 
    {
        std::cerr << "Invalid address/Address not supported\n";
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        std::cerr << "Connection failed\n";
        return -1;
    }

    std::cout << "Connected to server\n";

    // 启动两个线程
    std::thread(heartbeat_sender, sock).detach();  // 启动心跳发送线程
    std::thread(receive_messages, sock).detach();  // 启动接收消息线程

    // 主线程可以继续进行其他任务，或等待线程结束
    std::this_thread::sleep_for(std::chrono::minutes(10));  // 让程序运行一段时间
    close(sock);
    return 0;
}