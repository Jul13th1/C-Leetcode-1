#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define FIFO "oneFIFO"
int main()
{
    //创建管道并赋予读写权限
    mkfifo(FIFO,S_IRUSR | S_IWUSR);
    //以只读的方式打开文件
    int fd = open(FIFO,O_RDONLY);

    //判断是否打开成功
    if(fd < 0)
    {
        perror("open:");
        return -1;
    }

    while(1)
    {
        char buffer[20] = {0};
        //读取管道文件的内容
        int bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) 
        {
            printf("读取管道的信息为：%s\n", buffer);
        }
        usleep(100000); // 加入短暂延迟，避免 CPU 占用过高
    }
    
    close(fd);

    return 0;
}