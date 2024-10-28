// 1. 只能在堆上生成对象
// 方法：将析构函数设置为私有。
// 原因：当类的析构函数是私有的时，编译器在处理栈上对象的生命周期时会发现无法访问析构函数，从而不允许在栈上创建该类的对象。

#include <iostream>

class HeapOnly {
private:
    // 私有构造函数
    HeapOnly() {
        std::cout << "HeapOnly created!" << std::endl;
    }

    // 私有析构函数
    ~HeapOnly() {
        std::cout << "HeapOnly destroyed!" << std::endl;
    }

public:
    static HeapOnly* create() {
        return new HeapOnly(); // 只能在堆上创建
    }
};

int main() {
    HeapOnly* obj = HeapOnly::create();
    delete obj; // 必须手动释放
    return 0;
}
// 2. 只能在栈上生成对象
// 方法：将 new 和 delete 重载为私有。

// 原因：当类的 new 和 delete 操作符被设置为私有时，任何尝试在堆上创建对象的操作都会失败，因为无法调用 new。
#include <iostream>

class StackOnly {
private:
    // 私有构造函数
    StackOnly() {
        std::cout << "StackOnly created!" << std::endl;
    }

    // 将 new 和 delete 设置为私有
    void* operator new(size_t) = delete; // 禁止在堆上创建对象
    void operator delete(void*) = delete;

public:
    static StackOnly create() {
        return StackOnly(); // 可以在栈上创建对象
    }

    void greet() {
        std::cout << "Hello from StackOnly!" << std::endl;
    }
};

int main() {
    StackOnly obj = StackOnly::create(); // 在栈上创建对象
    obj.greet();
    
    // StackOnly* ptr = new StackOnly(); // 这将会导致编译错误
    return 0;
}
总结
只能在堆上创建对象：通过私有析构函数来限制栈上对象的创建。
只能在栈上创建对象：通过私有化 new 和 delete 操作符来阻止堆上对象的创建。