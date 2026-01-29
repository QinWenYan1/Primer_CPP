# 📘 12.2 动态数组 (Dynamic Arrays)

> 来源说明：C++ Primer 12.2 | 本节涵盖：如何分配、初始化、管理和释放动态数组，以及如何使用allocator类进行更灵活的内存管理。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 动态数组的必要性与最佳实践*](#id1)
* [*知识点2: new与数组的分配*](#id2)
* [*知识点3: 分配数组得到的是指向元素类型的指针*](#id3)
* [*知识点4: 动态分配数组的初始化*](#id4)
* [*知识点5: 动态分配空数组的合法性*](#id5)
* [*知识点6: 释放动态数组*](#id6)
* [*知识点7: 智能指针与动态数组*](#id7)
* [*知识点8: allocator类概述*](#id8)
* [*知识点9: allocator的基本操作*](#id9)
* [*知识点10: 拷贝和填充未初始化内存的算法*](#id10)

---

<a id="id1"></a>
## ✅ 知识点1: 动态数组的必要性与最佳实践

**理论**
* **核心主旨总结**：
    * `new`和`delete`一次只能分配/释放一个对象。
    * 为了支持需要一次性为多个对象分配连续内存的场景（如`vector`、`string`重新分配时），C++语言和库提供了两种分配对象数组的方式：
        * `new`的数组形式，以及`allocator`模板类。
    * `allocator`类可以将内存<b>分配(allocation)</b>与对象<b>构造(construction)</b>分离，通常能提供更好的性能和更灵活的内存管理。


**注意点**
* ⚠️ **警告注意**：明确警告在掌握足够知识（第13章）前，避免在类中使用动态数组。
* 💡 **理解技巧**：理解`vector`等容器内部就是使用动态数组的思想来管理元素的，但为我们封装了所有复杂的内存管理细节。
* 💡 **最佳实践**：
    * **大多数应用程序应该使用库容器（如`vector`），而不是动态分配的数组**。
    * 使用容器更容易、更不容易出现内存管理错误，并且可能提供更好的性能。
    * 使用容器的类可以使用默认的拷贝、赋值和析构操作。而分配动态数组的类必须自定义这些操作来管理关联的内存。

---

<a id="id2"></a>
## ✅ 知识点2: new与数组的分配

**理论**
* **核心主旨总结**：
    * 通过在类型名后跟一对**方括号**，并在括号内指定要分配的**对象数量**，可以让`new`分配一个对象数组。
    * `new`会分配请求数量的对象，并（假设分配成功）返回指向第一个对象的指针。
* **关键要点**：
    * 方括号内的<b>大小(size)</b>必须是**整数类型**，但**不必是常量**。
    * 也可以使用<b>类型别名(type alias)</b>来表示数组类型，此时在`new`中可以省略方括号。但编译器仍会按`new[]`的方式执行。

**教材示例代码**
```cpp
// call get_size to determine how many ints to allocate
int *pia = new int[get_size()]; // pia points to the first of these ints

typedef int arrT[42]; // arrT names the type array of 42 ints
int *p = new arrT;    // allocates an array of 42 ints; p points to the first one
// 编译器实际执行：int *p = new int[42];
```

---

<a id="id3"></a>
## ✅ 知识点3: 分配数组得到的是指向元素类型的指针

**理论**
* **核心主旨总结**：
    * 使用`new T[]`分配内存通常被称为“动态数组”，但这有些误导。
    * **我们得到的并不是一个数组类型的对象，而是一个指向数组元素类型的指针**。
    * 即使使用数组类型别名，`new`也不会分配数组类型的对象。
* **关键后果**：
    * 因为分配的内存没有数组类型，所以我们**不能**在动态数组上调用`begin()`或`end()`。这些函数需要使用数组维度（数组类型的一部分）。
    * 同样原因，我们也**不能**使用<b>范围for循环(range for)</b>来处理所谓的动态数组的元素。

**注意点**
* 💡 **理解技巧**：
    * 这是理解动态数组行为的关键点。`new int[10]`返回的是`int*`，而不是`int[10]`。
    * 这使得动态数组在许多方面与普通数组不同。
    * 所谓的“动态数组”本质上只是一个指向内存的指针，虽然支持下标运算，但它并**不具备**原生数组那种包含**长度信息**的“数组类型”身份。

---

<a id="id4"></a>
## ✅ 知识点4: 动态分配数组的初始化

**理论**
* **核心主旨总结**：
    * 默认情况下，由`new`分配的对象（无论是单个对象还是数组）都是**默认初始化(default-initialized)**。
    * 可以通过在大小后跟一对空括号来对数组元素进行**值初始化(value-initialize)**。
    * 在新标准下，还可以提供初始化器列表。
* **关键要点**：
    * 如果初始化器数量少于元素数量，剩余元素将被值初始化。
    * 如果初始化器数量多于给定大小，则`new`表达式**失败**，**不分配存储**，并抛出一个类型为`bad_array_new_length`的异常。该类型定义在头文件`<new>`中。
    * **不能**在用于值初始化的空括号内提供元素初始化器，这意味着**不能使用`auto`来分配数组**。


**教材示例代码**
```cpp
int *pia = new int[10];          // block of ten uninitialized ints
int *pia2 = new int[10]();       // block of ten ints value initialized to 0
string *psa = new string[10];    // block of ten empty strings
string *psa2 = new string[10](); // block of ten empty strings

// 新标准：使用初始化器列表
int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};
string *psa3 = new string[10]{"a", "an", "the", string(3,'x')};
// 前四个用给定初始化器初始化，剩余元素值初始化
auto p = new auto[10];   // 错误：编译器不知道该推导成什么类型
auto p = new auto[10](); // 错误：虽然有括号，但括号内必须为空，编译器还是没法猜
auto p = new auto(42); // 正确：编译器看到 42，知道 auto 应该是 int，p 是 int*
```

---

<a id="id5"></a>
## ✅ 知识点5: 动态分配空数组的合法性

**理论**
* **核心主旨总结**：
    * 允许使用`new`分配大小为0的数组，这是合法的，尽管不能定义长度为0的数组变量。
* **关键行为**：
    * 当用`new`分配大小为0的数组时，`new`返回一个有效的、非零的指针。该指针保证与`new`返回的任何其他指针都不同。
    * 该指针的作用类似于零元素数组的**尾后指针(off-the-end pointer)** 或迭代器。
    * 可以对该指针进行比较、加减零以及自身相减（得到0）。
    * **该指针不能被解引用(dereferenced)**，因为它不指向任何元素。


**教材示例代码**
```cpp
char arr[0];           // 错误: 无法定义一个length为0的array
char *cp = new char[0]; // ok: 但是无法解引用

size_t n = get_size(); 
int* p = new int[n];   // 可行即使n为0
for (int* q = p; q != p + n; ++q) { /* process the array */ } // 循环体直接被跳过
```


---

<a id="id6"></a>
## ✅ 知识点6: 释放动态数组

**理论**
* **核心主旨总结**：
    * 为了释放动态数组，必须使用`delete`的一种特殊形式，即包含一对方括号：`delete [] pa;`。
    * 数组元素以逆序销毁（从后往前）。
* **关键要点**：
    * 空方括号对是**必不可少的**，它告诉编译器该指针指向一个**对象数组**的第一个元素。
    * 即使使用类型别名分配数组时省略了`new`后的方括号，`delete`时也必须使用方括号。


**教材示例代码**
```cpp
delete p;   // p must point to a dynamically allocated object or be null
delete [] pa; // pa must point to a dynamically allocated array or be null

typedef int arrT[42];
int *p = new arrT; // allocates an array of 42 ints
delete [] p;       // brackets are necessary because we allocated an array
```
**注意点**：
   * ⚠️ 如果对指向数组的指针`delete`时省略了方括号，或者对指向单个对象的指针`delete`时使用了方括号，其**行为是未定义的(undefined behavior)**。
   * ⚠️ 编译器不太可能发出警告，但程序可能在运行时出错。

---

<a id="id7"></a>
## ✅ 知识点7: 智能指针与动态数组

**理论**
* **核心主旨总结**：
    * 标准库提供了可以管理由`new`分配的数组的`unique_ptr`版本。
    * `shared_ptr`不直接支持管理动态数组，如果要用，必须提供自定义的**删除器(deleter)**。
* **关键要点**：
    * **`unique_ptr`管理数组**：
        * 类型说明符中`<int[]>`表示`unique_ptr`指向一个ints数组
        * 指向数组的`unique_ptr`**不支持**点(`.`)和箭头(`->`)成员访问运算符，但支持**下标运算符(subscript operator) `[]`** 来访问数组元素。
        * 当其释放指针时，会自动使用`delete[]`。
    * **`shared_ptr`管理数组**：
        * **不直接支持**。必须提供自定义删除器（例如一个使用`delete[]`的lambda表达式）。
        * 不传入的话会直接调用`delete`而不是`delete[]`，从而造成问题
        * `shared_ptr`没有下标运算符，也不支持指针算术，因此要访问元素，必须使用`.get()`获取内置指针，然后按常规方式使用。
* **指向数组的`unique_ptr`的特殊操作**

    | 操作 | 功能描述 |
    | --- | --- |
    | **`unique_ptr<T[]> u`** | 声明一个空的智能指针 `u`，它可以指向一个类型为 `T` 的动态分配数组。 |
    | **`unique_ptr<T[]> u(p)`** | 让 `u` 指向内置指针 `p` 所指向的动态数组。`p` 必须能转换成 `T*` 类型。 |
    | **`u[i]`** | **核心操作**：返回数组中位置 `i` 处的对象。这让你像使用普通数组一样使用智能指针。 |

---

**教材示例代码**
```cpp
// unique_ptr 管理动态数组
unique_ptr<int[]> up(new int[10]); // up points to an array of ten uninitialized ints
for (size_t i = 0; i != 10; ++i) {
    up[i] = i; // use subscript operator to access elements
}
up.release(); // automatically uses delete[] to destroy its pointer

// shared_ptr 管理动态数组（需自定义删除器）
shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; });
// 访问元素：需通过 .get() 获取内置指针
for (size_t i = 0; i != 10; ++i) {
    *(sp.get() + i) = i; // use get to get a built-in pointer, then use pointer arithmetic
}
sp.reset(); // uses the lambda we supplied that uses delete[] to free the array
```

**注意点**
* ⚠️ **警告注意**：如果使用`shared_ptr`管理动态数组但未提供使用`delete[]`的删除器，代码将是未定义的，因为默认的`delete`不匹配数组的分配方式。

---

<a id="id8"></a>
## ✅ 知识点8: `allocator`类概述

**理论**
* **核心主旨总结**：
    * `new`将内存分配与对象构造**结合在一起**，`delete`将对象析构与内存释放**结合在一起**。（这也是与`malloc`, `free`的区别）
    * 这种结合有时不够灵活或效率低下（例如，可能创建从未使用的对象，或者对没有默认构造函数的类无法动态分配数组）。
    * `allocator`类允许我们将<b>内存分配(allocation)</b>与<b>对象构造(construction)</b>分离开来。
* **关键要点**：
    * `allocator`是一个**模板类(template class)**，定义在`<memory>`头文件中。
    * 它提供**类型感知的(type-aware)**、原始的、未构造的内存分配。
    * 分离分配和构造允许我们分配大块内存，只在**真正需要创建对象时才支付对象构造的开销**。


**教材示例代码**
```cpp
string *const p = new string[n]; // 构造n个空字符串，可能浪费
string s;
string *q = p;
while (cin >> s && q != p + n)
    *q++ = s; // 覆盖之前初始化的值，元素被写了两次
// ... 使用数组
delete[] p;
```

---

<a id="id9"></a>
## ✅ 知识点9: `allocator`的基本操作

**理论**
* **核心主旨总结**：
    * `allocator`对象分配的内存是**未构造的(unconstructed)**。
    * 我们通过在该内存中构造对象来使用它。
    * 使用完毕后，**必须**先销毁构造的对象，然后才能释放内存。
* **关键操作**：
    1. `allocator<T> a`: 定义了一个名为a的`allocator`用于分配对象`T`的内存。
    2.  `allocate(n)`：分配能保存`n`个类型为`T`的对象的原始、未构造内存。
    3.  `construct(p, args)`：在指针`p`指向的原始内存中，使用参数`args`在未构造内存上构造一个类型为`T`的对象。
    4.  `destroy(p)`：对指针`p`指向的对象运行析构函数，变回到未构造内存
        * 方便复用与销毁。
    5.  `deallocate(p, n)`：释放从指针`p`开始的内存，该内存必须是由`allocate`分配的，且大小参数`n`必须与分配时一致。
    * `deallocate`前，一定要先`destroy`



**教材示例代码**
```cpp
allocator<string> alloc;            // object that can allocate strings
auto const p = alloc.allocate(n);   // allocate n unconstructed strings

auto q = p; // q will point to one past the last constructed element
alloc.construct(q++);               // *q is the empty string
alloc.construct(q++, 10, 'c');      // *q is cccccccccc
alloc.construct(q++, "hi");         // *q is hi!

// 错误示例：使用未构造的内存
// cout << *q << endl; // disaster: q points to unconstructed memory!

// 销毁已构造的元素
while (q != p)
    alloc.destroy(--q); // 逆序销毁

// 释放内存
alloc.deallocate(p, n);
```

* **注意点**：
    * ⚠️ **必须构造对象后才能使用`allocate`返回的内存**，以其他方式使用未构造的内存是未定义行为。
    * ⚠️ **只能销毁`destroy()`实际已构造的元素**。
    * 传递给`deallocate`的指针不能是`nullptr`，且大小必须匹配。

---

<a id="id10"></a>
## ✅ 知识点10: 拷贝和填充未初始化内存的算法

**理论**
* **核心主旨总结**：
    * 标准库在`<memory>`头文件中定义了几个算法，作为`allocator`类的补充，用于在未初始化的内存中构造对象
    * 这些算法是在<b>构造(elements)</b>元素，而不是给它们赋值。
* **关键算法**：
    * `uninitialized_copy(b, e, b2)`：将输入迭代器范围`[b, e)`中的元素拷贝到由迭代器`b2`指向的未构造原始内存中。`b2`指向的内存必须足够大。返回（递增后的）目的位置迭代器。
    * `uninitialized_copy_n(b, n, b2)`：从迭代器`b`开始拷贝`n`个元素到从`b2`开始的原始内存。
    * `uninitialized_fill(b, e, t)`：在迭代器范围`[b, e)`指定的原始内存中构造对象，每个对象都是`t`的副本。
    * `uninitialized_fill_n(b, n, t)`：从迭代器`b`开始，构造`n`个对象，每个对象都是`t`的副本。


**教材示例代码**
```cpp
vector<int> vi = {0,1,2,3,4};
allocator<int> alloc;
// allocate twice as many elements as vi holds
auto p = alloc.allocate(vi.size() * 2);
// construct elements starting at p as copies of elements in vi
auto q = uninitialized_copy(vi.begin(), vi.end(), p);
// initialize the remaining elements to 42
uninitialized_fill_n(q, vi.size(), 42);
```

**注意点**
* 🔄 **知识关联**： 
* `uninitialized_copy`类似于`copy`算法，但它在目的地构造对象。
* `uninitialized_fill_n`类似于`fill_n`算法，但它是在原始内存中构造对象。
* 并且目标迭代器指向的一定要是未构造的内存

---

## 🔑 核心要点总结
1.  **优先使用容器**：大多数情况下，应使用`vector`等标准库容器，而非手动管理动态数组，因其更安全、高效。
2.  **`new[]`返回指针，而非数组**：`new T[n]`返回的是`T*`，不是数组类型，因此不能对其使用`begin`/`end`或范围`for`。
3.  **必须配套使用`delete[]`**：释放动态数组必须使用`delete []`，否则行为未定义。即使使用类型别名，`delete`时方括号也不能少。
4.  **智能指针的区别**：`unique_ptr`通过`unique_ptr<T[]>`直接支持动态数组管理；`shared_ptr`需要自定义使用`delete[]`的删除器。
5.  **`allocator`分离分配与构造**：当需要更精细地控制内存时（如提前分配大块内存、处理无默认构造函数的类），可使用`allocator`类及配套算法（如`uninitialized_copy`）来分离内存分配和对象构造/销毁。

## 📌 考试速记版
* **`new type[n]`**：分配动态数组，返回`type*`。
* **初始化**：`new int[10]`（默认初始化），`new int[10]()`（值初始化），`new int[10]{...}`（列表初始化）。
* **`delete[] ptr`**：释放动态数组，必须带`[]`。
* **空数组**：`new int[0]`合法，返回唯一指针，可像尾后迭代器一样使用，但**不能解引用**。
* **`unique_ptr<T[]>`**：管理动态数组，支持`[]`，不支持`.`/`->`。
* **`shared_ptr`管理数组**：需提供自定义删除器`[](T* p){ delete[] p; }`，访问需用`.get()`获取原始指针。
* **`allocator<T>`**：`allocate`（分配）、`construct`（构造）、`destroy`（析构）、`deallocate`（释放）。搭配`uninitialized_copy`/`uninitialized_fill_n`使用。

**记忆口诀**：容器优先效率高，new返指针非数组，配套delete不能少，智能指针分工明（unique直接管，shared要定删），allocator分构造，精细管理内存好。