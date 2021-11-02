# smartPointers 2 - unique_ptr and weak_ptr

## unique_ptr

```c++
unique_ptr<double> p1; // unique_ptr that can point at a double
unique_ptr<int> p2(new int(42)); // p2 points to int with value 42

//Because a unique_ptr owns the object to which it points, unique_ptr does
//not support ordinary copy or assignment:
unique_ptr<string> p1(new string("Stegosaurus"));
unique_ptr<string> p2(p1); // error: no copy for unique_ptr
unique_ptr<string> p3;
p3 = p2; // error: no assign for unique_ptr

```

### operations that are specific to unique_ptr
```c++
unique_ptr<T> u1 //Null unique_ptrs that can point to objects of type T. u1 will use delete to free its pointer; 
unique_ptr<T, D> u2 //u2 will use a callable object of type D to free its pointer.
unique_ptr<T, D> u(d) // Null unique_ptr that point to objects of type T that uses d,which must be an object of type D in place of delete.
u = nullptr  //Deletes the object to which u points; makes u null.
u.release() //Relinquishes control of the pointer u had held; returns the pointer u had held and makes u null.
u.reset() //Deletes the object to which u points;
u.reset(q) //If the built-in pointer q is supplied, makes u point to that object. Otherwise makes u null.
u.reset(nullptr)

// c++ 14 has introduced the std::make_unique<T>(args)

// transfers ownership from p1 (which points to the string Stegosaurus ) to p2
unique_ptr<string> p2(p1.release()); // release makes p1 null
unique_ptr<string> p3(new string("Trex"));
// transfers ownership from p3 to p2
p2.reset(p3.release()); // reset deletes the memory to which p2 had pointed

p2.release(); // WRONG: p2 won’t free the memory and we’ve lost the pointer
auto p = p2.release(); // ok, but we must remember to delete(p)

}
```

### passing and returing an unique_ptr
```c++
unique_ptr<int> clone(int p) {
// ok: explicitly create a unique_ptr<int> from int*
return unique_ptr<int>(new int(p));
}

unique_ptr<int> clone(int p) {
    unique_ptr<int> ret(new int (p));
    // . . .
    return ret;
}
```

### passing a deleter to the unique_ptr
```c++
// p points to an object of type objT and uses an object of type delT to free that object
// it will call an object named fcn of type delT
unique_ptr<objT, delT> p (new objT, fcn);
void f(destination &d /* other needed parameters */)
{
    connection c = connect(&d); // open the connection
    // when p is destroyed, the connection will be closed
    unique_ptr<connection, decltype(end_connection)*>
    p(&c, end_connection);
    // use the connection
    // when f exits, even if by an exception, the connection will be properly closed
}
```

## weak_ptr

A weak_ptr (Table 12.5) is a smart pointer that does not control the lifetime of the object to which it points. Instead, a weak_ptr points to an object that is managed by a shared_ptr.
```c++
auto p = make_shared<int>(42);
weak_ptr<int> wp(p); // wp weakly shares with p ; use count in p is unchanged
if (shared_ptr<int> np = wp.lock()) { // true if np is not null
// inside the if , np shares its object with p
}
```

### common operation of unique_ptr
```c++
weak_ptr<T> w //Null weak_ptr that can point at objects of type T.
weak_ptr<T> w(sp) //weak_ptr that points to the same object as the shared_ptr sp.
w = p //T must be convertible to the type to which sp points. p can be a shared_ptr or a weak_ptr. After the assignment w shares ownership with p.
w.reset() //Makes w null.
w.use_count() //The number of shared_ptrs that share ownership with w.
w.expired() //Returns true if w.use_count() is zero, false otherwise.
w.lock() //If expired is true, returns a null shared_ptr; otherwise returns a shared_ptr to the object to which w points.

```













