#include <iostream>
#include <functional>
// 1
void hello(int value)
{
    std::cout << "function可以指具体的某个函数：" << value << std::endl;
}
// 2
class StaticFunc
{
public:
    static void hello(int value)
    {
        std::cout << "保存类静态成员函数："<< value << std::endl;
    }
};
// 3
class Hello
{
public:
    int i = 0;
    void operator()(int value)
    {
        i += value;
        std::cout << "重载仿函数" << i << std::endl;
    }
    void operator()(int a,int b)
    {
        std::cout << "a+b= " << a+b << std::endl;
    }
};

// 4
class Hello1
{
public:
    void hello(int value)
    {
        std::cout << "保存类成员函数" << value << std::endl;
    }
};

// 5
class LambdaHello
{
public:
    LambdaHello(int _i) : i(_i){}
    void operator()(int count)
    {
        i++;
        std::cout << "lambda参数列表重载" << count << "i= " << i << std::endl;
    }
    int i;
};

int main()
{
    // 1.function可以保存具体某个函数
    std::function<void(int)> hello1 = hello;
    hello1(1);
    // 2.可以保存类静态成员函数
    std::function<void(int)> hello2 = &StaticFunc::hello;
    hello2(2);
    // 3.保存仿函数 保存函数状态
    std::function<void(int)> hello3 = Hello();
    hello3(4);// 输出4
    hello3(4);// 输出8
    // 4.保存类成员函数
    std::function<void(Hello1 *,int)> hello4 = &Hello1::hello;
    Hello1 c;
    hello4(&c,4);

    // 5.保存lambda表达式
    int i = 0; 
    //值捕获不能修改外部变量的值,可以在其（）函数后面加上mutable修改传进来的外部变量的值，函数结束之后，外部变量的值仍然不会被改变
    // 使用引用捕获时，外部和内部的值都会被修改
    auto hello5 = [i](int count) mutable
    {
        i++;
        std::cout << "lambda hello5 :" << count << " "<< i << std::endl;
    };
    hello5(5);

    // 6.lambda参数列表重载
    auto hello6 = LambdaHello(i);
    hello6(6);

    return 0;
}