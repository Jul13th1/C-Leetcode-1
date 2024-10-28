#include <iostream>

/*
好处
更高效：少了一次调用默认构造函数的过程。
有些场合必须要用初始化列表：
常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面
引用类型，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面
*/

class MyClass {
public:
    MyClass(int& ref) : myRef(ref) {} // 在初始化列表中初始化引用
    void print() { std::cout << myRef << std::endl; }

private:
    int& myRef; // 引用成员
};

/*
class MyClass1 
{
public:
    // 常量成员变量
    const int constantValue;

    // 构造函数，使用初始化列表初始化常量成员
    MyClass1(int value) : constantValue(value) 
    {
        // 在这里不能对 constantValue 赋值
        // constantValue = value; // 这会导致编译错误
    }

    void display() const {
        std::cout << "Constant Value: " << constantValue << std::endl;
    }
};
*/