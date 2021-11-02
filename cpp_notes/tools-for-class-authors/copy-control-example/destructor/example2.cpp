//提示找不到基类析构
//原因是基类的析构声明为纯虚函数没有实例化
class Interface
{
public:
    Interface(){};
    virtual ~Interface() = 0;
};

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