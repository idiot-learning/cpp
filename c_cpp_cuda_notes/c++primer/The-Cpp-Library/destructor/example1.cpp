//提示找不到虚表
//原因是子类的析构没有实例化。
class Interface
{
public:
    Interface(){};
    virtual ~Interface(){};
};

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

