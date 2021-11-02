//代码编译正确，并能成功打印

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
    ~Class(){};
};

int main()
{
    Class c1;
}