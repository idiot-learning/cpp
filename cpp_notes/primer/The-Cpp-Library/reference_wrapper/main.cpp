#include"led.h"

int main(int argc, char* argv[])
{
    int a;
    std::reference_wrapper<int>  b = std::ref(a);
    Led led(b);
    led.Print();
    return 0;
}