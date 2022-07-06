# allocate an array of objects at once.
two ways:
1. The language defines a second kind of new expression that allocates and initializes an array of objects. 
2. The library includes a template class named allocator that lets us separate allocation from initialization.


## new and array
```c++
typedef int arrT[42]; // arrT names the type array of 42 int s
int *p = new arrT; // allocates an array of 42 int s; p points to the first one
// the above code is the same as following
int *p = new int[42];


```
When we use new to allocate an array, we do not get an object with an array type. Instead, we get a pointer to the element type of the array.

### Initializing an Array of Dynamically Allocated Objects
```c++
int *pia = new int[10]; // block of ten uninitialized int s
int *pia2 = new int[10](); // block of ten int s value initialized to 0
string *psa = new string[10]; // block of ten empty string s
string *psa2 = new string[10](); // block of ten empty string s

// block of ten int s each initialized from the corresponding initializer
int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};
// block of ten string s; the first four are initialized from the given initializers
// remaining elements are value initialized
string *psa3 = new string[10]{"a", "an", "the", string(3,’x’)};
```
Although we can use empty parentheses to value initialize the elements of an array, we cannot supply an element initializer inside the parentheses. The fact that
we cannot supply an initial value inside the parentheses means that we cannot use auto to allocate an array.
but we can use auto to allocate a class object like this 
```c++
auto p1 = new auto(Obj) // p points to an object of the type of obj // that object is initialized from obj
auto p2 = new auto{a,b,c}; // error: must use parentheses for the initializer
```

### initialize an array of size 0
```c++
char arr[0]; // error: cannot define a zero-length array
char *cp = new char[0]; // ok: but cp can’t be dereferenced
```


### freeing the array
```c++
delete p;// p must point to a dynamically allocated object or be null
delete [] pa; // pa must point to a dynamically allocated array or be null
typedef int arrT[42];// arrT names the type array of 42 int s
int *p = new arrT; // allocates an array of 42 int s; p points to the first one
delete [] p;// brackets are necessary because we allocated an array

```

### smart pointers and dynamic arrays
```c++
// the unique pointer
// up points to an array of ten uninitialized int s
unique_ptr<int[]> up(new int[10]);
up.release();
// automatically uses delete[] to destroy its pointer

unique_ptr<T[]> u  //u can point to a dynamically allocated array of type T.
unique_ptr<T[]> u(p) //u points to the dynamically allocated array to which the built-in pointer p points. p must be convertible to T* (§ 4.11.2, p. 161).
u[i]  //Returns the object at position i in the array that u owns. u must point to an array.


// if we want to use shared_ptr to point to a dynamically allocated array, we must provide our own deleter
// to use a shared_ptr we must supply a deleter
shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; });
sp.reset(); // uses the lambda we supplied that uses delete[] to free the array

// shared_ptr s don’t have subscript operator and don’t support pointer arithmetic
for (size_t i = 0; i != 10; ++i)
*(sp.get() + i) = i; // use get to get a built-in pointer
```

## The allocator Class
The library allocator class, which is defined in the memory header, lets us separate allocation from construction.
### why do we need the allocator 
1. sometimes we will create objects that we do not need
2. those objects that we assign value to are assigned twice, first is in the default initialization, second is the assignment
3. classes that do not have default constructors cannot be dynamically allocated as an array

```c++
// common operation of allocator class
allocator<string> alloc;
// object that can allocate string s
auto const p = alloc.allocate(n); // allocate n unconstructed string s

auto q = p; // q will point to one past the last constructed element
alloc.construct(q++); // *q is the empty string
alloc.construct(q++, 10, ’c’); // *q is cccccccccc
alloc.construct(q++, "hi"); // *q is hi!

cout << *p << endl;// ok: uses the string output operator
cout << *q << endl;// disaster: q points to unconstructed memory!
//When we’re finished using the objects, we must destroy the elements we con-
//structed, which we do by calling destroy on each constructed element.
while (q != p)
    alloc.destroy(--q); // free the string s we actually allocated

alloc.deallocate(p, n);// Deallocates memory that held n objects of type T starting at the address in the T* pointer p; p must be a pointer previously
                       // returned by allocate, and n must be the size requested when p
                       //was created. The user must run destroy on any objects that
                       //were constructed in this memory before calling deallocator
```