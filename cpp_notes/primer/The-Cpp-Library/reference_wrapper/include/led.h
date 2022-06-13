#ifndef __LED__
#define __LED__

#ifdef SM_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#include<functional>
#include<memory>
#include<iostream>

// #ifdef _MSC_VER

// #else
// #define DLL_API
// #endif

class DLL_API Led
{
public:
    Led(std::reference_wrapper<int> a) ;
    ~Led();
    void Print();
private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

#endif