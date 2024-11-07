#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 102400

//接收客户端的文件头
void recvFile(int clientSocket)
{
    // 定义一个字符数组 buffer，用于存放从客户端接收到的数据（文件头和文件内容）
    char buffer[BUFFER_SIZE];
    // 使用 recv 函数从 clientSocket 套接字接收数据，存入 buffer 中。接收到的数据大小将存储在 bytesReceived 中
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) 
    {
        std::cerr << "Failed to receive file header!" << std::endl;
        return;
    }

    buffer[bytesReceived] = '\0';  // Null terminate the string
    //将接收到的文件头数据（存储在 buffer 中）转换为一个 std::string 对象。假设接收到的数据格式是 "filename,file_size"，即文件名和文件大小由逗号分隔。
    std::string fileInfo(buffer);
    // 通过 substr 函数从 fileInfo 字符串中提取文件名。find(",") 找到逗号的位置，substr(0, fileInfo.find(",")) 获取逗号前的部分，即文件名
    std::string fileName = fileInfo.substr(0, fileInfo.find(","));
    // 通过 fileInfo.find(",") + 1 得到文件大小的开始位置。然后使用 substr 从该位置截取字符串，并通过 std::stol 将字符串转换为 long 类型的文件大小。
    long fileSize = std::stol(fileInfo.substr(fileInfo.find(",") + 1));
    std::cout << "收到文件名 大小: " << fileName << " (" << fileSize << " bytes)" << std::endl;

    // 创建文件以写入数据
    // 使用 std::ofstream 打开一个输出文件流 outFile，并指定文件名 fileName
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) 
    {
        std::cerr << "文件创建失败!" << std::endl;
        return;
    }

    // 接收文件数据
    long totalBytesReceived = 0;
    // 使用 while 循环持续接收文件数据，直到接收的数据量达到文件的总大小 fileSize。
    while (totalBytesReceived < fileSize) 
    {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) 
        {
            std::cerr << "收取文件失败!" << std::endl;
            break;
        }
        outFile.write(buffer, bytesReceived);
        totalBytesReceived += bytesReceived;
    }

    // 关闭文件
    std::cout << "文件接收成功!" << std::endl;
    outFile.close();

    // 发送传输完成的结束标志
    const char* endMessage = "服务器文件接受完成!";
    send(clientSocket, endMessage, strlen(endMessage), 0);

    // 关闭客户端连接
    close(clientSocket);
}

int main() 
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) 
    {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Binding failed!" << std::endl;
        return -1;
    }

    // 监听客户端连接
    if (listen(serverSocket, 5) == -1) 
    {
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == -1) 
    {
        std::cerr << "Accept failed!" << std::endl;
        return -1;
    }

    // 接收文件
    recvFile(clientSocket);

    // 关闭服务器套接字
    close(serverSocket);

    return 0;
}