#include <iostream>
#include <thread>

class base
{
    public:
    virtual void Run(int i, int j , int k)=0; 
};

class A : public base
{
   public:
    void Run(int i, int j , int k )override{
        std::cout << "A Run is called" << std::endl;
    };
    void f(int i) { std::cout << i << std::endl; }
};

int main()
{
    A a;
    std::thread t(&A::f, &a,
                  42);  // 第一个参数为成员函数地址，第二个参数为实例地址
    std::thread t2(&A::Run, a, 11, 12, 13);

    t.join();
    t2.join();
}