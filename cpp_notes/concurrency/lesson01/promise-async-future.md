# use opencv in a cmake project




# promise 和 async 均返回一个future 类

future 类可以接收线程返回的信息

## promise
```c++
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double> &&prms, double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else
            prms.set_value(num / denom);
    }
    catch (...)
    {
        prms.set_exception(std::current_exception());
    }
}

int main()
{
    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    t.join();

    return 0;
}

```

## async
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
 
std::mutex m;
struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};
 
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);
 
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // 以默认策略调用 x.foo(42, "Hello") ：
    // 可能同时打印 "Hello 42" 或延迟执行
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // 以 deferred 策略调用 x.bar("world!")
    // 调用 a2.get() 或 a2.wait() 时打印 "world!"
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // 以 async 策略调用 X()(43) ：
    // 同时打印 "43"
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // 打印 "world!"
    std::cout << a3.get() << '\n'; // 打印 "53"
} // 若 a1 在此点未完成，则 a1 的析构函数在此打印 "Hello 42"

```

# promise 和 future 之间通信

```c++
#include <thread>
#include <future>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
 
int main()
{
    std::istringstream iss_numbers{"3 4 1 42 23 -23 93 2 -289 93"};
    std::istringstream iss_letters{" a 23 b,e a2 k k?a;si,ksa c"};
 
    std::vector<int> numbers;
    std::vector<char> letters;
    std::promise<void> numbers_promise, letters_promise;
 
    auto numbers_ready = numbers_promise.get_future();
    auto letter_ready = letters_promise.get_future();
 
    std::thread value_reader([&]
    {
        // I/O operations.
        std::copy(std::istream_iterator<int>{iss_numbers},
                  std::istream_iterator<int>{},
                  std::back_inserter(numbers));
 
        //Notify for numbers.
        numbers_promise.set_value();
 
        std::copy_if(std::istreambuf_iterator<char>{iss_letters},
                     std::istreambuf_iterator<char>{},
                     std::back_inserter(letters),
                     ::isalpha);
 
        //Notify for letters.
        letters_promise.set_value();
    });
 
 
    numbers_ready.wait();
 
    std::sort(numbers.begin(), numbers.end());
 
    if (letter_ready.wait_for(std::chrono::seconds(1)) ==
            std::future_status::timeout)
    {
        //output the numbers while letters are being obtained.
        for (int num : numbers) std::cout << num << ' ';
        numbers.clear(); //Numbers were already printed.
    }
 
    letter_ready.wait();
    std::sort(letters.begin(), letters.end());
 
    //If numbers were already printed, it does nothing.
    for (int num : numbers) std::cout << num << ' ';
    std::cout << '\n';
 
    for (char let : letters) std::cout << let << ' ';
    std::cout << '\n';
 
    value_reader.join();
}

```
