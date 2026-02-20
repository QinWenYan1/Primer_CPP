Exercise 13.49 - 50 太过冗长繁杂，直接跳过

# 📘 第13章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 13.51 | ⭐⭐⭐⭐ (4/5) | 核心概念正确，但表述可以更精确，对两种返回方式的细节可进一步阐明 |
| 13.52 | ⭐⭐⭐⭐ (4/5) | 理解基本到位，但部分术语使用不准确，过程描述需更严谨 |
| 13.53 | ⭐ (1/5) | 未作答，需补充学习并完成此题 |

---

## 🎯 逐题详细评价

### Exercise 13.51

**原题：**  
Although `unique_ptrs` cannot be copied, in § 12.1.5 (p.471) we wrote a clone function that returned a `unique_ptr` by value. Explain why that function is legal and how it works.

```cpp
unique_ptr<int> clone(int p) {
    return unique_ptr<int>(new int(p));
}

unique_ptr<int> clone(int p) {
    unique_ptr<int> ret(new int (p));
    return ret;
}
```

**你的答案：**
```
显然unique_ptr是通过移动语意来实现的， 这两个clone尽管有点小区别但是实际的意义和功能都是一样的， 两个`unique_ptr`没有拷贝构造和拷贝赋值操作符号， unique_ptr只有移动构造函数， 因此在返回一个临时变量unique_ptr的时候， 编译器直接调用移动构造函数并返回到调用处， 函数内部剩下的这个unique_ptr也直接在函数结束后销毁， 并不会被违规访问到内存， 因此这个函数时合理合法的
```

**批改结果：** ⭐⭐⭐⭐ (4/5)

- **概念理解：** ✅ 正确指出了 `unique_ptr` 不能拷贝，依赖移动语义实现返回。  
- **代码质量：** ⚠️ 对两种返回方式的机制描述不够细致，可区分直接返回临时对象与返回局部变量的不同处理。  
- **逻辑完整：** ✅ 基本解释了合法性，但未提及 C++ 标准中“返回值优化 (RVO)”或“将左值视为右值”的规则。  
- **表达清晰：** ⚠️ 部分语句稍显混乱（如“调用移动构造函数并返回到调用处”），术语可更规范。

**正确答案：**
```cpp
// 两种写法均合法，原因如下：
// 1. unique_ptr 只支持移动构造，不支持拷贝构造。
// 2. 返回临时对象时（第一种），编译器直接使用移动构造（或可能应用拷贝省略）。
// 3. 返回局部变量 ret 时（第二种），虽然 ret 是左值，但在返回语句中编译器会将其视为右值（隐式移动），从而调用移动构造函数。
// 4. 移动后，原指针被置空，函数结束后局部变量销毁，不会导致双重释放。
```


---

### Exercise 13.52

**原题：**  
Explain in detail what happens in the assignments of the HasPtr objects on page 541. In particular, describe step by step what happens to values of hp, hp2, and of the rhs parameter in the HasPtr assignment operator.

```cpp
class HasPtr {
public:
    // added move constructor
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps=0; }
    // assignment operator is both the move- and copy-assignment operator
    HasPtr& operator=(HasPtr rhs) { swap(*this, rhs); return *this; }
    // other members as in § 13.2.1 (p. 511)
};

hp = hp2;          // hp2 is an lvalue; copy constructor used to copy hp2
hp = std::move(hp2); // move constructor moves hp2
```

**你的答案：**
```
在`hp = hp2`的时候， hp2是lvalue, 根据函数参数匹配的原则
编译器直接调用拷贝构造函数来构造hp, 这里直接调用默认的拷贝构造函数， 并对这个HasPtr类的成员逐个开始逐个创建临时值并拷贝进去，然后再销毁这这个临时变量但是hp2依然状态不变

在`hp = std::move(hp2)`的时候， 这个时候右边已经是rvalue 引用，根据函数匹配的规则， 这一次调用的是移动构造函数，将hp2标为可以移交内存的变量， 并将新建立的hp里的成员逐个指向之前hp2的每个成员的内存， 并将ps这个指针成员置0防止意外造成为定义行为
执行完后， hp2 并不会销毁， 尽管hp2存在，但是这个时候的hp2是不允许再去访问了
```

**批改结果：** ⭐⭐⭐⭐ (4/5)

- **概念理解：** ✅ 正确区分了左值和右值导致的不同构造函数调用。  
- **代码质量：** ⚠️ 对过程的描述不够精确，混淆了“构造hp”和“构造rhs”的概念。  
- **逻辑完整：** ✅ 大致描述了赋值操作的过程，但缺少对 `swap` 和临时对象析构的细致说明。  
- **表达清晰：** ⚠️ 存在术语误用（如“调用默认的拷贝构造函数”），以及“hp”指代不明。

**正确答案：**
```cpp
// hp = hp2 时：
// 1. hp2 是左值，调用拷贝构造函数初始化 rhs（形参），rhs 成为 hp2 的副本。
// 2. 进入 operator= 内部，执行 swap(*this, rhs)，交换 hp 和 rhs 的资源（指针、计数器等）。
// 3. 函数返回，rhs 被销毁（此时 rhs 持有原 hp 的资源），原 hp2 保持不变。

// hp = std::move(hp2) 时：
// 1. std::move(hp2) 将 hp2 转换为右值，调用移动构造函数初始化 rhs，rhs 接管 hp2 的资源，hp2.ps 被置空。
// 2. 执行 swap(*this, rhs)，交换 hp 和 rhs 的资源（此时 rhs 持有原 hp2 的资源，hp 持有原 this 的资源）。
// 3. 函数返回，rhs 被销毁（释放原 hp 的资源），hp 现在拥有原 hp2 的资源，hp2 处于“空”状态（可安全析构）。
```


---
### Exercise 13.53

**原题：**  
As a matter of low-level efficiency, the HasPtr assignment operator is not ideal. Explain why. Implement a copy-assignment and move-assignment operator for HasPtr and compare the operations executed in your new move-assignment operator versus the copy-and-swap version.

**你的答案：**  
相比于移动赋值运算符来说， 依然是效率笔记低的， 原因有两个，第一就是如果没有定义自己版本的swap的话， 那么这个拷贝赋值运算符号依然是通过依次拷贝两次赋值完成的效率第下， 第二就是在调用这个拷贝拷贝操作的时候， 参数需要调用到这个拷贝构造函数，这两个情况都导致了赋值操作的效率低下，那么接下来我们定义一个自己的移动赋值操作符来解决这两个问题

```cpp
    HasPtr &operator=(HasPtr &&rhs)
    {

        //自赋值检查
        if(*this == rhs) return *this; 

        //否则开始移动
        ps = rhs.ps; 
        rhs.ps = 0; 
        i = rhs.i; 

        return *this; 

    }
```
对比下来， 相对于之前那个， 没有意义的拷贝构造都不存在了， 现在有的只是三次赋值， 没有了拷贝， 因此效率非常高

**批改：** ⭐⭐⭐ (3/5) 总体评价：你对拷贝赋值运算符低效原因的理解基本正确，但移动赋值运算符的实现存在关键缺陷，且未按要求提供拷贝赋值运算符的实现。

**详细分析：**
- ✅ **概念理解：** 准确指出了拷贝交换版本会额外调用拷贝构造函数（对于左值）以及可能因未自定义 swap 而导致的低效问题，思路方向正确。
- ⚠️ **代码实现不完整：** 题目要求同时实现**拷贝赋值**和**移动赋值**运算符，你只提供了移动赋值的实现，缺少拷贝赋值部分。
- ❌ **移动赋值实现错误：**
    1. **未释放当前资源：** 在接管 `rhs` 的资源前，没有释放当前对象持有的内存（如 `delete ps`），会导致内存泄漏。
    2. **自赋值检查不当：** 使用 `*this == rhs` 进行自赋值检查，但 `HasPtr` 通常未定义 `operator==`，且移动赋值中自赋值极少发生。更常见的是检查地址 `if (this == &rhs)`。
    3. **缺少异常安全保证：** 简单的指针赋值在抛出异常时可能使对象处于不一致状态。移动赋值通常应保证操作后源对象处于有效但未定义的状态，且不抛出异常（noexcept）。
- ⚠️ **比较分析不全面：** 你仅提到了“三次赋值”，但真正的移动赋值应避免资源重新分配，而你的实现因内存泄漏问题，实际上并不正确，因此比较失去了意义。

**正确答案：**  
以下是 `HasPtr` 拷贝赋值（采用拷贝并交换惯用法）和正确移动赋值的参考实现，并附操作对比。

```cpp
#include <string>
#include <iostream>

class HasPtr {
public:
    // 构造函数
    HasPtr(const std::string &s = std::string())
        : ps(new std::string(s)), i(0) {}
    // 拷贝构造函数
    HasPtr(const HasPtr &p)
        : ps(new std::string(*p.ps)), i(p.i) {}
    // 移动构造函数
    HasPtr(HasPtr &&p) noexcept
        : ps(p.ps), i(p.i) { p.ps = nullptr; }
    // 析构函数
    ~HasPtr() { delete ps; }

    // 拷贝赋值运算符（拷贝并交换版本）
    HasPtr& operator=(HasPtr rhs) {  // 参数按值传递，调用拷贝或移动构造
        swap(*this, rhs);             // 交换资源
        return *this;                 // rhs 销毁，释放原资源
    }

    // 移动赋值运算符（更高效的直接版本）
    HasPtr& operator=(HasPtr &&rhs) noexcept {
        if (this != &rhs) {           // 自赋值检查（地址比较）
            delete ps;                 // 释放当前资源
            ps = rhs.ps;                // 接管资源
            i = rhs.i;
            rhs.ps = nullptr;           // 将 rhs 置于可析构状态
        }
        return *this;
    }

    // swap 函数
    friend void swap(HasPtr &lhs, HasPtr &rhs) noexcept {
        using std::swap;
        swap(lhs.ps, rhs.ps);
        swap(lhs.i, rhs.i);
    }

private:
    std::string *ps;
    int i;
};
```

**操作对比（新移动赋值 vs 拷贝交换版本）：**
- **拷贝交换版本：** 当对左值赋值时，`operator=(HasPtr rhs)` 会调用**拷贝构造函数**（分配新内存），然后交换指针，最后析构临时对象（释放原内存）。涉及一次内存分配、一次释放，以及指针交换。
- **新移动赋值：** 当对右值赋值时，直接**释放当前内存**，然后**转移指针**，将源对象指针置空。无内存分配，仅有指针赋值和一次释放。因此，对于右值，移动赋值避免了不必要的内存分配和拷贝，效率更高。
