#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
//分别定义心跳包的发送间隔和连接超时的时间
#define HEARTBEAT_INTERVAL 30 // seconds
#define TIMEOUT 6 // seconds

void handle_client(int client_socket) 
{
    char buffer[1024];
    time_t last_received_time = time(0);

    while (true) 
    {
        int valread = read(client_socket, buffer, 1024);
        if (valread == 0) 
        {
            std::cout << "连接断开\n";
            break;
        }

        if (valread > 0) 
        {
            buffer[valread] = '\0';
            std::cout << "收到消息: " << buffer << std::endl;
            // Respond to client
            send(client_socket, "服务器收到消息", 27, 0);
            last_received_time = time(0);
        }

        //计算的是当前时间和 last_received_time（即上次收到客户端消息的时间）之间的差值，单位为秒。如果这个差值大于设定的 TIMEOUT 时间，则认为客户端已经超时，没有及时回应。
        if (difftime(time(0), last_received_time) > TIMEOUT) 
        {
            std::cout << "连接超时....\n";
            break; // Timeout: client failed to respond in time
        }
    }
    close(client_socket);
}

void server() 
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) 
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) 
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
        {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        std::thread(handle_client, new_socket).detach();
    }
}

int main() 
{
    server();
    return 0;
}