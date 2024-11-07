#include <functional>
#include <iostream>

// 1
void hello(int value)
{
    std::cout << "将参数与函数绑定到一起" << value << std::endl;
}
// 2
class Hello1
{
public:
    void hello(int value)
    {
        std::cout << "绑定类成员函数" << value << std::endl;
    }
};
// 3
void hello3(int a,int b, int c)
{
    std::cout << " 多个参数和多个占位符" << a+b+c << std::endl;
}

int main()
{
    // 1.将参数与函数绑定到一起
    auto b_hello1 = std::bind(hello,1);
        // 此时的函数就不需要绑定参数了
    b_hello1();

    // 2.绑定类成员函数
    Hello1 c;
    auto b_hello2 = std::bind(&Hello1::hello,&c,2);
    b_hello2();

    // 3.提供占位符
    auto b_hello3 = std::bind(&Hello1::hello,&c,std::placeholders::_1);
    b_hello3(3);

    // 4. 多个参数和多个占位符
    auto b_hello4 = std::bind(hello3,10, std::placeholders::_1, 20);
    b_hello4(1);

    
    return 0;
}