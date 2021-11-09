//提示找不到虚表
//基类析构声明为纯虚且实例化，子类析构没有实例化
#include <iostream>

class Interface
{
public:
    Interface(){};
    virtual ~Interface() = 0;
};

Interface::~Interface()
{
    std::cout << "Interface::~Interface" << std::endl;
}

class Class : public Interface
{
public:
    Class(){};
    ~Class();
};

int main()
{
    Class c1;
}