#include<stdio.h>
class Point3d
{
public:
    virtual ~Point3d();

    static Point3d origin;
    float x,y,z;
};

int main()
{
    //how to access the vptr in class Point3d
    //printf("size of vptr is: ")
    printf("&Point3d::x = %p\n", &Point3d::x);
    printf("&Point3d::y = %p\n", &Point3d::y);
    printf("&Point3d::z = %p\n", &Point3d::z);
    return 0;
}