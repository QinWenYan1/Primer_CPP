# 📘 13.5 管理动态内存的类 (Classes That Manage Dynamic Memory)

> 来源说明：[C++ Primer 5th] 章节 13.5 | 本节涵盖：如何设计一个类似 vector 的类 StrVec，通过自定义分配器(allocator)管理动态内存，并实现拷贝控制成员以正确管理内存。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 需要管理动态内存的类*](#id1)
* [*知识点2: StrVec 类设计*](#id2)
* [*知识点3: StrVec 类定义*](#id3)
* [*知识点4: 默认构造函数*](#id4)
* [*知识点5: size 成员*](#id5)
* [*知识点6: capacity 成员*](#id6)
* [*知识点7: chk_n_allocz 成员*](#id7)
* [*知识点8: begin 和 end 成员*](#id8)
* [*知识点9: 使用 construct —— push_back 实现*](#id9)
* [*知识点10: alloc_n_copy 成员*](#id10)
* [*知识点11: free 成员*](#id11)
* [*知识点12: 拷贝构造函数*](#id12)
* [*知识点13: 析构函数*](#id13)
* [*知识点14: 拷贝赋值运算符*](#id14)
* [*知识点15: 重新分配时移动而非拷贝元素*](#id15)
* [*知识点16: 移动构造函数和 std::move*](#id16)
* [*知识点17: reallocate 成员*](#id17)

---

<a id="id1"></a>
## ✅ 知识点1: 需要管理动态内存的类

**理论**
* **核心主旨总结**：
    * 某些类需要在运行时分配可变大小的存储空间，通常应优先使用标准库容器（如 `vector`）来管理数据。
    * 例如 `StrBlob` 类使用 `vector` 管理底层存储。
    * 但并非所有类都能采用这种策略，**必须自己进行内存分配的类，通常需要定义拷贝控制成员**来正确管理所分配的内存。


**注意点**
* ⚠️ **警告注意**：不要轻易自定义内存管理，容易导致资源泄漏或重复释放。优先使用标准库容器。
* ⚠️ **重点突出**：**如果可以，应优先使用库容器**；只有在必须自定义内存管理时，才需要实现拷贝控制。
---

<a id="id2"></a>
## ✅ 知识点2: `StrVec`类设计

**理论**
* **核心主旨总结**：本节实现一个简化版的 `vector`，它专用于存储 `string`，因此命名为 `StrVec`。设计策略模仿 `vector`：
  - 元素存储在<b>连续内存(contiguous storage)</b>中。
  - 为获得可接受的性能，会<b>预分配(preallocate)</b>多于实际需要的空间。
  - 添加元素时，先检查是否有空闲位置；若有则直接在下一个可用位置构造对象；否则执行**重新分配(reallocation)**：获取新空间、将现有元素移动到新空间、释放旧空间、添加新元素。
* **关键数据结构**：
  - 使用 `allocator<string>` 获取原始内存（未构造）。
  - 三个指针管理内存区域：
    - `elements`：指向第一个元素。
    - `first_free`：指向最后一个实际元素之后的位置。
    - `cap`：指向分配内存末尾之后的位置。
* **四个工具函数**：
  - `alloc_n_copy`：分配空间并拷贝给定范围元素。
  - `free`：销毁已构造元素并释放空间。
  - `chk_n_alloc`：确保至少能添加一个元素，否则调用 `reallocate`。
  - `reallocate`：空间不足时重新分配更大内存。


**注意点**

* 💡 **理解技巧**：将 `StrVec` 的内存管理比作一个动态数组：`elements` 是数组头，`first_free` 是已使用的尾部，`cap` 是容量尾部。

---

<a id="id3"></a>
## ✅ 知识点3: `StrVec`类定义

**理论**
* **核心主旨总结**：`StrVec` 类的定义展示了如何通过三个指针和 `allocator` 实现类似 `vector` 的内存管理策略。类中包含默认构造函数、拷贝控制成员、基本大小/容量查询接口、迭代器接口（指针形式）以及私有工具函数。
   类体定义了它的几个成员：

    - **默认构造函数**：(隐式地) 默认初始化 `alloc`，并(显式地) 将指针初始化为 `nullptr`，表示当前没有元素。

    - **`size` 成员**：返回实际在用的元素数量，等于 `first_free - elements`。

    - **`capacity` 成员**：返回 `StrVec` 能够容纳的元素数量，等于 `cap - elements`。

    - **`chk_n_alloc`**：当没有空间添加新元素时（即 `cap == first_free` 时），会导致 `StrVec` 重新分配内存。

    - **`begin` 和 `end` 成员**：分别返回指向第一个元素（即 `elements`）的指针，以及指向最后一个已构造元素之后位置（即 `first_free`）的指针。

**教材示例代码**
```cpp
// simplified implementation of the memory allocation strategy for a vector-like class
class StrVec {
public:
    StrVec() : // the allocator member is default initialized
        elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&); // copy constructor
    StrVec &operator=(const StrVec&); // copy assignment
    ~StrVec(); // destructor
    void push_back(const std::string&); // copy the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...
private:
    std::allocator<std::string> alloc; // allocates the elements
    // used by the functions that add elements to the StrVec
    void chk_n_alloc()
        { if (size() == capacity()) reallocate(); }
    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free(); // destroy the elements and free the space
    void reallocate(); // get more space and copy the existing elements
    std::string *elements;   // pointer to the first element in the array
    std::string *first_free; // pointer to the first free element in the array
    std::string *cap;        // pointer to one past the end of the array
};
```



---

<a id="id4"></a>
## ✅ 知识点4: 默认构造函数

**理论**
* **核心主旨总结**：默认构造函数**隐式地默认初始化(implicitly default initializes)** `alloc` 成员（调用 `allocator<string>` 的默认构造函数），并**显式初始化(explicitly initializes)** 三个指针为 `nullptr`，表示初始时没有任何元素。

**教材示例代码**  
已在类定义中呈现，此处重复强调：
```cpp
StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
```

---

<a id="id5"></a>
## ✅ 知识点5: `size`成员

**理论**
* **核心主旨总结**：`size` 成员返回**当前实际存储的元素个数**，计算方式为 `first_free - elements`。由于指针减法得到的是两个指针之间对象的数量，因此该差值恰好是已构造元素的数量。

**教材示例代码**
```cpp
size_t size() const { return first_free - elements; }
```

**注意点**
* ⚠️ **警告注意**：仅当 `elements` 和 `first_free` 均指向同一数组中的元素（或尾后位置）时，指针减法才有定义。`StrVec` 的设计保证了这一点。


---

<a id="id6"></a>
## ✅ 知识点6: `capacity` 成员

**理论**
* **核心主旨总结**：`capacity` 成员返回当前分配的内存最多可容纳的元素个数，计算方式为 `cap - elements`。它表示在不重新分配内存的前提下，还可以添加多少元素。

**教材示例代码**
```cpp
size_t capacity() const { return cap - elements; }
```

---

<a id="id7"></a>
## ✅ 知识点7: `chk_n_alloc` 成员

**理论**
* **核心主旨总结**：`chk_n_alloc` 是一个私有工具函数，用于**确保有空间添加至少一个元素**。当 `size() == capacity()`（即内存已满）时，调用 `reallocate()` 获取更多空间。

**教材示例代码**
```cpp
void chk_n_alloc()
    { if (size() == capacity()) reallocate(); }
```

---

<a id="id8"></a>
## ✅ 知识点8:`begin` 和 `end` 成员

**理论**
* **核心主旨总结**：`begin` 返回指向第一个元素的指针（即 `elements`），`end` 返回指向最后一个元素之后位置的指针（即 `first_free`）。它们提供了类似容器的迭代器接口（以原生指针形式）。

**教材示例代码**
```cpp
std::string *begin() const { return elements; }
std::string *end() const { return first_free; }
```



---

<a id="id9"></a>
## ✅ 知识点9: 使用 `construct` —— `push_back` 实现

**理论**
* **核心主旨总结**：`push_back` 函数首先调用 `chk_n_alloc()` 确保有可用空间，然后调用 `alloc.construct` 在 `first_free` 指向的未构造内存中构造一个 `string` 副本。`construct` 的第一个参数是**指向未构造空间的指针**，其余参数用于选择构造函数（此处为 `string` 的拷贝构造函数）。调用后，`first_free` 通过**后置递增(postfix increment)** 移动指向下一个未构造位置。

**教材示例代码**
```cpp
void StrVec::push_back(const string& s)
{
    chk_n_alloc(); // ensure that there is room for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}
```

**注意点**
* ⚠️ **警告注意**：使用 `allocator` 分配的内存是**未构造(unconstructed)**的，必须通过 `construct` 创建对象，否则解引用是未定义行为。
* 💡 **理解技巧**：`first_free++` 既将对象构造在当前位置，又将指针后移，非常紧凑。

---

<a id="id10"></a>
## ✅ 知识点10: `alloc_n_copy` 成员

**理论**
* **核心主旨总结**：
* `alloc_n_copy` 在拷贝或赋值时被调用，它**分配足够容纳给定范围元素的内存**，并将该范围内的元素拷贝到新分配的内存中。
* 它返回一个 `pair<string*, string*>`，`first` 指向新分配内存的起始位置，`second` 指向最后一个构造元素之后的位置（由 `uninitialized_copy` 返回）。

**教材示例代码**
```cpp
pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, uninitialized_copy(b, e, data)};
}
```

**注意点**
* ⚠️ **警告注意**：`uninitialized_copy` 在目的位置构造元素，而不是简单赋值。它返回指向最后一个构造元素之后位置的迭代器（指针）。


---

<a id="id11"></a>
## ✅ 知识点11: `free` 成员

**理论**
* **核心主旨总结**：
    * `free` 负责**销毁已构造的元素**并**释放整个内存空间**。
    * 销毁按<b>逆序(reverse order)</b>进行（从最后一个元素到第一个），通过调用 `alloc.destroy` 逐个执行 `string` 的析构函数。
    * 然后调用 `alloc.deallocate` 释放整块内存。
    * 函数首先检查 `elements` 非空，避免对空指针调用 `deallocate`。

**教材示例代码**
```cpp
void StrVec::free()
{
    // may not pass deallocate a 0 pointer; if elements is 0, there's no work to do
    if (elements) {
        // destroy the old elements in reverse order
        for (auto p = first_free; p != elements; /* empty */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
```

**注意点**
* ⚠️ **警告注意**：`deallocate` 要求传入的指针必须是由同类型 `allocator` 的 `allocate` 返回的，且大小必须匹配。此处 `cap - elements` 正是原始分配的大小。


---

<a id="id12"></a>
## ✅ 知识点12: 拷贝构造函数

**理论**
* **核心主旨总结**：
    * 拷贝构造函数调用 `alloc_n_copy` 为源对象的所有元素分配新内存并拷贝构造。
    * 返回的 `pair` 中 `first` 赋给 `elements`，`second` 同时赋给 `first_free` 和 `cap`，因为新分配的内存大小恰好等于元素个数，所以容量等于已用大小。

**教材示例代码**
```cpp
StrVec::StrVec(const StrVec &s)
{
    // call alloc_n_copy to allocate exactly as many elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
```

**注意点**
* ⚠️ **警告注意**：拷贝构造完成后，新对象的 `cap` 与 `first_free` 指向同一位置，表示**没有预留额外空间**。后续 `push_back` 会立即触发重新分配。


---

<a id="id13"></a>
## ✅ 知识点13: 析构函数

**理论**
* **核心主旨总结**：析构函数直接调用 `free()`，释放所有已构造元素和整个内存块。

**教材示例代码**
```cpp
StrVec::~StrVec() { free(); }
```



---

<a id="id14"></a>
## ✅ 知识点14: 拷贝赋值运算符

**理论**
* **核心主旨总结**：
    * 拷贝赋值运算符采用**拷贝并交换(copy and swap)** 风格，但此处直接实现：先调用 `alloc_n_copy` 为右侧操作数的元素分配新内存并拷贝，然后调用 `free()` 释放左侧原有内存，最后更新三个指针。
    * **这种顺序天然地处理了自赋值(self-assignment)**：因为先分配新内存，再释放旧内存，即使左右对象相同，也是安全的。

**教材示例代码**
```cpp
StrVec &StrVec::operator=(const StrVec &rhs)
{
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
```

**注意点**
* ⚠️ **警告注意**：先 `alloc_n_copy` 再 `free`，保证了自赋值时不会提前释放掉源数据（因为源数据在 `rhs` 中，分配新内存时不依赖于旧内存）。


---

<a id="id15"></a>
## ✅ 知识点15: 重新分配时移动而非拷贝元素（C++11）

**理论**
* **核心主旨总结**：
    * `reallocate` 需要分配新内存、将现有元素转移到新空间、释放旧内存。
    * 由于 `string` 类具有**值行为(value behavior)**，拷贝一个 `string` 会分配独立字符存储，开销较大。
    * 但在重新分配时，旧元素即将被销毁，**仅有一个用户（新对象）会使用这些字符串**，因此**移动(move)** 而非拷贝这些字符串可以大幅提升性能：
        * **移动操作通常只是交换资源指针，避免字符存储的分配与释放**。



**注意点**
* ⚠️ **警告注意**：值行为意味着拷贝是深拷贝，移动是**资源窃取(resource pilfering)**。移动后的源对象处于**有效但未指定(valid but unspecified)** 的状态，可以安全析构。

* 💡 **理解技巧**：重新分配时，旧元素已经是“将亡值”，移动比拷贝更高效。

---

<a id="id16"></a>
## ✅ 知识点16: 移动构造函数和 `std::move` (C++11)

**理论**
* **核心主旨总结**：
    * 标准库类（如 `string`）定义了**移动构造函数(move constructor)**，它通常通过“移动”资源而非拷贝来实现。
    * `std::move` 函数（定义在 `<utility>` 头文件中）将其参数转换为**右值引用(rvalue reference)**，从而触发移动构造函数。关键点：
        1. 在 `reallocate` 中构造新元素时，必须显式使用 `std::move` 以调用移动构造函数；若省略，则使用拷贝构造函数。
        2. 通常**不提供 `using` 声明**给 `move`，而是直接写 `std::move`（原因将在后续章节解释）。



**注意点**
* ⚠️ **警告注意**：**不要对持久对象随意使用 `std::move`**，它仅仅是一个转换，对象被移动后不应再依赖其原值，除非重新赋值。
* 💡 **理解技巧**：`std::move` 并不移动任何东西，它只是**类型转换**，使得移动构造函数可以被匹配。

---

<a id="id17"></a>
## ✅ 知识点17: `reallocate`成员

**理论**
* **核心主旨总结**：
    * `reallocate` 实现内存扩容策略：
        - 新容量为原大小的两倍（若空则初始容量为1）。
        - 通过 `alloc.allocate` 获取新内存。
        - 使用**移动构造**将旧元素转移到新空间：`alloc.construct(dest++, std::move(*elem++))`。
        - 调用 `free()` 释放旧内存和元素。
        - 更新 `elements` 指向新空间首地址，`first_free` 指向最后一个构造元素之后，`cap` 指向新空间末尾。
* **关键点**：移动构造避免了字符数据的拷贝，显著提升性能。

**教材示例代码**
```cpp
void StrVec::reallocate()
{
    // we'll allocate space for twice as many elements as the current size
    auto newcapacity = size() ? 2 * size() : 1;
    // allocate new memory
    auto newdata = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    auto dest = newdata; // points to the next free position in the new array
    auto elem = elements; // points to the next element in the old array
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // free the old space once we've moved the elements
    // update our data structure to point to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
```


---

## 🔑 核心要点总结
1. **自定义动态内存管理的类必须定义拷贝控制成员**：包括拷贝构造函数、拷贝赋值运算符和析构函数，以确保分配的内存被正确释放且资源不泄漏。
2. **使用 `allocator` 分离内存分配与对象构造**：`allocate` 获得原始内存，`construct` 在特定位置构造对象，`destroy` 销毁对象，`deallocate` 释放内存。
3. **指针三件套**：`elements`（首元素）、`first_free`（已用尾部）、`cap`（容量尾部）共同管理连续内存，通过指针差值快速获得 `size` 和 `capacity`。
4. **重新分配时优先移动而非拷贝**：利用 `std::move` 调用移动构造函数，高效转移资源，特别适合 `string` 等具有动态资源的类型。
5. **异常安全与自赋值保护**：拷贝赋值运算符先分配新内存再释放旧内存，天然避免自赋值问题，并保持强异常安全保证。

## 📌 考试速记版
* **最关键的技术要点**：
  - `alloc_n_copy`：分配+拷贝，返回指针`pair`。
  - `free`：逆序`destroy` + `deallocate`。
  - `reallocate`：双倍扩容，`std::move`移动构造。
* **重要对比**：
  - 拷贝构造函数：精确分配，`cap = first_free`。
  - `push_back`：`chk_n_alloc` + `construct(first_free++, s)`。
  - 移动与拷贝：移动窃取资源，拷贝深复制。
* **常见错误陷阱**：
  - 忘记检查 `elements` 是否为空就调用 `deallocate` → 未定义行为。
  - 在 `reallocate` 中忘记 `std::move` → 昂贵的拷贝操作。
  - 自赋值未正确处理 → 使用先分配后释放策略可避免。

**记忆口诀**：
> 分配器，三指针，`size` `capacity` 差相减。  
> 拷贝构造精确配，扩容移动省时间。  
> `chk_n_alloc` 防满员，`free` 逆序销毁全。  
> 赋值先拷后释放，自赋值安全心不悬。