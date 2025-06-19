# C++

## NameSpaces

Use when organizing utility code, libraries, or modules

```C++
namespace math {
    int add(int a, int b) {
        return a + b;
    }
}

int main() {
    std::cout << math::add(2, 3); // 5
}
```

## Memory Management and Pointers

### Stack vs Heap Allocation

| Feature    | Stack            | Heap                      |
| ---------- | ---------------- | ------------------------- |
| Allocation | Automatic        | Manual (`new` / `delete`) |
| Scope      | Function-limited | Until explicitly freed    |
| Speed      | Fast             | Slower                    |
| Example    | `int a = 10;`    | `int* p = new int(10);`   |

#### Mistakes to watch out

| Mistake                 | What Happens           |
| ----------------------- | ---------------------- |
| Forgetting `delete`     | Memory leak            |
| Double `delete`         | Undefined behavior     |
| Using freed memory      | Crash or garbage value |
| Dereferencing `nullptr` | Crash                  |

#### Pointer basics

```c++
#include <iostream>
using namespace std;

int main() {

    // -- Pointers
    // - Pointers hold the memory address of another variable
    int a = 10;
    int *b = &a;
    cout << "Value => a = " << a << endl;
    cout << "Pointer => b = " << b << endl;
    cout << "Address => &a = " << &a << endl;
    cout << "Dereferencing => *b = " << *b << endl;
    int double_a = *b * 2;
    cout << "Value => double_a = " << double_a << endl;

    // -- Heap Memory
    int* c = new int(50); // - Allocate memory
    cout << "Value => c = " << *c << endl;

    delete c; // - Manually free up memory
    c = nullptr; // - Avoid dangling pointers
 }
```

#### Heap Arrays

```c++
// -- Heap Array
    int* arr = new int[10]; //- Array of length 10
    arr[0] = 20; //- access/set array index 0
    *(arr +1) = 30; //- array set value of index 1 to 30
    delete[] arr; //- free up memory
    arr = nullptr;

    int size = 10;
    // cout << "Enter size of array: ";
    // cin >> size;
    // cout << "Size => size = " << size << endl;
    int* arr2 = new int[size];
    cout<< "Array Elements - [";
    for (int i = 0; i < size; i++) {
        *(arr2 + i) = i * i;
        cout << *(arr2 + i) << ",";
    }
    cout << "]" << endl;
    delete[] arr2;
    arr2 = nullptr;
```

#### Passing Array to functions

- Arrays decay to pointers when passed to functions
- Modifying array i inside the function changes the original array

```c++
void fillSquares(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * i;
    }
}

void printArray(int* arr, int size) {
    cout << "Array: [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i != size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// -- calling functions
    int * arr3 = new int[size];
    fillSquares(arr3, size);
    printArray(arr3, size);
    delete[] arr3;
    arr3 = nullptr;

    return 0;
```

## Classes

```c++
#include <iostream>

using namespace std;

class DynamicArray {
private:
    int *data;
    int size;
public:
    //-- constructor
    DynamicArray(int s) {
        size = s;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    //-- destructor
    ~DynamicArray() {
        delete[] data; //free heap memory
    }

    //set value
    void set(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    int get(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1; // -error case
    }

    // Print array
    void print() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // Get array size
    int getSize() const {
        return size;
    }
};

int main() {
    int n;
    cout << "Enter size of dynamic array: ";
    cin >> n;

    DynamicArray arr(n);  // stack-allocated object, but internally uses heap

    for (int i = 0; i < arr.getSize(); i++) {
        arr.set(i, i * 5);
    }

    cout << "Array contents: ";
    arr.print();

    // Destructor is called automatically here (when arr goes out of scope)

    return 0;
}
```

### Copy Constructor, Assignment Operator

Compilers by default do shallow copy

Implement the Rule of Three:

- Copy constructor
- Copy assignment operator
- Destructor

#### Shallow Copy

```C++
// -- b.data will point to the same heap as a.data
DynamicArray a(5);
DynamicArray b = a;
```

#### Copy Constructor and Copy Assignment Operator

```C++
// -- Copy Constructor
DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];  // deep copy
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}

// -- Copy Assignment Operator
DynamicArray& operator=(const DynamicArray& other) {
    if (this == &other) return *this;  // handle self-assignment

    delete[] data;  // free old memory

    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];

    return *this;
}

int main() {
    DynamicArray a(3);
    a.set(0, 11); a.set(1, 22); a.set(2, 33);

    DynamicArray b = a;      // invokes copy constructor
    b.set(0, 99);             // only modifies b

    cout << "Array a: "; a.print();  // Should remain unchanged
    cout << "Array b: "; b.print();

    return 0;
}
```

### Move Semantics

Make your classes faster and safer, especially when dealing with large data structures like vectors, strings, files, etc.

When you return an object from a function or pass it around, C++ often copies it. For large objects with heap memory, copying can be expensive.

Instead of copying, move the internal data — just transfer the pointer ownership!

```c++
//-- noexcept tells the compiler this won't throw — required for optimal performance.
 // 🔥 Move constructor
DynamicArray(DynamicArray&& other) noexcept {
    size = other.size;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
}

// 🔥 Move assignment
DynamicArray& operator=(DynamicArray&& other) noexcept {
    if (this == &other) return *this;
    delete[] data;
    size = other.size;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
    return *this;
}
```

#### Rule of 5

| Function             | When it’s called            | Purpose            |
| -------------------- | --------------------------- | ------------------ |
| **Destructor**           | When object is destroyed    | Free memory        |
| **Copy Constructor**     | `MyClass a = b;`            | Deep copy          |
| **Copy Assignment**     | `a = b;`                    | Deep copy          |
| **Move Constructor** | `MyClass a = std::move(b);` | Transfer ownership |
| **Move Assignment**  | `a = std::move(b);`         | Transfer ownership |

### Operator Overloading

```c++
// 🔹 1. Operator [] for element access
    int& operator[](int index) {
        return data[index];  // no bounds check for performance (like real arrays)
    }

    // 🔹 2. Operator + to add two arrays element-wise
    DynamicArray operator+(const DynamicArray& other) const {
        int minSize = (size < other.size) ? size : other.size;
        DynamicArray result(minSize);
        for (int i = 0; i < minSize; i++) {
            result[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    // 🔹 3. Operator == to compare arrays
    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // 🔹 4. Operator << for printing
    friend ostream& operator<<(ostream& os, const DynamicArray& arr) {
        os << "[";
        for (int i = 0; i < arr.size; i++) {
            os << arr.data[i];
            if (i != arr.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }
```

### Static

Persist data across function calls / share among instances

```C++
void counter() {
    static int count = 0;
    std::cout << ++count << "\n";
}

class MyClass {
public:
    static int count;
};
int MyClass::count = 0;

int main() {
    MyClass::count++;
}
```

### Friend Function

A friend function is not a member of the class, but it is allowed to access the class's private and protected members.

| Feature                      | Member Function          | Friend Function                    |
| ---------------------------- | ------------------------ | ---------------------------------- |
| Belongs to class             | ✅ Yes                    | ❌ No                               |
| Access to private/protected  | ✅ Yes                    | ✅ Yes (via `friend` keyword)       |
| Requires object to be called | ✅ (e.g., `obj.method()`) | ❌ Not required (e.g., `func(obj)`) |
| Uses `this` pointer          | ✅ Yes                    | ❌ No                               |
| Can be a free function       | ❌ No                     | ✅ Yes                              |

```c++
//-- Operator without friend fails

class MyClass {
private:
    int x;

public:
    MyClass(int x): x(x) {}

    ostream& operator<<(ostream& os) const {  // ❌ This won't work
        os << x;
        return os;
    }
};

//-- Correct way of using it
//-- In the case x is a private variable but it can be access by friend function
//-- If the object was just passed to the function, the x would not be accessible
class MyClass {
private:
    int x;

public:
    MyClass(int val) : x(val) {}

    friend ostream& operator<<(ostream& os, const MyClass& obj);
};

ostream& operator<<(ostream& os, const MyClass& obj) {
    os << "Value: " << obj.x;
    return os;
}
```

## Smart Pointers

Smart pointers automate memory management.

### Types of Smart pointers

| Smart Pointer | Ownership Model                        | C++ Version |
| ------------- | -------------------------------------- | ----------- |
| `unique_ptr`  | Sole ownership (like a moving box)     | C++11       |
| `shared_ptr`  | Shared ownership, reference-counted    | C++11       |
| `weak_ptr`    | Non-owning reference to a `shared_ptr` | C++11       |

#### Unique Pointer

| Feature       | Description                           |
| ------------- | ------------------------------------- |
| Auto clean-up | Deletes memory automatically          |
| No copying    | Prevents bugs related to ownership    |
| Safe          | Prevents memory leaks, double deletes |
| Fast          | Zero-overhead abstraction (no GC)     |

```C++
#include <memory> // for unique_ptr

auto p1 = make_unique<int>(100);

//-- Can't be copied only moved
auto p2 = make_unique<int>(200);
// unique_ptr<int> p3 = p2; ❌ Error: copy not allowed
auto p3 = move(p2); // ✅ Transfer ownership
```

```C++
//-- Smart array example, better than previous array class
//- No need for destuction as memory is freed when it goes out of scope
//- No need for deep copy/move as compiler handles it
//- No risk of memory leaks

#include <memory>

class SmartArray {
private:
    unique_ptr<int[]> data;
    int size;

//-- Following is size(s) ... is member initializer list
//- data(make_unique...) creates a new unique_ptr
public:
    SmartArray(int s) : size(s), data(make_unique<int[]>(s)) {
        for (int i = 0; i < size; i++) data[i] = 0;
    }

    int& operator[](int i) {
        return data[i];
    }

    void print() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i != size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};
```

#### Shared Ownership Smart Pointer

Used when multiple parts of your program to share ownership of a resource.

When the last owner goes out of scope, the memory is automatically freed.

```C++
#include <memory>

auto ptr1 = std::make_shared<int>(100);

//-- Both ptr1 and ptr2 point to the same int
std::shared_ptr<int> ptr2 = ptr1; // ✅ Copy allowed
std::cout << *ptr2 << std::endl;

//- Memory is deleted only when the last shared pointer is destroyed

std::cout << ptr1.use_count(); // prints number of shared owners


//-- Complete Example
#include <iostream>
#include <memory>
using namespace std;

class SharedDemo {
public:
    SharedDemo() { cout << "Constructor\n"; }
    ~SharedDemo() { cout << "Destructor\n"; }
    void greet() { cout << "Hello from shared object\n"; }
};

int main() {
    shared_ptr<SharedDemo> a = make_shared<SharedDemo>();
    {
        shared_ptr<SharedDemo> b = a;  // shared ownership
        cout << "Use count inside block: " << a.use_count() << endl;
        b->greet();
    }
    // b is out of scope, but a still exists
    cout << "Use count after block: " << a.use_count() << endl;

    return 0; // Destructor runs here when last owner (a) dies
}
```

#### Non-Owning Reference

weak_ptr does not increase reference count

Use it to observe shared_ptr-owned objects without keeping them alive.

```C++
#include <memory>
weak_ptr<SharedDemo> wptr = a;

if (auto sp = wptr.lock()) {
    sp->greet();  // safe to use
}
```

> `->` is used to access functions from a pointer, similar to `.` is used to access functions if it was a object.

#### Summary of Smart Pointers

| Pointer Type | Ownership | Copies Allowed | Auto Deletes | Ref Count |
| ------------ | --------- | -------------- | ------------ | --------- |
| `unique_ptr` | Sole      | ❌ No           | ✅ Yes        | ❌ No      |
| `shared_ptr` | Shared    | ✅ Yes          | ✅ Yes        | ✅ Yes     |
| `weak_ptr`   | Observer  | ✅ Yes          | ❌ No         | ✅ Yes     |

- `shared_ptr` → When objects are shared in multiple places (e.g., graph nodes, GUI elements, observers).
- `unique_ptr` → Default and best for most cases (RAII).
- `weak_ptr` → Prevent memory leaks in cyclic structures.

## Enums & Enum Class

Use enum class to avoid polluting the global scope. Replace magic numbers with named constants.

```c++
// Traditional
enum Color { RED, GREEN, BLUE };

// Safer (C++11+)
enum class Fruit { Apple, Banana, Mango };

int main() {
    Color c = RED;
    Fruit f = Fruit::Apple;
}
```

## Functions

### Default Arguments for Functions

Avoid writing overloads for simple variations

```C++
void greet(std::string name = "User") {
    std::cout << "Hello, " << name << "!\n";
}

int main() {
    greet();          // Hello, User!
    greet("Adwait");  // Hello, Adwait!
}
```

### Function Overloading

Use when logic is conceptually the same but types differ.

```C++
void print(int x)    { std::cout << "int: " << x << "\n"; }
void print(double x) { std::cout << "double: " << x << "\n"; }

int main() {
    print(5);
    print(3.14);
}
```

### Const Correctness

Prevent accidental modification, enable usage in `const` contexts.

Use for parameters, return values, and member functions

```C++
void print(const std::string& msg) {
    // msg can't be modified
}

class MyData {
    int value;
public:
    int get() const {
        return value;  // Cannot modify value here
    }
};
```

### Inline Functions

Suggest compiler to substitute function body at call site.

Use in headers to avoid multiple definitions.

```C++
inline int square(int x) {
    return x * x;
}
```

### Function Pointers

A function pointer lets you store the address of a function in a variable, pass it as an argument, or call it dynamically — similar to using Runnable or Function objects in Java, but lower-level.

They're the foundation for:

- Callbacks
- Plugin-style architectures
- Event handlers
- C-style APIs

Use function pointers when you need runtime polymorphism but don’t want the overhead of inheritance.

They’re powerful in C-style code, embedded systems, or performance-critical code where templates or virtual functions are too heavy.

```C++
//-- Basic
#include <iostream>

void greet() {
    std::cout << "Hello!\n";
}

void callMe(void (*fptr)()) {
    fptr();  // call the function using pointer
}

int main() {
    void (*myFunc)() = greet;
    callMe(myFunc);  // Prints: Hello!
}

//-- With Parameters
int add(int a, int b) {
    return a + b;
}

int operate(int x, int y, int (*op)(int, int)) {
    return op(x, y);
}

int main() {
    std::cout << operate(3, 4, add);  // 7
}
```

## Structs

In C++, a struct is nearly identical to a class, except:

- Members are public by default
- Used for simple data containers

In contrast to Java, C++ structs can have:

- Constructors
- Member functions
- Inheritance
- Operator overloading

Use struct when:

The type is primarily data-oriented

- You want public by default behavior (like Vector2, Color, Config, etc.)
- You want to model a plain-old-data (POD) layout that works with C APIs

Structs work perfectly for:

- Config containers
- Simple math types (Point, Vec3)
- Lightweight return types (e.g., from parsing functions)

```C++
struct Point {
    int x, y;

    Point(int a, int b) : x(a), y(b) {}

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    Point p(3, 4);
    p.print();  // (3, 4)
}
```

## Template - Write Generic, Reusable Code

Templates allow writting type independent code. Similar to generics in Java.

Both `typename` and `class` mean the same in templates.

```C++
template <typename T>
// or
template <class T>

//- Single Type passed
template <typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

//- Passing Multiple Types
template <typename T, typename U>
void printPair(T a, U b) {
    cout << a << " and " << b << endl;
}
```

### Class Template

```C++
template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {}
    void set(T val) { value = val; }
    T get() const { return value; }
};

//- Usage
Box<int> intBox(100);
cout << intBox.get() << endl;

Box<string> strBox("hello");
cout << strBox.get() << endl;
```

| Feature                | Description                            |
| ---------------------- | -------------------------------------- |
| `template<typename T>` | Defines a generic parameter            |
| Function template      | Reusable function for any type         |
| Class template         | Generic classes like `vector<T>`       |
| Multiple types         | Use `template<typename T, typename U>` |
| With smart pointers    | Combine templates with RAII tools      |

## STL Containers

| Category        | Container Types                      | Use Case Example                     |
| --------------- | ------------------------------------ | ------------------------------------ |
| **Sequence**    | `vector`, `deque`, `list`, `array`   | Store elements in a linear order     |
| **Associative** | `set`, `map`, `multiset`, `multimap` | Fast key-based lookup & organization |
| **Unordered**   | `unordered_set`, `unordered_map`     | Hash table-based fast access         |
| **Adapters**    | `stack`, `queue`, `priority_queue`   | Specialized container behavior       |

### Vectors - Dynamic Array

```C++
#include <vector>

vector<int> nums = {10, 20, 30};

nums.push_back(40);      // Add element
nums[1] = 25;            // Modify element
nums.pop_back();         // Remove last

cout << "Size: " << nums.size() << endl;
cout << "First element: " << nums.front() << endl;
cout << "Last element: " << nums.back() << endl;
```

### map - Sorted Key-Value Pairs

- Like TreeMap in Java
- Keys are unique and sorted
- Fast lookups (logarithmic time)

```C++
#include <map>

map<string, int> ages;
ages["Alice"] = 30;
ages["Bob"] = 25;

for (auto [name, age] : ages) {
    cout << name << ": " << age << endl;
}
```

### set - Sorted Unique Values

```C++
#include <set>

set<int> s;
s.insert(5);
s.insert(3);
s.insert(5); // Ignored

for (int val : s) cout << val << " "; // 3 5
```

### unordered_map & unordered_set

- Based on hash tables (like Java's HashMap)
- Faster than map/set (on average)
- No ordering guarantee

```C++
#include <unordered_map>
unordered_map<string, int> stock;

stock["TSLA"] = 250;
stock["AAPL"] = 180;
```

### Summary

| Container       | Description                       | Java Equivalent |
| --------------- | --------------------------------- | --------------- |
| `vector`        | Dynamic array                     | `ArrayList`     |
| `list`          | Doubly linked list                | `LinkedList`    |
| `map`           | Sorted key-value pairs            | `TreeMap`       |
| `set`           | Sorted unique values              | `TreeSet`       |
| `unordered_map` | Fast hash-based key-value storage | `HashMap`       |
| `stack`         | LIFO (last-in, first-out)         | `Stack`         |
| `queue`         | FIFO (first-in, first-out)        | `Queue`         |

### Iterators

```C++
//-- Range-based for loop (uses iterators under the hood)
for (int val : v) {
    cout << val << " ";
}
```

```C++
vector<int> v = {1, 2, 3, 4, 5};

//-- Use auto unless explicit type is needed
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}

//-- Using explicit type
for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    cout << *it << " "; // dereference to access value
}

//-- Example with map
map<string, int> scores = {{"Alice", 90}, {"Bob", 85}};

for (auto it = scores.begin(); it != scores.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
}
//-- 🔸 it->first is the key
//-- 🔸 it->second is the value
```

## Classes and Headers

| File Type     | Role                                                       |
| ------------- | ---------------------------------------------------------- |
| `.h` / `.hpp` | **Header file** — contains declarations (no real code)     |
| `.cpp`        | **Source file** — contains definitions (actual code logic) |

> `#ifndef` / `#define` / `#endif` is called an include guard — it prevents double inclusion.

```C++
#ifndef POINT_H
#define POINT_H

#endif
```

## CMake

```css
BoxProject/
├── CMakeLists.txt
├── main.cpp
├── Box.h
└── Box.cpp
```

```c++
//-- Box.h
#ifndef BOX_H
#define BOX_H

class Box {
private:
    double length;
    double width;
    double height;

public:
    Box(double l = 1.0, double w = 1.0, double h = 1.0);
    double volume() const;
    void print() const;
};

#endif
```

```c++
//--Box.cpp
#include "Box.h"
#include <iostream>
using namespace std;

Box::Box(double l, double w, double h) : length(l), width(w), height(h) {}

double Box::volume() const {
    return length * width * height;
}

void Box::print() const {
    cout << "Box(" << length << ", " << width << ", " << height << ")" << endl;
}
```

```C++
//-- Main.cpp
#include <iostream>
#include "Box.h"
using namespace std;

int main() {
    Box b1(2.0, 3.5, 4.0);
    b1.print();
    cout << "Volume: " << b1.volume() << endl;

    return 0;
}
```

```txt
cmake_minimum_required(VERSION 3.10)
project(BoxProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(BoxProject main.cpp Box.cpp)
```

Building -

```python
cd BoxProject

mkdir build
cd build

cmake .. # Manages building cleanly and automatically
make # compiles and links the source files

./BoxProject
```

### Using External Libraries with CMake

#### FetchContent

This downloads and builds the library automatically.

#### find_package

For when a library is already installed on your system (via apt, brew, vcpkg, etc.).

#### Manual Linking

You download the library yourself, add the .cpp/.h files to your project, and:

```txt
include_directories(lib_folder)
add_executable(Example main.cpp lib/some.cpp)
```

## Exception Handling

| Concept                    | Java             | C++                                        |
| -------------------------- | ---------------- | ------------------------------------------ |
| All exceptions are objects | ✅ Required       | ✅ Recommended (but can throw anything)     |
| Must catch or declare      | ✅ Yes (`throws`) | ❌ No requirement to catch or declare       |
| Checked exceptions         | ✅ Yes            | ❌ C++ has **only unchecked exceptions**    |
| Catching by reference      | Not relevant     | ✅ Best practice: catch by `const&`         |
| Destructors auto-called    | Yes              | ✅ Yes — this allows **RAII-based cleanup** |

```cpp
#include <iostream>
#include <stdexcept> // std::runtime_error, etc.

int divide(int a, int b) {
    if (b == 0)
        throw std::runtime_error("Division by zero!");
    return a / b;
}

int main() {
    try {
        int result = divide(10, 0);
        std::cout << "Result = " << result << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught error: " << e.what() << "\n";
    }

    std::cout << "Program continues...\n";
    return 0;
}
```

### Custom Exceptions

```c++
class MyCustomError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Something custom went wrong!";
    }
};

//-- Use
throw MyCustomError();
```

> Smart Pointers are much safer during exceptions as they clean up memory in case of any errors or exceptions.

## Multithreading

n C++11 and later, multithreading is part of the standard library via `<thread>` and related headers like `<mutex>`, `<atomic>`, and `<condition_variable>`.

Unlike Java, where you often extend Thread or use Runnable, in C++ you can start any function in a new thread using the `std::thread` class.

### Function in new Thread

```C++
#include <iostream>
#include <thread>

void say_hello() {
    std::cout << "Hello from thread!\n";
}

int main() {
    std::thread t1(say_hello);  // Start new thread
    t1.join();                  // Wait for thread to finish
    std::cout << "Main thread done.\n";
}
```

| Concept       | Description                                         |
| ------------- | --------------------------------------------------- |
| `std::thread` | Launches a new thread                               |
| `.join()`     | Wait for the thread to finish                       |
| `.detach()`   | Run thread independently (you can’t join it later)  |
| Thread-safe?  | C++ assumes nothing is thread-safe unless specified |

| Tool                          | Purpose                        |
| ----------------------------- | ------------------------------ |
| `std::thread`                 | Run code in parallel           |
| `std::mutex`, `lock_guard`    | Protect shared data            |
| `std::atomic<T>`              | Lock-free thread-safe variable |
| `std::condition_variable`     | Wait/notify threads            |
| `std::this_thread::sleep_for` | Delay execution                |

### Threads with Parameters

```C++
void repeat(int n, const std::string& name) {
    for (int i = 0; i < n; ++i)
        std::cout << name << " " << i << "\n";
}

int main() {
    std::thread t1(repeat, 5, "Worker");
    t1.join();
}
```

### Thread Safety - Race Conditions

```C++
//-- No thread safety
int counter = 0;

void increment() {
    for (int i = 0; i < 10000; ++i)
        ++counter;
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Counter: " << counter << "\n"; // Maybe wrong!
}

//-- Fixing with Mutex
#include <mutex>

std::mutex mtx;
int counter = 0;

void safe_increment() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}
```

## Lambda Functions

You can use lambdas wherever you'd use a function pointer, but lambdas are:

- More expressive
- Can capture variables
- Don't pollute the global scope

| Concept              | Syntax/Example                |
| -------------------- | ----------------------------- |
| Basic lambda         | `[](int x) { return x * x; }` |
| Capture by value     | `[=]`                         |
| Capture by reference | `[&]`                         |
| Threaded lambda      | `std::thread t([] { ... });`  |
| Generic lambda       | `[](auto x) { ... }`          |


```C++
//-- Syntax
[ capture ] ( parameters ) -> return_type {
    // function body
}

//-- Basic Example
auto add = [](int a, int b) {
    return a + b;
};

//-- Use in algorithms
std::cout << add(2, 3); // Outputs 5

#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::for_each(nums.begin(), nums.end(), [](int x) {
        std::cout << x * x << " ";
    });
}
```

### Capture Clause

The `[ ]` part is the capture list, which lets the lambda access variables from the surrounding scope.

```C++
//-- Capture by Value
int factor = 2;
auto scale = [=](int x) { return x * factor; };  // Captures by value

//-- Capture by reference
int count = 0;
auto increment = [&]() { ++count; };  // Modifies count
increment();

//-- Mixed Captures
int a = 10, b = 20;
auto f = [=, &b]() { std::cout << a << " " << ++b; };

//-- Generic Lambdas
auto print = [](auto x) {
    std::cout << x << "\n";
};

print(10);     // int
print("hi");   // const char*

//-- Lambda in threads
std::thread t([] {
    std::cout << "Hello from lambda thread\n";
});
t.join();

//-- Lambda with Return Types
auto diff = [](int a, int b) -> double {
    return a - b;
};
```