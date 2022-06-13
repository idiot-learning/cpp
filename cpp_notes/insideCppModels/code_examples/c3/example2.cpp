#include<stdio.h>
struct Base1 {int val1;};
struct Base2 {int val2;};
struct Derived : Base1, Base2 {};

void func1 (int Derived::*dmp, Derived *pd)
{
    printf("pd->*dmp is : %p\n",pd->*dmp);
    printf("pd->*dmp is : %p\n",dmp);
}

void func2(Derived * pd)
{
    int Base2::*bmp = &Base2::val2;
    printf("Base2::*bmp  is : %p\n",&Base2::val2); 
    func1(bmp ,pd);
}

int main()
{
    Derived* d = new Derived();

    printf("d  is : %p\n",d);

    func2(d);

    printf("Base1::val1 is : %d\n",&Base1::val1); 
    printf("Base2::val2 is : %d\n",&Base2::val2); 
    printf("Derived::val1 is : %d\n",&Derived::val1); 
    printf("Derived::val2 is : %d\n",&Derived::val2); 
    return 0;
}