#include <iostream>
#include <thread>
#include <mutex>
 
std::mutex mutex1, mutex2;
 
void ThreadA()
{
    // Creates deadlock problem
    mutex2.lock();
    std::cout << "Thread A mutex2 lock" << std::endl;
    std::cout << "Thread A" << std::endl;
    mutex1.lock();
    std::cout << "Thread A mutex1 lock" << std::endl;
    mutex2.unlock();
    
    std::cout << "Thread A mutex2 unlock" << std::endl;
    mutex1.unlock();
    std::cout << "Thread A mutex1 unlock" << std::endl;
}
 
void ThreadB()
{
    // Creates deadlock problem
    mutex1.lock();
    std::cout << "Thread B mutex1 lock" << std::endl;
    mutex2.lock();
    std::cout << "Thread B mutex2 lock" << std::endl;
    mutex1.unlock();
    std::cout << "Thread B mutex1 unlock" << std::endl;
    mutex2.unlock();
    std::cout << "Thread B mutex2 unlock" << std::endl;
}
 
void ExecuteThreads()
{
    std::thread t1( ThreadA );
    std::thread t2( ThreadB );
 
    t1.join();
    t2.join();
 
    std::cout << "Finished" << std::endl;
}
 
int main()
{
    ExecuteThreads();
 
    return 0;
}