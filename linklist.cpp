#include <iostream>
#include <string>

class myList
{
public:
    struct List
    {
        std::string name;
        int price;
        int rate;
        List* next;
        List(const std::string& n, int p, int r) : name(n), price(p), rate(r), next(nullptr) {}
    };
public:
    //1.创建头尾结点，构造函数
    myList()
    {
        head = nullptr;
        tail = nullptr;
    }

    //2.拷贝构造函数
    // myList(const myList &other)
    // {
    //     List *cur = other.head;
    //     //调用添加新节点函数
    //     while(cur)
    //     {
    //         append(cur->name,cur->price,cur->rate);
    //         cur = cur->next;
    //     }
    // }

    //3.添加新节点 尾插
    void append(std::string name,int price,int rate)
    {
        List *newNode = new List(name,price,rate);
        // std::cout << "name: " << newNode->name << std::endl;
        if (!head) 
        {
            head = tail = newNode; // 如果链表为空，头尾指向新节点
        } 
        else 
        {
            tail->next = newNode; // 将新节点加到尾部
            tail = newNode;       // 更新尾节点
        }
    }

    //4.移除某个节点
    // void remove(const std::string &name)
    // {
    //     //判断链表情况
    //     //1.如果链表为空，直接返回
    //     if(head == nullptr)
    //     {
    //         return;
    //     }
    //     //2.如果删除的是头结点
    //     if(head->name == name)
    //     {
    //         //保存头结点，让头结点指向下一节点更新头结点
    //         List *temp = head;
    //         head = head->next;
    //         delete temp;

    //         //如果删除完头结点链表为空了，也直接返回
    //         if(head == nullptr)
    //         {
    //             tail = nullptr;
    //         }
    //         return;
    //     }

    //     //遍历要删除的节点
    //     List *cur = head;
    //     while(cur->next && cur->next->name != name)
    //     {
    //         cur = cur->next;
    //     }

    //     //如果找到了节点
    //     if(cur->next)
    //     {
    //         List *temp = cur->next;
    //         cur->next = cur->next->next;

    //         //如果被删除的节点是尾节点
    //         if(cur->next == nullptr)
    //         {
    //             //更新尾节点
    //             tail = cur;
    //         }
    //         delete temp;
    //     }
    // }

    //5.查询某个几点
    // List *find(const std::string &name)
    // {
    //     List *cur = head;
    //     while(cur)
    //     {
    //         if(cur->name == name)
    //         {
    //             //找到就返回
    //             return cur;
    //         }
    //         else
    //         {
    //             //找不到就指向下一节点 进行循环
    //             cur = cur->next;
    //         }
    //     }

    //     //链表循环结束还没有找到，就直接返回
    //     return nullptr;
    // }

    // //根据余额排序 //快排 冒泡 插入
    // void sort()
    // {
    //     //

    // }

    //输出所有节点
    void show()
    {
        // std::cout <<  " 2 "<< std::endl;
        List *cur = head;

         // 检查链表是否为空
        if (cur == nullptr) 
        {
            std::cout << "The list is empty!" << std::endl;
            return;  // 如果链表为空，直接返回
        }
        while(cur)
        {
            // std::cout <<  " 3 "<< std::endl;
            std::cout << "name: " << cur->name << ",price " << cur->price << ",rage " << cur->rate << std::endl;
            cur = cur->next;
        }
    }

    //调整存款利率
    void setRete(int newRate)
    {
        List *cur = head;
        while(cur)
        {
            //将节点上的所有利率都设为设定的值
            cur->rate = newRate;
            cur = cur->next;
        }
    }

private:
    List *head;
    List *tail;
};  

int main()
{
    myList list;

    list.append("A", 1000, 5);
    list.append("B", 1500, 6);
    list.append("C", 1800, 4);

    std::cout <<  " 1 "<< std::endl;
    //输出链表
    list.show();
    

    return 0;
}