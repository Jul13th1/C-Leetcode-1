/*
   四种类型转换 

// 一：static_cast
    static_cast 的使用场景
    1.数值类型转换：通常用于不同数值类型之间的转换，比如 float 到 int，这是最常见的用法。
    float f = 3.14f;
    int i = static_cast<int>(f); // 转换为整数，结果是 3

    2.指针或引用转换：
    向上转换（Upcasting）：将子类指针或引用转换为父类指针或引用，这是安全的，且可以隐式转换。
    class Base {};
    class Derived : public Base {};
    Derived d;
    Base* b = static_cast<Base*>(&d); // 安全，向上转换

    3.向下转换（Downcasting）：将父类指针或引用转换为子类指针或引用，这种转换可能不安全，如果父类指针实际指向的不是该子类的实例，就会导致未定义行为。
    Base* b = new Derived();
    Derived* d = static_cast<Derived*>(b); // 安全，前提是 b 实际指向 Derived

    4.不同类型的类转换：在类层次结构中，可以使用 static_cast 在类层次之间进行转换，但必须确保转换是合法的。
    class A {};
    class B : public A {};
    class C : public A {};
    B b;
    A* a = static_cast<A*>(&b); // 向上转换
    C* c = static_cast<C*>(a); // 不安全，可能导致未定义行为
    安全性
    static_cast 不执行运行时类型检查，因此使用时需要确保类型转换的合法性。这是它与 dynamic_cast 的主要区别，后者在运行时会检查类型安全性。

// 二：dynamic_cast 的特点
    用于多态类型的转换：
    dynamic_cast 主要用于具有虚函数的类，以确保正确处理多态。
    运行时类型检查：
    在运行时，dynamic_cast 会检查对象的实际类型，确保转换的安全性。这意味着只有在对象的实际类型与目标类型匹配时，转换才会成功。
    适用于指针或引用：

    dynamic_cast 只能应用于指针或引用，不能用于普通对象。
    失败处理：
    如果转换失败，对于指针类型，返回 nullptr；对于引用类型，抛出 std::bad_cast 异常。
    类层次结构中的移动：
    可以在类层次结构中进行向上转换（upcasting）和向下转换（downcasting）。
    向上转换总是安全的，而向下转换需要确保对象确实是目标类型或其子类的实例。
    示例代码
#include <iostream>
#include <typeinfo>

class Base {
    virtual void foo() {} // 需要至少一个虚函数以实现多态
};

class Derived : public Base {
    void foo() override {}
};

void example(Base* base) {
    // 向下转换
    Derived* derived = dynamic_cast<Derived*>(base);
    if (derived) {
        std::cout << "转换成功，derived 不是 nullptr\n";
    } else {
        std::cout << "转换失败，derived 是 nullptr\n";
    }
}

int main() {
    Base base;
    Derived derived;

    example(&derived); // 成功转换
    example(&base);    // 失败转换

    return 0;
}
总结
dynamic_cast 是进行安全类型转换的工具，特别是在使用多态时。
它通过运行时检查确保转换的安全性，避免了潜在的类型错误。
在面向对象编程中，合理使用 dynamic_cast 可以提高代码的安全性和可维护性。

// 三.const_cast
    删除 const 和 volatile 属性：
    const_cast 用于在类型转换中添加或删除 const 和 volatile 属性。这使得你可以修改原本被声明为 const 或 volatile 的变量。
    例如，可以将 const int* 转换为 int*，从而允许对其内容进行修改。
    语法：
    const_cast<new_type>(expression)
    new_type 是目标类型，expression 是要转换的变量。
    不影响内存中的实际数据：
    const_cast 只是改变了类型的视图，不会改变存储的数据本身。如果原始数据是 const，在转换后修改它将导致未定义行为。
    不适用于其他类型的转换：
    const_cast 仅限于 const 和 volatile 的转换，不适用于其他类型，如基类与派生类之间的转换。
    示例代码
    #include <iostream>

    void modifyValue(const int* ptr) {
        // 使用 const_cast 删除 const 属性
        int* modifiablePtr = const_cast<int*>(ptr);
        *modifiablePtr = 10; // 修改指向的值
    }

    int main() {
        int x = 5;
        const int* constPtr = &x;

        // 修改 const 变量
        modifyValue(constPtr);
        
        std::cout << "x 的新值: " << x << std::endl; // 输出 10
        return 0;
    }
注意事项
使用 const_cast 时需谨慎：如果原始数据是 const，则对其进行修改会导致未定义行为。
通常建议避免不必要地使用 const_cast，可以通过设计避免将 const 对象传递给需要修改的函数。

四.reinterpret_cast 
    是 C++ 中的一种强制类型转换运算符，用于在不同类型之间进行低级别的指针和引用转换。
    尽管它很强大，但滥用 reinterpret_cast 可能会导致潜在的风险和未定义行为。以下是一些重要的要点：

    用法
    指针类型转换：
    你可以使用 reinterpret_cast 将任何指针类型转换为任何其他指针类型。例如，从 char* 转换为 int*，或者从一个类的指针转换为一个不相关类的指针。
    这种转换不检查类型安全，因此在使用时要特别小心，确保你理解底层内存布局。
    整数与指针之间的转换：
    你还可以将整数类型转换为指针类型，反之亦然。这在底层编程（如操作系统或硬件编程）中可能有用，但需要小心，确保地址有效。
    保留特性：
    reinterpret_cast 不会丢弃 const、volatile 或 __unaligned 特性。这意味着转换后的指针仍然保留原有的属性。
    风险
    未定义行为：
    如果你将一个指针转换为不相关的类型，并试图通过这个指针访问内存，可能会导致未定义行为。
    内存对齐：

    不同类型可能对内存对齐有不同要求，错误的对齐可能导致性能下降或硬件错误。
    类型安全：

    reinterpret_cast 完全绕过了类型系统的保护，使得类型安全性降低。
    实际用途
    reinterpret_cast 的一个常见用途是在哈希函数中。例如，你可能希望将不同类型的值映射到哈希表的索引。通过将这些值转换为指针或整数类型，你可以确保它们在计算索引时不会冲突。

    示例
    cpp
    #include <iostream>

    struct A {
        int x;
    };

    struct B {
        float y;
    };

    int main() {
        A a;
        a.x = 10;

        // 将 A 的指针转换为 B 的指针
        B* b = reinterpret_cast<B*>(&a);
        // 访问 b 的成员可能导致未定义行为
        b->y = 5.0f; // 不安全的操作

        std::cout << "A.x: " << a.x << std::endl; // 输出可能不正确
        return 0;
    }
