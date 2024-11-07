#include <iostream>
#include <thread>
#include <functional>

// 与线程结合 std::bind 可以用来将一个函数与其参数绑定，并传递给线程，从而在后台执行
void printSum(int a, int b) 
{
    std::cout << "Sum: " << a + b << std::endl;
}

int main() 
{
    std::thread t(std::bind(printSum, 10, 20));
    t.join();  // 等待线程完成
    
    return 0;
}