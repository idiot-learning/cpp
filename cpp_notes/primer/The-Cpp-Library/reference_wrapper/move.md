# 动态内存管理类 - StrVec
- 使用 `allocator`获得原始内存
- 三个指针成员指向其元素使用的内存 `elements` 指向分配内存的首元素， `first_free`最后一个实际元素之后的位置， `cap`指向分配的内存末尾之后的位置 
- 名为alloc的静态成员，会分配StrVec使用的内存
- 四个工具函数： `alloc_n_copy`分配内存并拷贝一个给定范围的元素, `free`销毁构造的元素并释放内存, `chk_n_alloc` 确保至少有容纳一个新元素的空间，如果没有会调用reallocate函数分配, `reallocate` 在内存用完时，分配新的内存


```cpp
//StrVec.h
class StrVec
{
public:
    StrVec() : // allocator 成员默认初始化
        elements(nullptr), first_free(nullptr), cap(nullptr){}
    StrVec(const StrVec&); 
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const std::string &);
    size_t size() const {return first_free - elements;}
    size_t capacity() const{return cap - elments;}
    std::string * begin() const{return elements;}
    std::string * end() const {return first_free;}
private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc() {if(size() == capacity()) reallocate();}
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::sttring*);
    void free(); 
    void reallocate();
    std::string * elements;
    std::string* first_free;
    std::string * cap;
};

void StrVec::push_back(const string & s)
{
    chk_n_alloc(); 
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> alloc_n_copy(const std::string* b, const std::sttring* e)
{
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b,e,data)};
}

void StrVec::free()
{}
if(elements){
    for(auto p = first_free; p != elemnts;)
        alloc.destroy(--p); // destroy 会运行string的析构函数
    alloc.deallocate(elements,cap-elements);
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec(){free();}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocae()
{
    auto newcapacity = size() ? 2*size():1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(size_t i = 0 ; i != size() ; i++)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
```

# 移动操作与异常


# 合成的移动操作
- 如果我们没有定义拷贝构造或者拷贝赋值运算符，编译器总是会为我们合成这些操作。拷贝操作要么定义为逐成员拷贝，要么为对象赋值，要么是删除的函数。
- 但是如果我们定义了拷贝构造和拷贝赋值运算符，那么编译器不会为我们合成这些操作，同时也不会合成移动构造和赋值运算符。如果一个类没有移动操作，则通过正常的函数匹配，会调用对应的拷贝操作来替代移动操作。
- 只有当一个类没有定义任何自己版本的拷贝控制成员，且它的所有数据成员都能够移动构造或者移动赋值时，编译器才会为它合成移动构造函数或移动赋值运算符。
相应的，如果一个类定义了一个移动构造函数和/或一个移动赋值运算符，则该类的合成拷贝构造函数和拷贝赋值运算符会被定义为删除的。

```cpp
//编译器会为X 和 hasX 合成移动操作
struct X {
    int i;  // 内置类型可移动
    std::string s; // string 定义了自己的移动操作
};

struct hasX{
    X men; // X 有合成的移动操作
};

X x, x2 = std::move(x) ; //使用合成的移动构造函数
hasX hx, hx2 = std::move(hx); // 使用合成的移动构造
```
## 编译器将移动构造定义为删除的函数 
和拷贝操作不同，移动操作永远不会隐式定义为删除的函数。
但是如果我们显示要求编译器生成 =default的移动操作，且编译器不能移动所有成员，则编译器会将移动操作定义为删除的函数。
将移动操作定义为删除的函数遵循的原则：
1. 有类成员定义了自己的拷贝构造函数且未定义移动构造函数，或者有类成员未定义拷贝构造函数且编译器不能为其合成移动构造函数。
2. 类成员的移动操作被定义为删除或者不可访问的
3. 类的析构函数被定义为删除或者不可访问
4. 类成员是const 的或是引用，则类的移动赋值运算符被定义为删除的。


# 移动右值，拷贝左值

# 如果没有移动构造函数，右值也被拷贝

# 移动迭代器
```cpp

```

# 右值引用和成员函数
成员函数同时提供拷贝和移动版本
拷贝版本：`void push_back(const X&)`
移动版本：`void push_back(X &&)`

```cpp

```

# 右值和左值引用成员函数
指出`this` 的左值和右值属性的方式与定义const成员相同，在参数列表后防止一个引用限定符，可以是 `&` 和 `&&`。 和const限定符类似，该限定符只能用于（非static）的成员函数，且必须同时出现在声明和定义中。
```cpp
class Foo{
public:
    Foo someMem() & const; //错误：const 限定符必须在前
    Foo someMen() const &; //正确
};
```

## 重载和引用函数
如果一个成员函数有引用限定符，则具有相同参数列表的所有版本都必须有引用限定符。