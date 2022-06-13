# smart pointers
To make using dynamic objects safer, the library
defines two smart pointer types that manage dynamically allocated
objects. Smart pointers ensure that the objects to which they point
are automatically freed when it is appropriate to do so.

## common operations for both shared_ptr and unique_ptr
```c++

std::shared_ptr<T> sp; 
std::unique_ptr<T> up; // both sp and up can point to the object of type T, which are set to null currently

if(p) statement; // use sp as a condition, which is true if sp points to an object
*p; // dereference sp to get the object that is pointed by sp

p->member; // access the member of object pointed by p
(*p).member;

p.get(); // returns the pointer in p

std::swap(p,q); // swap the objects pointed by p and q
p.swap(q); 
```

## things to keep in mind, use smart pointer properly
- Don’t use the same built-in pointer value to initialize (or reset) more than one smart pointer.
- Don’t delete the pointer returned from get().
- Don’t use get() to initialize or reset another smart pointer.
- If you use a pointer returned by get(), remember that the pointer will become
invalid when the last corresponding smart pointer goes away.
- If you use a smart pointer to manage a resource other than memory allocated by
new, remember to pass a deleter

## shared_ptr
```c++
shared_ptr<string> p1; // shared_ptr that can point at a string
shared_ptr<list<int>> p2; // shared_ptr that can point at a list of ints
// if p1 is not null, check whether it’s the empty string
if (p1 && p1->empty())
*p1 = "hi"; // if so, dereference p1 to assign a new value to that string

// shared_ptr that points to an int with value 42
shared_ptr<int> p3 = make_shared<int>(42);
// p4 points to a string with value 9999999999
shared_ptr<string> p4 = make_shared<string>(10, ’9’);
// p5 points to an int that is value initialized (§ 3.3.1 (p. 98)) to 0
shared_ptr<int> p5 = make_shared<int>();

// p6 points to a dynamically allocated, empty vector<string>
auto p6 = make_shared<vector<string>>();
```


### copying and assigning

```c++
auto p = std::make_shared<int>(42); // object to which p points has one user
auto q(p); // p and q point to the same object
// object to which p and q point has two users
auto r = std::make_shared<int>(42); // int to which r points has one user
r = q; // assign to r, making it point to a different address
// increase the use count for the object to which q points
// reduce the use count of the object to which r had pointed
// the object r had pointed to has no users; that object is automatically freed
```
### Operations Specific to shared_ptr

```c++
std::make_shared<T>(args) //Returns a shared_ptr pointing to a dynamically allocated object of type T. Uses args to initialize that object.
shared_ptr<T> p(q) //p is a copy of the shared_ptr q; increments the count in q. The pointer in q must be convertible to T* (§ 4.11.2, p. 161).
p=q //p and q are shared_ptrs holding pointers that can be converted to one another. Decrements p’s reference count and increments q’s count; deletes p’s existing memory if p’s count goes to 0.
p.unique() //Returns true if p.use_count() is one; false otherwise.
p.use_count() //Returns the number of objects sharing with p; may be a slow operation, intended primarily for debugging purposes.

//Other Ways to Define and Change shared_ptrs
shared_ptr<T> p(q) //p manages the object to which the built-in pointer q points; q must point to memory allocated by new and must be convertible to T* .
shared_ptr<T> p(u)   //p assumes ownership from the unique_ptr u; makes u null.
shared_ptr<T> p(q, d) // p assumes ownership for the object to which the built-in pointer q points. q must be convertible to T* (§ 4.11.2, p. 161). p will use the callable object d (§ 10.3.2, p. 388) in place of delete to free q.
shared_ptr<T> p(p2, d) // p is a copy of the shared_ptr p2 as described in Table 12.2 except that p uses the callable object d in place of delete.

shared_ptr<T> p(q)
p.reset()
p.reset(q)
p.reset(q, d)
//If p is the only shared_ptr pointing at its object, reset frees p’s existing object. If the optional built-in pointer q is passed,
//makes p point to q, otherwise makes p null. If d is supplied, will call d to free q otherwise uses delete to free q

```

### return the shared_ptr from a function
```c++
// factory returns a shared_ptr pointing to a dynamically allocated object
shared_ptr<Foo> factory(T arg)
{
// process arg as appropriate
// shared_ptr will take care of deleting this memory
return make_shared<Foo>(arg);
}

void use_factory(T arg)
{
shared_ptr<Foo> p = factory(arg);
// use p
} // p goes out of scope; the memory to which p points is automatically freed

shared_ptr<Foo> use_factory(T arg)
{
shared_ptr<Foo> p = factory(arg);
// use p
return p; // reference count is incremented when we return p
} // p goes out of scope; the memory to which p points is not freed

```
### Using shared_ptrs with new
```c++
shared_ptr<int> p1 = new int(1024); // error: must use direct initialization
shared_ptr<int> p2(new int(1024)); // ok: uses direct initialization
// similarly the function cannot return a shared_ptr cannot convert a plain pointer in its return statement
// we must explicitly create the shared_ptr
shared_ptr<int> clone(int p) {
    // ok: explicitly create a shared_ptr<int> from int*
    return shared_ptr<int>(new int(p));
}
```

### Don’t Mix Ordinary Pointers and Smart Pointers . . .
```c++
// ptr is created and initialized when process is called
void process(shared_ptr<int> ptr)
{
    // use ptr
} // ptr goes out of scope and is destroyed

// the correct way to use the process
shared_ptr<int> p(new int(42)); // reference count is 1
process(p); // copying p increments its count; in process the reference count is 2
int i = *p; // ok: reference count is 1

// wrong way: mix built-in pointer with smart pointer
int *x(new int(1024)); // dangerous: x is a plain pointer, not a smart pointer
process(x); // error: cannot convert int* to shared_ptr<int>
process(shared_ptr<int>(x)); // legal, but the memory will be deleted!
int j = *x; // undefined: x is a dangling pointer!

```

### Don’t Use get to Initialize or Assign Another Smart Pointer
```c++
shared_ptr<int> p(new int(42)); // reference count is 1
int *q = p.get(); // ok: but don’t use q in any way that might delete its pointer
{ // new block
    // undefined: two independent shared_ptr s point to the same memory
    shared_ptr<int>(q);
} // block ends, q is destroyed, and the memory to which q points is freed
int foo = *p; // undefined; the memory to which p points was freed
```

### Other shared_ptr Operations

```c++
p = new int(1024);// error: cannot assign a pointer to a shared_ptr
p.reset(new int(1024));// ok: p points to a new object


if (!p.unique())
    p.reset(new string(*p)); // we aren’t alone; allocate a new copy
*p += newVal; // now that we know we’re the only pointer, okay to change this object
```


## Smart Pointers and Exceptions

```c++
void f()
{
    shared_ptr<int> sp(new int(42)); // allocate a new object
    // code that throws an exception that is not caught inside f
}
// shared_ptr freed automatically when the function ends

void f()
{
    int *ip = new int(42);
    // dynamically allocate a new object
    // code that throws an exception that is not caught inside f
    // free the memory before exiting
    delete ip;
}
```

## Using Our Own Deletion Code

```c++
struct destination;
struct connection;
// represents what we are connecting to
// information needed to use the connection
connection connect(destination*); // open the connection
void disconnect(connection);
// close the given connection
void f(destination &d /* other parameters */)
{
    // get a connection ; must remember to close it when done
    connection c = connect(&d);
    // use the connection
    // if we forget to call disconnect before exiting f , there will be no way to close c
}

// this issue can be fixed by providing a deleter function

void end_connection(connection *p) { disconnect(*p); }
void f(destination &d /* other parameters */)
{
connection c = connect(&d);
shared_ptr<connection> p(&c, end_connection);
// use the connection
// when f exits, even if by an exception, the connection will be properly closed
}

```


