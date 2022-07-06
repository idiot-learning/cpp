#include <iostream>
#include <memory>
#include <mutex>

class SingletonBefore {
   public:
    static SingletonBefore* getInstance() {
        SingletonBefore* temp = pInstance;
        std::atomic_thread_fence(std::memory_order_acq_rel);
        if (temp == nullptr) {
            std::lock_guard<std::mutex> lk(m_muex);
            if (temp == nullptr) {
                temp = new SingletonBefore();
                std::atomic_thread_fence(std::memory_order_acq_rel);
                pInstance = temp;
            }
        }
        return pInstance;
    }
    SingletonBefore(SingletonBefore&) = delete;
    SingletonBefore operator=(const SingletonBefore& singleton) = delete;

   private:
    SingletonBefore() = default;
    static SingletonBefore* pInstance;
    static std::mutex m_muex;
};

SingletonBefore* SingletonBefore::pInstance = nullptr;

// c++11 之后的懒汉版本单例
class Singleton {
   public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    Singleton(Singleton&) = delete;
    Singleton& operator=(Singleton& single) = delete;

   private:
    Singleton() = default;
};
