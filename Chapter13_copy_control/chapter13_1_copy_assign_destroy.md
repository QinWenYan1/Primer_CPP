# 📘 第13章 拷贝控制 (Copy Control)

> 来源说明：C++ Primer 第13章 | 本节涵盖：类如何通过特殊成员函数控制对象的拷贝、赋值、移动和销毁行为。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 拷贝控制概述*](#id1)
* [*知识点2: 拷贝构造函数 (Copy Constructor) 定义与声明*](#id2)
* [*知识点3: 合成拷贝构造函数 (Synthesized Copy Constructor)*](#id3)
* [*知识点4: 拷贝初始化 (Copy Initialization)*](#id4)
* [*知识点5: 参数与返回值的拷贝初始化*](#id5)
* [*知识点6: 拷贝初始化的限制*](#id6)
* [*知识点7: 编译器优化与绕过拷贝构造函数*](#id7)
* [*知识点8: 拷贝赋值运算符 (Copy-Assignment Operator) 简介*](#id8)
* [*知识点9: 重载赋值与拷贝赋值运算符定义*](#id9)
* [*知识点10: 合成拷贝赋值运算符 (Synthesized Copy-Assignment Operator)*](#id10)
* [*知识点11: 析构函数 (Destructor) 定义与特性*](#id11)
* [*知识点12: 析构函数执行过程*](#id12)
* [*知识点13: 析构函数的调用时机*](#id13)
* [*知识点14: 合成析构函数 (Synthesized Destructor)*](#id14)
* [*知识点15: “三/五法则”介绍 (The Rule of Three/Five)*](#id15)
* [*知识点16: 需要析构函数的类也需要拷贝和赋值*](#id16)
* [*知识点17: 需要拷贝操作的类也需要赋值操作，反之亦然*](#id17)
* [*知识点18: 使用 `= default`*](#id18)
* [*知识点19: 阻止拷贝 (Preventing Copies)*](#id19)
* [*知识点20: 定义删除的函数 (Defining a Function as Deleted)*](#id20)
* [*知识点21: 析构函数不能是删除的成员*](#id21)
* [*知识点22: 合成拷贝控制成员可能被定义为删除的*](#id22)
* [*知识点23: 私有拷贝控制 (Prior to the new standard)*](#id23)

---

<a id="id1"></a>
## ✅ 知识点1: 拷贝控制概述

**理论**
* **核心主旨总结**：
    * 类通过<b>拷贝控制(Copy Control)</b>操作来定义其类型的对象在被拷贝、赋值、移动或销毁时的行为。
    * 这些操作由五个特殊成员函数实现：
        1. **拷贝构造函数(copy constructor)**
        2. **拷贝赋值运算符(copy-assignment operator)**
        3. **移动构造函数(move constructor)**
        4. **移动赋值运算符(move-assignment operator)**
        5. **析构函数(destructor)**。
    * 如果类没有定义这些操作，编译器会自动合成它们。
* **⚠️ 重要警告**：拷贝控制是定义任何C++类的重要组成部分。程序员必须理解并定义这些操作，否则编译器将生成默认版本，而这些默认行为可能并不符合预期。

---

<a id="id2"></a>
## ✅ 知识点2: 拷贝构造函数 (Copy Constructor) 定义与声明

**理论**
* **核心主旨总结**：
    * 如果一个构造函数的**第一个参数是类类型的引用**，且任何额外参数都有默认值，那么它就是拷贝构造函数。
    * 这个参数几乎总是`const`引用，但也可以是非`const`引用。
* **原因解释**：
    * 拷贝构造函数在多种场景下被隐式调用，因此通常<b>不应是`explicit`</b>的。

**教材示例代码**
```cpp
class Foo {
public:
    Foo(); // default constructor
    Foo(const Foo&); // copy constructor
};
```

---

<a id="id3"></a>
## ✅ 知识点3: 合成拷贝构造函数 (Synthesized Copy Constructor)

**理论**
* **核心主旨总结**：
    * 如果一个类没有定义自己的拷贝构造函数，编译器会为它合成一个。
    * 与合成的默认构造函数不同，**即使类定义了其他构造函数，拷贝构造函数也会被合成**。
* **工作原理**：合成拷贝构造函数执行**逐成员拷贝(memberwise copy)**：
    * 将给定对象中的每个非静态成员依次拷贝到正在创建的对象中。
* **成员拷贝方式**：成员的**类型决定如何拷贝**。
    * **类类型成员**：使用该类的拷贝构造函数。
    * **内置类型成员**：直接拷贝。
    * **数组成员**：逐个元素拷贝（类类型元素使用其拷贝构造函数）。

**教材示例代码**
```cpp
class Sales_data {
public:
    // ... 其他成员和构造函数
    // 声明等价于合成的拷贝构造函数
    Sales_data(const Sales_data&);
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};

// 等价于为Sales_data合成的拷贝构造函数
Sales_data::Sales_data(const Sales_data &orig) :
    bookNo(orig.bookNo), // 调用string的拷贝构造函数
    units_sold(orig.units_sold), // 拷贝orig.units_sold
    revenue(orig.revenue) // 拷贝orig.revenue
    { } // 空函数体
```

---

<a id="id4"></a>
## ✅ 知识点4: 拷贝初始化 (Copy Initialization)

**理论**
* **核心主旨总结**：理解<b>直接初始化(direct initialization)</b>和<b>拷贝初始化(copy initialization)</b>的区别:
    * **直接初始化**：编译器使用普通的函数匹配来选择最匹配的构造函数。
    * **拷贝初始化**：编译器将右侧运算对象拷贝到正在创建的对象中，必要时进行类型转换。
* **发生场景**：拷贝初始化不仅在使用`=`定义变量时发生，还会在以下情况发生：
    1. 将对象作为实参传递给一个**非引用类型**的形参。
    2. 从一个返回类型为**非引用**的函数返回对象。
    3. 用花括号列表初始化数组元素或聚合类成员。
    4. 某些类（如标准库容器）在初始化其元素或调用`insert`/`push`操作时。
        * 相反`emplace`使用的是直接初始化
* **拷贝初始化不一定用拷贝构造函数**：
    * 拷贝初始化通常调用拷贝构造函数，但在支持移动操作的类下也可能调用移动构造函数 § 13.6.2。
    * 因此拷贝初始化要求类必须定义这两者之一。 
* **拷贝初始化VS赋值：**
    


    | 特性 | 拷贝初始化 | 赋值操作 |
    | --- | --- | --- |
    | **核心目的** | **创建新对象** | 修改**已有对象**的内容 |
    | **调用函数** | `Point(const Point&)` | `Point& operator=(const Point&)` |
    | **标志符** | 声明语句（如 `Point x = ...`） | 独立的语句（如 `x = ...`） |



**教材示例代码**
```cpp
string dots(10, '.'); // direct initialization
string s(dots); // direct initialization
string s2 = dots; // copy initialization
string null_book = "9-999-99999-9"; // copy initialization
string nines = string(100, '9'); // copy initialization
```

---

<a id="id5"></a>
## ✅ 知识点5: 参数与返回值的拷贝初始化

**理论**
* **核心主旨总结**：
    * 在函数调用中，**非引用类型的参数**是拷贝初始化的；
    * 函数返回**非引用类型**的对象时，返回值也用于拷贝初始化调用点的结果。
* **关键推论**：
    * 这解释了为什么**拷贝构造函数自己的参数必须是引用类型**。
    * 如果参数不是引用，调用拷贝构造函数需要拷贝实参，而拷贝实参又需要调用拷贝构造函数，导致无限递归。

---

<a id="id6"></a>
## ✅ 知识点6: 拷贝初始化的限制

**理论**
* **核心主旨总结**：
    * 如果初始化需要用到`explicit`构造函数进行转换，那么使用拷贝初始化还是直接初始化就很重要。
    * **拷贝初始化不能使用`explicit`构造函数**。
* **原理**：
    * 无法在拷贝初始化的隐式转换过程中使用`explicit`构造函数。
    * 如果需要，必须显式地使用构造函数。

**教材示例代码**
```cpp
vector<int> v1(10); // ok: direct initialization
vector<int> v2 = 10; // error: constructor that takes a size is explicit
void f(vector<int>); // f‘s parameter is copy initialized
f(10); // error: can’t use an explicit constructor to copy an argument
f(vector<int>(10)); // ok: directly construct a temporary vector from an int
```

**代码解析**
* `v2`报错是因为`vector`的只接受一个表示大小的参数构造函数是`explicit`
* 为了使用这个构造函数， 我们必须显式申明

---

<a id="id7"></a>
## ✅ 知识点7: 编译器优化与绕过拷贝构造函数

**理论**
* **核心主旨总结**：
    * 在拷贝初始化过程中，编译器被允许（但非必须）<b>跳过</b>拷贝/移动构造函数，直接创建对象。
* **重要限制**：**即使编译器省略了拷贝/移动构造函数的调用，该拷贝/移动构造函数也必须存在且可访问**（例如，不能是`private`的）。

**教材示例代码**
```cpp
// 编译器可能将以下拷贝初始化
string null_book = “9-999-99999-9”; // copy initialization
// 重写为直接初始化，从而跳过拷贝构造函数
string null_book(“9-999-99999-9”); // compiler omits the copy constructor
```

---

<a id="id8"></a>
## ✅ 知识点8: 拷贝赋值运算符 (Copy-Assignment Operator) 简介

**理论**
* **核心主旨总结**：
    * 类可以控制其类型的对象如何被赋值。
    * 与拷贝构造函数一样，**如果类没有定义自己的拷贝赋值运算符，编译器会为它合成一个**。

**教材示例代码**
```cpp
Sales_data trans, accum;
trans = accum; // uses the Sales_data copy-assignment operator
```

---

<a id="id9"></a>
## ✅ 知识点9: 重载赋值与拷贝赋值运算符定义

**理论**
* **核心主旨总结**：
    * 重载运算符是名为`operator`后接运算符符号的函数。
    * 赋值运算符是名为`operator=`的函数。
* **作为成员函数**：
    * 当运算符是成员函数时，左侧运算对象绑定到**隐式的`this`参数**。
    * 右侧运算对象作为**显式函数参数传递**。
    * 拷贝赋值运算符号接受与所在类**相同类型**的参数
* **⚠️ 最佳实践**：
    * **赋值运算符通常应返回一个指向其左侧运算对象的引用**。
    * 以保持与内置类型赋值行为的一致性。
    * 这也是STL的准则

**教材示例代码**
```cpp
class Foo {
public:
    Foo& operator=(const Foo&); // assignment operator
};
```

---

<a id="id10"></a>
## ✅ 知识点10: 合成拷贝赋值运算符 (Synthesized Copy-Assignment Operator)

**理论**
* **核心主旨总结**：
    * 合成拷贝赋值运算符将右侧对象的每个非静态成员赋值给左侧对象的对应成员，使用相应类型的拷贝赋值运算符。
    * 对于数组成员，赋值每个元素，它返回一个指向其左侧对象的引用。
    * 与拷贝构造函数类似，在某些特定情况下（例如类中含有`const`成员、引用成员，或者某些成员的赋值运算符不可访问时），编译器会将合成的赋值运算符定义为删除的（deleted），即不允许进行对象间的赋值操作。

**教材示例代码**
```cpp
// equivalent to the synthesized copy-assignment operator
Sales_data&
Sales_data::operator=(const Sales_data &rhs)
{
    bookNo = rhs.bookNo; // calls the string::operator=
    units_sold = rhs.units_sold; // uses the built-in int assignment
    revenue = rhs.revenue; // uses the built-in double assignment
    return *this; // return a reference to this object
}
```

---

<a id="id11"></a>
## ✅ 知识点11: 析构函数 (Destructor) 定义与特性

**理论**
* **核心主旨总结**：
    * 析构函数执行与构造函数相反的操作：
        1. 释放对象使用的资源
        2. 并销毁对象的非静态数据成员

* **定义**：
    * 析构函数是名字由类名前加波浪线(`~`)组成的成员函数。
    * 它**没有返回值，也不接受参数**，因此**不能被重载**。
    * 一个类只有一个析构函数。

**教材示例代码**
```cpp
class Foo {
public:
    ~Foo(); // destructor
};
```

---

<a id="id12"></a>
## ✅ 知识点12: 析构函数执行过程

**理论**
* **核心主旨总结**：析构函数包括一个函数体和一个隐含的**析构部分(destruction part)**: 
    1. **首先执行函数体**，通常用于释放对象生命周期内分配的资源。
    2. **然后执行隐含的析构部分**，按成员初始化顺序的**逆序**销毁每个成员。
* **成员销毁方式**：
    * 类类型成员：执行该成员自己的析构函数。
    * 内置类型成员：**无析构函数**，什么都不做。
* **⚠️ 重要警告**：
    * **内置指针类型的隐式销毁不会`delete`指针所指的对象**。
    * 智能指针是类类型，有析构函数，因此会被自动销毁。

---

<a id="id13"></a>
## ✅ 知识点13: 析构函数的调用时机

**理论**
* **核心主旨总结**：当对象被销毁时，其析构函数自动运行。
* **调用时机**：
    1. 变量离开其作用域时。
    2. 一个对象被销毁时，其成员被销毁。
    3. 容器（标准库容器或数组）被销毁时，其元素被销毁。
    4. 对动态分配的对象，当`delete`运算符应用于指向它的指针时。
    5. 临时对象，在创建它的完整表达式结束时被销毁。
* **⚠️ 重要提示**：
    * **当指向某个对象的指针或引用变量自身离开作用域时，并不会因此而触发该对象的析构函数**。

**教材示例代码**
```cpp
{ 
    // p and p2 point to dynamically allocated objects
    Sales_data *p = new Sales_data; // p is a built-in pointer
    auto p2 = make_shared<Sales_data>(); // p2 is a shared_ptr
    Sales_data item(*p); // copy constructor copies *p into item
    vector<Sales_data> vec; // local object
    vec.push_back(*p2); 
    delete p; //p是内置指针类型 ，需要手动管理，此时调用析构函数
} // 退出本地scope, p2,vec,item的析构函数被自动调用
```

---

<a id="id14"></a>
## ✅ 知识点14: 合成析构函数 (Synthesized Destructor)

**理论**
* **核心主旨总结**：
    * 如果一个类没有定义自己的析构函数，编译器会为它合成一个。
    * 合成的析构函数有一个**空的函数体**。
* **⚠️ 重要提示**：
    * 析构函数体**并不直接销毁成员**。
    * 成员是在**析构函数体之后的隐含析构阶段**中被销毁的。
    * 析构函数体是成员销毁之外执行的额外操作。
    * 和复制初始化和复制赋值操作符一样，对于一些类，合成的析构函数不允许这些类的对象被销毁。 

**教材示例代码**
```cpp
class Sales_data {
public:
    // no work to do other than destroying the members, which happens automatically
    ~Sales_data() { }
    // other members as before
};
```

---

<a id="id15"></a>
## ✅ 知识点15: “三/五法则”介绍 (The Rule of Three/Five)

**理论**
* **核心主旨总结**：
    * 控制对象拷贝的三个基本操作是：
        1. **拷贝构造函数**
        2. **拷贝赋值运算符**
        3. **析构函数**
    * 在新标准下，一个类还可以定义移动构造函数和**移动赋值运算符**，因此合称“五法则”。
* **通常作为一个单元**：
    * 虽然可以只定义其中一两个操作，但这些操作通常应被视为一个整体。
    * 一般而言，需要其中一个而不需要其他所有的情况是不常见的。

---

<a id="id16"></a>
## ✅ 知识点16: 需要析构函数的类也需要拷贝和赋值

**理论**
* **核心主旨总结**：
    * 决定一个类是否需要自己版本的拷贝控制成员时，一个<b>经验法则(rule of thumb)</b>是：
        * 首先确定这个类是否需要一个析构函数。
        * **如果一个类需要析构函数，那么它几乎肯定也需要拷贝构造函数和拷贝赋值运算符**。
* **核心提示**：
    * **如果一个类需要析构函数，那么它几乎肯定也需要拷贝赋值运算符和一个拷贝构造函数。**

**教材示例代码**
```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    ~HasPtr() { delete ps; }
    // WRONG: HasPtr needs a copy constructor and copy-assignment operator
    // other members as before
};

HasPtr f(HasPtr hp) // HasPtr passed by value, so it is copied
{
    HasPtr ret = hp; // copies the given HasPtr
    // process ret
    return ret; // ret and hp are destroyed
}

HasPtr p("some values");
f(p); // when f completes, the memory to which p.ps points is freed
HasPtr q(p); // now both p and q point to invalid memory!
```
**示例分析**：
* 以`HasPtr`类为例，它在构造函数中动态分配了内存，因此需要自己定义析构函数来通过`delete`释放。
* 如果只定义析构函数而使用合成的拷贝操作
    * 会导致多个对象指向同一块内存
    * 因为默认合成的会拷贝这个指针成员到另一个对象
    * 并在析构时被`delete`多次，引发未定义行为。
* 同时，其中一个对象被销毁后，其他指向该内存的对象就变成了悬空指针。

---

<a id="id17"></a>
## ✅ 知识点17: 需要拷贝操作的类也需要赋值操作，反之亦然

**理论**
* **核心主旨总结**：
    * 另一个经验法则是：**如果一个类需要拷贝构造函数，那么它几乎肯定也需要拷贝赋值运算符，反之亦然**。
* **⚠️ 注意**：
    * 需要拷贝构造函数或拷贝赋值运算符**并不必然**意味着需要**析构函数**。

* **示例**：
    * 一个为每个对象分配唯一序列号的类。
    * 它需要拷贝构造函数来生成新序列号，也需要拷贝赋值运算符来避免覆盖左侧对象的序列号。
    * 但这个类可能不需要析构函数。

---

<a id="id18"></a>
## ✅ 知识点18: 使用 `= default`

**理论**
* **核心主旨总结**：
    * 我们可以通过将拷贝控制成员定义为`= default`来**显式要求编译器生成合成的版本**。
* **细节**：
    * 如果在类内成员声明时指定`= default`，则合成的函数是**隐式内联**的。
    * 如果在类外定义时指定`= default`，则成员不是内联的。
* **重要限制**：
    * 只能对**有合成版本**的成员函数（默认构造函数或拷贝控制成员）使用`= default`。

**教材示例代码**
```cpp
class Sales_data {
public:
    // copy control; use defaults
    Sales_data() = default;
    Sales_data(const Sales_data&) = default;
    Sales_data& operator=(const Sales_data&);
    ~Sales_data() = default;
    // other members as before
};
Sales_data& Sales_data::operator=(const Sales_data&) = default;
```

---

<a id="id19"></a>
## ✅ 知识点19: 阻止拷贝 (Preventing Copies)

**理论**
* **核心主旨总结**：有些类（如`iostream`）不应该有拷贝或赋值的意义。虽然不定义拷贝控制成员看似可行，但编译器会合成它们，因此必须通过其他方式阻止拷贝。

---

<a id="id20"></a>
## ✅ 知识点20: 定义删除的函数 (Defining a Function as Deleted)

**理论**
* **核心主旨总结**：在新标准下，可以通过将拷贝构造函数和拷贝赋值运算符定义为**删除的函数(deleted function)**来阻止拷贝。删除的函数是这样一种函数：我们声明了它们，但不能以任何方式使用它们。在函数的参数列表后加上`= delete`来指示删除的函数。
* **与`= default`的区别**：
    1. **出现位置**：`= delete`必须出现在函数**第一次声明**时，而`= default`可以在定义时出现。
    2. **适用范围**：`= default`只能用于编译器可以合成的默认构造函数或拷贝控制成员；`= delete`可用于任何函数（虽然主要用于拷贝控制成员）。

**教材示例代码**
```cpp
struct NoCopy {
    NoCopy() = default; // use the synthesized default constructor
    NoCopy(const NoCopy&) = delete; // no copy
    NoCopy &operator=(const NoCopy&) = delete; // no assignment
    ~NoCopy() = default; // use the synthesized destructor
};
```

---

<a id="id21"></a>
## ✅ 知识点21: 析构函数不能是删除的成员

**理论**
* **核心主旨总结**：不能删除析构函数。
* **原因**：如果析构函数被删除，就无法销毁该类型的对象。编译器将不允许定义该类型的变量或临时对象，也不能定义有该类型成员的类。虽然可以动态分配这种类型的对象，但**无法释放(`delete`)它们**。
* **⚠️ 警告**：**不可能定义对象或删除指向具有已删除析构函数的类型的动态分配对象的指针。**

---

<a id="id22"></a>
## ✅ 知识点22: 合成拷贝控制成员可能被定义为删除的

**理论**
* **核心主旨总结**：在某些情况下，编译器会将合成的拷贝控制成员定义为删除的。本质上，**当无法拷贝、赋值或销毁类的某个成员时，对应的合成拷贝控制成员就会被定义为删除的**。
* **主要规则**：
    1. **合成析构函数**：如果类的某个成员的析构函数是删除的或不可访问的，则合成析构函数被定义为删除的。
    2. **合成拷贝构造函数**：如果类的某个成员的拷贝构造函数是删除的或不可访问的，或者类有一个成员有删除的或不可访问的析构函数，则合成拷贝构造函数被定义为删除的。
    3. **合成拷贝赋值运算符**：如果类的某个成员的拷贝赋值运算符是删除的或不可访问的，或者类有一个`const`或引用成员，则合成拷贝赋值运算符被定义为删除的。
    4. **合成默认构造函数**：如果类的某个成员的析构函数是删除的或不可访问的；或者类有一个没有类内初始化器的引用成员；或者类有一个没有类内初始化器且其类型没有显式定义默认构造函数的`const`成员，则合成默认构造函数被定义为删除的。

**注意点**
* 理解这些规则有助于理解为什么某些类不能被拷贝、赋值或默认构造。
* 例如，有引用成员的类不能使用合成的拷贝赋值运算符，因为赋值后左侧引用成员仍然绑定到原来的对象，这通常不是期望的行为。

---

<a id="id23"></a>
## ✅ 知识点23: 私有拷贝控制 (Prior to the new standard)

**理论**
* **核心主旨总结**：在新标准之前，类通过将其拷贝构造函数和拷贝赋值运算符声明为`private`来阻止拷贝。
* **工作原理**：由于这些成员是私有的，用户代码无法拷贝对象。但类的友元和成员函数仍然可以拷贝。为了阻止所有拷贝，可以将这些私有成员**声明但不定义**。用户代码尝试拷贝会在编译时报错；成员或友元函数尝试拷贝会在链接时报错。
* **最佳实践**：**希望阻止拷贝的类应该使用`= delete`来定义其拷贝构造函数和拷贝赋值运算符，而不是将这些成员设为`private`。**

**教材示例代码**
```cpp
class PrivateCopy {
    // no access specifier; following members are private by default
    // copy control is private and so is inaccessible to ordinary user code
    PrivateCopy(const PrivateCopy&);
    PrivateCopy &operator=(const PrivateCopy&);
    // other members
public:
    PrivateCopy() = default; // use the synthesized default constructor
    ~PrivateCopy(); // users can define objects of this type but not copy them
};
```

---

## 🔑 核心要点总结
1.  **拷贝控制(Copy Control)**：类通过五个特殊成员函数（拷贝构造、拷贝赋值、移动构造、移动赋值、析构）定义对象在拷贝、赋值、移动、销毁时的行为。编译器会合成未定义的版本。
2.  **三/五法则(Rule of Three/Five)**：需要自定义析构函数的类，通常也需要自定义拷贝构造和拷贝赋值运算符；需要其中一个拷贝操作的类，通常也需要另一个。这些操作应被视为一个逻辑单元。
3.  **阻止拷贝**：在新标准中，通过将拷贝构造函数和拷贝赋值运算符定义为`= delete`来阻止拷贝。析构函数不能是删除的。
4.  **合成与删除**：编译器合成的拷贝控制成员在某些条件下（如类有引用成员、`const`成员或具有删除/不可访问析构函数的成员）会被定义为删除的。

## 📌 考试速记版
*   **拷贝构造函数**：`Foo(const Foo&);` 第一个参数必须是**类类型的引用**。用于拷贝初始化。
*   **拷贝赋值运算符**：`Foo& operator=(const Foo&);` 应返回**左侧对象的引用**。
*   **析构函数**：`~Foo();` 不接受参数，不能重载。先执行函数体，再**逆序销毁成员**。
*   **`= default` vs `= delete`**：`= default`显式要求合成版本；`= delete`禁止函数的使用，用于阻止拷贝。
*   **重要经验法则**：需要析构 -> 需要拷贝构造和拷贝赋值。
*   **重要限制**：
    *   有`const`或引用成员的类，合成拷贝赋值运算符是**删除的**。
    *   有未提供类内初始化器的引用成员或`const`成员，合成默认构造函数是**删除的**。
    *   析构函数不能是删除的。

**记忆口诀**：拷贝控制五成员，构造赋值析构动。需要析构三兄弟，阻止拷贝用删除(`delete`)。引用`const`成员要注意，合成赋值会屏蔽(`delete`)。