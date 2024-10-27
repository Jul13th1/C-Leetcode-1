#include <iostream>

class MyClass 
{
public:
    // 常量成员变量
    const int constantValue = 1;

    // 构造函数，使用初始化列表初始化常量成员
    MyClass(int value) : constantValue(value) 
    {
        // 在这里不能对 constantValue 赋值
        // constantValue = value; // 这会导致编译错误
    }

    void display() const {
        std::cout << "Constant Value: " << constantValue << std::endl;
    }
};

int main() 
{
    MyClass obj(10);
    obj.display(); // 输出：Constant Value: 10

    return 0;
}