#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void sendFile(const std::string& fileName, int serverSocket) {
    // 打开文件
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    // 获取文件大小
    inFile.seekg(0, std::ios::end);
    long fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    // 构建文件头（文件名和文件大小）
    std::string fileHeader = fileName + "," + std::to_string(fileSize);
    send(serverSocket, fileHeader.c_str(), fileHeader.size(), 0);

    // 发送文件数据
    char buffer[BUFFER_SIZE];
    while (inFile.read(buffer, sizeof(buffer))) {
        send(serverSocket, buffer, inFile.gcount(), 0);
    }

    // 发送剩余的数据
    if (inFile.gcount() > 0) {
        send(serverSocket, buffer, inFile.gcount(), 0);
    }

    std::cout << "File sent successfully!" << std::endl;

    // 关闭文件
    inFile.close();
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 服务器IP

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Connection failed!" << std::endl;
        return -1;
    }

    std::string fileName = "testfile.txt";  // 假设发送的文件名
    sendFile(fileName, clientSocket);

    // 等待服务器的完成确认
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    // 关闭客户端套接字
    close(clientSocket);

    return 0;
}