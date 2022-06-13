#include"led.h"

class Led::Impl
{
public:
    Impl(std::reference_wrapper<int> a) : defect_num(a){};
    ~Impl() = default;
    void print()
    {
        std::cout << "a" <<std::endl;
    }
private:
    std::reference_wrapper<int> defect_num;
    int a;
};

Led::Led(std::reference_wrapper<int> a): impl_(std::make_shared<Impl>(a)){};
Led::~Led(){};

void Led::Print()
{
    impl_->print();
}