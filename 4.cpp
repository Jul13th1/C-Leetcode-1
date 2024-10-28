/*
一：获取类型信息：
typeid 可以用于获取变量、对象或表达式的类型。它返回一个 std::type_info 对象，该对象包含类型的相关信息。
#include <iostream>
#include <typeinfo>

class Base {};
class Derived : public Base {};

int main() {
    Derived d;
    Base* b = &d;

    std::cout << "Type of d: " << typeid(d).name() << std::endl; // Derived
    std::cout << "Type of b: " << typeid(*b).name() << std::endl; // Base
    return 0;
}

多态类型：如果使用 typeid 检查基类指针的实际类型，需要确保基类有虚函数。否则，typeid 将返回基类的类型信息，而不是派生类的信息。
类型名称：返回的类型名称可能与预期的名称不同，因为它通常是经过编码的，可能需要使用 abi::__cxa_demangle（在 GCC 和 Clang 中）来进行解码。
编译时与运行时：typeid {在编译时对静态类型进行求值，但在运行时用于动态类型的检查。}
#include <iostream>
#include <typeinfo>
class Base {
    virtual void func() {} // 虚函数
};
class Derived : public Base {};
int main() {
    Base* b = new Derived();

    // 使用 typeid 检查实际类型
    std::cout << "Type of b: " << typeid(*b).name() << std::endl; // 输出 Derived

    delete b;
    return 0;
}