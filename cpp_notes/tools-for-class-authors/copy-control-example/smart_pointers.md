# 智能指针使用
## shared_ptr
```c++
shared_ptr<string> ptr(new string("1111"));
shared_ptr<string> ptr2 = make_shared<string>("1111");

//这么写可以吗
shared_ptr<string> ptr3; 
ptr3 = new string("1111"); //错误，没有从 *string 到 shared_ptr<string> 的转化
ptr3 = std::shared_ptr<string>(new string("1111")); //可以
ptr3 = std::make_shared<string>(new string("1111")); //不可以,make_shared 调用string 的构造函数

std::shared_ptr<std::string> ptr = std::make_shared<std::string>("1111" ); //可以

```


# 智能指针使用的注意点
1. 如果使用裸指针初始化智能指针后，这个裸指针不能够再次被使用
```c++
void process(shared_ptr<int>ptr)
{
    //使用ptr
}//ptr 离开作用域，被销毁
shared_ptr<int> p(new int(42)); // 引用计数为1
process(p); //正确，拷贝p会增加它的引用技术；在process中引用计数为2
int i = *p; // 正确

int *x(new int(1024)); // x 是一个普通指针
process(x); //错误，不能将int* 转换为一个 shared_ptr<int>
process(shared_ptr<int>(x)); // 合法，但是内存会被释放
int j = *x; // 未定义的： x是一个空悬指针
```

2. 不要使用get初始化另外一个智能指针或者为智能指针赋值
```c++
shared_ptr<int> p(new int(42)); // 引用计数为1
int *q = p.get(); // 正确，但是不能释放q管理的指针
{
    shared_ptr<int>(q) ;
}//程序块结束，q被销毁，它指向的内存被释放
int foo = *p; // 未定义： p指向的内存已经被释放了
```

# 对于动态分配内存变量的初始化
1. 默认情况下，动态分配的对象是默认初始化的，这意味着内置类型或者组合类型的对象的值将是未定义的，而类类型的对象将调用默认构造函数进行初始化。
string *ps = new string ; // 初始化为空的string
int* pi = new int; //pi 指向一个未初始化的int
2. 使用直接初始化的方式
```c++
int *pi = new int(1025);
string * ps = new string(10, '9');
vector<int> * pv = new vector<int>{0,1,2,3,4,5,6};
```
3. 使用值初始化
```c++
int * pi = new int();
string * ps = new string();
```


# 使用new和delete分配内存的局限性
1. 内存分配和对象构造组合在了一起，可能会产生不必要的内存浪费。
2. 没有默认构造函数的类就无法动态分配数组了。

## 改进： 使用allocator
定义在头文件memory中，提供一种类型感知的内存分配方法，他分配的内存是原始的，未构造的。
```c++
allocator<string> alloc; 
auto const p = alloc.allocate(n); // 分配n个未初始化的string

auto q = p;
alloc.construct(q++);
alloc.construct(q++, 10,'c');
alloc.construct(q++,"hi");

while(q!= p) 
    alloc.destroy(--q);// 释放我们真正构造的string

alloc.deallocate(p,n);

//拷贝和填充未初始化的内存
vector<int> vi;
auto p = alloc.allocate(vi.size() *2);
//通过拷贝vi中的元素来构造从p开始的元素
auto q = uninitialized_copy(vi.begin(),vi.end(), p);
//将剩余元素初始化为42
uninitialized_fill_n(q,vi.size(),42);
```



