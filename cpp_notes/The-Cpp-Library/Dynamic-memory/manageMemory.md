# Using new to Dynamically Allocate and Initialize Object

```c++
int *pi = new int; // pi points to a dynamically allocated,
// unnamed, uninitialized int

string *ps = new string; // initialized to empty string
int *pi = new int; // pi points to an uninitialized int

int *pi = new int(1024); // object to which pi points has value 1024
string *ps = new string(10, ’9’); // *ps is "9999999999"
// vector with ten elements with values from 0 to 9
vector<int> *pv = new vector<int>{0,1,2,3,4,5,6,7,8,9};

string *ps1 = new string; // default initialized to the empty string
string *ps = new string(); // value initialized to the empty string
int *pi1 = new int; // default initialized; *pi1 is undefined
int *pi2 = new int(); // value initialized to 0; *pi2 is 0

auto p1 = new auto(obj); // p points to an object of the type of obj
// that object is initialized from obj

// The type of p1 is a pointer to the auto-deduced type of obj. If obj is an int,
// then p1 is int*; if obj is a string, then p1 is a string*; and so on. The newly
// allocated object is initialized from the value of obj.

auto p2 = new auto{a,b,c}; // error: must use parentheses for the initializer
```

# Dynamically Allocated const Objects
```c++
// allocate and initialize a const int
const int *pci = new const int(1024);
// allocate a default-initialized const empty string
const string *pcs = new const string;

// if allocation fails, new returns a null pointer
int *p1 = new int; // if allocation fails, new throws std::bad_alloc
int *p2 = new (nothrow) int; // if allocation fails, new returns a null pointer


//Pointer Values and delete
int i, *pi1 = &i, *pi2 = nullptr;
double *pd = new double(33), *pd2 = pd;
delete i; // error: i is not a pointer
delete pi1; // undefined: pi1 refers to a local
delete pd; // ok
delete pd2; // undefined: the memory pointed to by pd2 was already freed
delete pi2; // ok: it is always ok to delete a null pointer

```

# Dynamically Allocated Objects Exist until They Are Freed
As we saw in § 12.1.1 (p. 452), memory that is managed through a shared_ptr
is automatically deleted when the last shared_ptr is destroyed. The same is not
true for memory we manage using built-in pointers. A dynamic object managed
through a built-in pointer exists until it is explicitly deleted.

```c++
// factory returns a pointer to a dynamically allocated object
Foo* factory(T arg)
{
// process arg as appropriate
return new Foo(arg); // caller is responsible for deleting this memory
}


void use_factory(T arg)
{
Foo *p = factory(arg);
// use p
delete p; // remember to free the memory now that we no longer need it
}

Foo* use_factory(T arg)
{
Foo *p = factory(arg);
// use p
return p; // caller must delete the memory
}

int *p(new int(42)); // p points to dynamic memory
auto q = p; // p and q point to the same memory
delete p; // invalidates both p and q
p = nullptr; // indicates that p is no longer bound to an object
// while it is very difficult to find q that is also pointed to the memory
```