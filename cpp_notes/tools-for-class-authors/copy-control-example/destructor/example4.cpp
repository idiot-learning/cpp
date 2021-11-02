////代码编译正确，并能成功打印

class Interface
{
public:
    Interface(){};
    virtual ~Interface() = default;
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