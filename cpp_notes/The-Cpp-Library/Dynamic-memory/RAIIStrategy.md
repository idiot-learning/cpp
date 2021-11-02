# RAII strategy
Use a class object to maintain the lifetime of a resources (file or dynamically allocated memory).

Summary:
encapsulate each resource into a class
    - constructor is used for obtaining the resources, exception is thrown if not acquired successfully
    - destructor is used to release the resource, exception is not thrown here
always use the instance of this class to use the resource

## RAII in STL
- `std::string std::vector std::thread`: containers to manage the user-defined resources
- `std::unique_ptr std::shared_ptr`: use the deleter to manage any resources
- `std::lock_guard std::unique_lock std::shared_lock`: class to manage the mutual exclusive units

## example 1 
```c++
class MyInt
{
    int *_p; // pointer to heap data
public:
    MyInt(int *p = NULL) { _p = p; }
    ~MyInt()
    {
        std::cout << "resource " << *_p << " deallocated" << std::endl;
        delete _p;
    }
    int &operator*() { return *_p; } // // overload dereferencing operator
};

int main()
{
    double den[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (size_t i = 0; i < 5; ++i)
    {
        // allocate the resource on the stack
        MyInt en(new int(i));

        // use the resource
        std::cout << *en << "/" << den[i] << " = " << *en / den[i] << std::endl;
    }

    return 0;
}
```
## example 2

```c++
void fun() {}
bool everything_ok() { return true; };
std::mutex g_mutex;
void bad_get_resource()
{
	g_mutex.lock(); // get the mutex
	fun(); // the g_mutex is not released if an exception is encountered
	if (!everything_ok()) return; // early return,mutex is not released
	g_mutex.unlock(); // only after the .unlock , the mutex can be released
}

void good_get_resource()
{
	// lock_guard is a RAII类：g_mutex is initialized after getting the resource
	std::lock_guard<std::mutex> lock_guard(g_mutex);
	fun(); // if an exeption encountered, mutex will be released， because function good_get_resource ends
	// lock_guard will call the destructor to release the resource it owns, here is the g_mutex
	if (!everything_ok()) return; // same as fun()，g_mutex will be released
}

```


## Classes with Resources That Have Dynamic Lifetime
Programs tend to use dynamic memory for one of three purposes:
1. They don’t know how many objects they’ll need
2. They don’t know the precise type of the objects they need
3. They want to share data between several objects

for purpose 3, we have such examples

```c++
vector<string> v1; // empty vector
{ // new scope
vector<string> v2 = {"a", "an", "the"};
v1 = v2; // copies the elements from v2 into v1
} // v2 is destroyed, which destroys the elements in v2
// v1 has three elements, which are copies of the ones originally in v2


Blob<string> b1; // empty Blob
{ // new scope
Blob<string> b2 = {"a", "an", "the"};
b1 = b2; // b1 and b2 share the same elements
} // b2 is destroyed, but the elements in b2 must not be destroyed
// b1 points to the elements originally created in b2
```