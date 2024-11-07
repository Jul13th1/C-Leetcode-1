#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // 创建子进程

    if (pid < 0)
    {
        perror("fork失败");
        return 1;
    }

    if (pid == 0) 
    {
        // 子进程
        for (int i = 0; i < 5; i++) 
        {
            printf("子进程：%d\n", i);
            sleep(1); // 模拟耗时操作
        }
    } 
    else 
    {
        // 父进程
        for (int i = 0; i < 5; i++) 
        {
            printf("父进程：%d\n", i);
            sleep(1); // 模拟耗时操作
        }
        wait(NULL); // 等待子进程结束
    }

    return 0;
}