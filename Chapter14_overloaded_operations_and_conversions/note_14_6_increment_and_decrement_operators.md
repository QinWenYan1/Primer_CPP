# 📘 14.6. 递增和递减操作符 (Increment and Decrement Operators)

> 来源说明：C++ Primer 5th 14.6节 | 本节涵盖：如何为类定义前缀和后缀的递增(++)与递减(--)操作符，以及它们的实现细节和最佳实践。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 递增递减操作符概述*](#id1)
* [*知识点2: 最佳实践：应同时定义前缀和后缀版本，通常应定义为成员*](#id2)
* [*知识点3: 定义前缀递增/递减操作符（含StrBlobPtr声明）*](#id3)
* [*知识点4: 最佳实践：前缀操作符应返回引用*](#id4)
* [*知识点5: 前缀递增的实现*](#id5)
* [*知识点6: 前缀递减的实现*](#id6)
* [*知识点7: 区分前缀和后缀操作符*](#id7)
* [*知识点8: 为StrBlobPtr添加后缀操作符声明*](#id8)
* [*知识点9: 最佳实践：后缀操作符应返回旧值（值返回）*](#id9)
* [*知识点10: 后缀递增的实现*](#id10)
* [*知识点11: 后缀递减的实现*](#id11)
* [*知识点12: 后缀操作符如何工作（调用前缀版本）*](#id12)
* [*知识点13: 注意：int参数未使用，不命名*](#id13)
* [*知识点14: 显式调用后缀操作符*](#id14)
* [*知识点15: 显式调用后缀操作符的代码示例*](#id15)
* [*知识点16: 显式调用时传递的值通常忽略*](#id16)

---

<a id="id1"></a>
## ✅ 知识点1: 递增递减操作符概述

**理论**
* **核心主旨总结**：递增(++)和递减(--)操作符最常用于实现迭代器(iterator)类，使对象能够在序列元素之间移动。虽然C++语言没有强制要求这些操作符必须定义为类的成员，但更倾向于将它们定义为成员，因为它们会改变操作对象的状态。
* **术语提醒**：迭代器(iterator)是用于遍历容器元素的对象。

---

<a id="id2"></a>
## ✅ 知识点2: 最佳实践：应同时定义前缀和后缀版本，通常应定义为成员

**理论**
* **核心主旨总结**：**定义递增或递减操作符的类应该同时定义前缀(prefix)和后缀(postfix)版本**。这些操作符通常应定义为类的成员。
* **重点突出**：这是一个重要的**最佳实践**，确保类的行为与内置类型一致。

---

<a id="id3"></a>
## ✅ 知识点3: 定义前缀递增/递减操作符（含StrBlobPtr声明）

**理论**
* **核心主旨总结**：为了说明，我们将为`StrBlobPtr`类（参见12.1.6节）定义这些操作符。下面的代码展示了前缀递增(++)和递减(--)操作符在类中的声明。
* **术语提醒**：`StrBlobPtr`是一个指向`StrBlob`内部向量的指针类，用于遍历元素。

**教材示例代码**
```cpp
class StrBlobPtr {
public:
    // increment and decrement
    StrBlobPtr& operator++();    // prefix operators
    StrBlobPtr& operator--();
    // other members as before
};
```

---

<a id="id4"></a>
## ✅ 知识点4: 最佳实践：前缀操作符应返回引用

**理论**
* **核心主旨总结**：**为了与内置操作符保持一致，前缀操作符应返回指向递增或递减后对象的引用**。
* **重点突出**：这是确保自定义类型行为与内置类型一致的关键。

---

<a id="id5"></a>
## ✅ 知识点5: 前缀递增的实现

**理论**
* **核心主旨总结**：前缀递增和递减操作符的工作方式相似——它们调用`check`来验证`StrBlobPtr`是否仍然有效，并检查给定的索引是否合法。如果`check`没有抛出异常，操作符返回指向当前对象的引用。
* **具体实现**：在递增时，将当前值`curr`传递给`check`。只要该值小于底层`vector`的大小，`check`就会正常返回；如果`curr`已经指向`vector`末尾，`check`会抛出异常。
* **术语提醒**：`check`是一个成员函数，用于验证下标是否有效。

**教材示例代码**
```cpp
// prefix: return a reference to the incremented/decremented object
StrBlobPtr& StrBlobPtr::operator++()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;    // advance the current state
    return *this;
}
```

**注意点**
* ⚠️ **检查时机**：递增操作在增加`curr`之前先检查，防止越界。

---

<a id="id6"></a>
## ✅ 知识点6: 前缀递减的实现

**理论**
* **核心主旨总结**：递减操作符先递减`curr`，然后调用`check`。这样，如果`curr`已经是0，递减后会产生一个很大的无符号数值（无效下标），`check`会捕获到错误并抛出异常。
* **重点突出**：**递减操作符先递减后检查**，以确保边界安全。

**教材示例代码**
```cpp
StrBlobPtr& StrBlobPtr::operator--()
{
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;    // move the current state back one element
    check(-1, "decrement past begin of StrBlobPtr");
    return *this;
}
```

**注意点**
* ⚠️ **递减边界**：当`curr`为0时，`--curr`会产生一个极大的正数（因为`curr`是`size_t`类型），这个值作为无效下标传递给`check`，从而触发异常。

---

<a id="id7"></a>
## ✅ 知识点7: 区分前缀和后缀操作符

**理论**
* **核心主旨总结**：同时定义前缀和后缀操作符时存在一个问题：普通的重载无法区分它们，因为前缀和后缀使用相同的符号（++或--），并且有相同数量和类型的操作数。
* **解决方法**：后缀版本接受一个额外的`int`类型参数（通常不使用）。当使用后缀操作符时，编译器自动传递**0**作为该参数的值。虽然后缀函数可以使用这个额外参数，但通常不应使用它，其唯一目的是**区分前缀函数和后缀函数**。

**注意点**
* 📋 **参数约定**：这个额外的`int`参数不参与实际操作，仅用于函数重载决议。

---

<a id="id8"></a>
## ✅ 知识点8: 为StrBlobPtr添加后缀操作符声明

**理论**
* **核心主旨总结**：现在为`StrBlobPtr`添加后缀递增和递减操作符的声明，注意它们返回的是`StrBlobPtr`（值返回），而不是引用，并且参数列表中多了一个`int`。

**教材示例代码**
```cpp
class StrBlobPtr {
public:
    // increment and decrement
    StrBlobPtr operator++(int);    // postfix operators
    StrBlobPtr operator--(int);
    // other members as before
};
```

---

<a id="id9"></a>
## ✅ 知识点9: 最佳实践：后缀操作符应返回旧值（值返回）

**理论**
* **核心主旨总结**：**为了与内置操作符保持一致，后缀操作符应返回对象的旧值（即递增或递减前的值）**。该旧值作为**值（而非引用）**返回。
* **重点突出**：这是后缀操作符与前缀操作符的另一个关键区别：前缀返回引用，后缀返回原状态的副本。

---

<a id="id10"></a>
## ✅ 知识点10: 后缀递增的实现

**理论**
* **核心主旨总结**：后缀版本需要先保存对象的当前状态，然后调用前缀版本完成实际递增，最后返回保存的旧状态。这样，对象本身被更新，但返回的是递增前的值。
* **实现细节**：通过`++*this`调用前缀递增，由前缀操作符负责安全检查。

**教材示例代码**
```cpp
// postfix: increment/decrement the object but return the unchanged value
StrBlobPtr StrBlobPtr::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    StrBlobPtr ret = *this;    // save the current value
    ++*this;    // advance one element; prefix ++ checks the increment
    return ret;    // return the saved state
}
```

---

<a id="id11"></a>
## ✅ 知识点11: 后缀递减的实现

**理论**
* **核心主旨总结**：后缀递减的实现方式与后缀递增类似：先保存当前状态，然后通过`--*this`调用前缀递减，最后返回保存的旧值。

**教材示例代码**
```cpp
StrBlobPtr StrBlobPtr::operator--(int)
{
    // no check needed here; the call to prefix decrement will do the check
    StrBlobPtr ret = *this;    // save the current value
    --*this;    // move backward one element; prefix -- checks the decrement
    return ret;    // return the saved state
}
```

---

<a id="id12"></a>
## ✅ 知识点12: 后缀操作符如何工作（调用前缀版本）

**理论**
* **核心主旨总结**：每个后缀操作符都调用其对应的前缀版本来完成实际工作。例如，后缀递增执行`++*this`，这会调用前缀递增操作符。前缀操作符检查递增是否安全，若安全则递增`curr`，否则抛出异常。假设`check`不抛出异常，后缀函数返回存储在`ret`中的副本。因此，函数返回后，对象本身已经向前移动，但返回的值反映了原始的、未递增的状态。
* **重点突出**：这种设计避免了代码重复，并确保了安全检查的一致性。

---

<a id="id13"></a>
## ✅ 知识点13: 注意：int参数未使用，不命名

**理论**
* **核心主旨总结**：后缀操作符的`int`参数并不使用，因此在定义时通常不给出参数名（只写类型`int`），以表明该参数是有意省略名称的。

**注意点**
* 📋 **命名惯例**：在函数定义中，如果不使用某个参数，可以省略其名称，仅保留类型，这样可以避免编译器产生“未使用参数”的警告。

---

<a id="id14"></a>
## ✅ 知识点14: 显式调用后缀操作符

**理论**
* **核心主旨总结**：与普通操作符一样，我们可以通过函数调用的方式显式调用重载的操作符。如果想调用后缀版本，必须为那个额外的`int`参数传递一个值（通常是0），以告诉编译器使用后缀版本。

---

<a id="id15"></a>
## ✅ 知识点15: 显式调用后缀操作符的代码示例

**理论**
* **核心主旨总结**：下面的代码展示了如何显式调用`StrBlobPtr`的后缀和前缀操作符。

**教材示例代码**
```cpp
StrBlobPtr p(a1); // p points to the vector inside a1
p.operator++(0);    // call postfix operator++
p.operator++();     // call prefix operator++
```

**注意点**
* 📋 **参数意义**：`p.operator++(0)`中的`0`仅用于区分版本，实际值通常被忽略。

---

<a id="id16"></a>
## ✅ 知识点16: 显式调用时传递的值通常忽略

**理论**
* **核心主旨总结**：传递给后缀操作符的整数参数通常被忽略，但它是必要的，因为编译器需要依靠它来区分前缀和后缀版本。

---

## 🔑 核心要点总结

1. **定义规则**：为类定义递增/递减操作符时，**必须同时定义前缀和后缀版本**，并且通常将它们定义为成员函数。
2. **返回值差异**：
   - **前缀版本**返回**指向递增/递减后对象的引用**（`StrBlobPtr&`）。
   - **后缀版本**返回**递增/递减前的对象副本**（`StrBlobPtr`），并且通过一个额外的`int`参数与前缀区分。
3. **实现技巧**：后缀版本通常通过调用前缀版本来完成实际工作，这样既保证安全又避免代码重复。
4. **安全检查**：前缀递增先检查再递增，前缀递减先递减再检查，以正确处理边界条件。
5. **显式调用**：可以通过函数调用语法显式调用操作符，后缀调用必须传递一个整数参数（如`0`）。

## 📌 考试速记版

* **声明形式**：
  - 前缀：`StrBlobPtr& operator++();`
  - 后缀：`StrBlobPtr operator++(int);`
* **返回值**：
  - 前缀：返回引用（`*this`）
  - 后缀：返回原状态的副本
* **后缀实现模式**：
  ```cpp
  StrBlobPtr operator++(int) {
      StrBlobPtr ret = *this;
      ++*this;      // 调用前缀版本
      return ret;
  }
  ```
* **边界检查**：
  - 递增：`check(curr, ...); ++curr;`
  - 递减：`--curr; check(curr, ...);` （注意先递减再检查）
* **常见错误**：
  - 忘记定义后缀版本
  - 后缀返回了引用而不是值
  - 忘记在递减前先递减检查，导致边界错误
  - 混淆前缀和后缀的调用方式（显式调用时后缀需传参）

**记忆口诀**：
> 前缀引用后值返，  
> 后缀调用前缀版。  
> 递增先查后移动，  
> 递减先减后查勘。  
> 显式调用后缀时，  
> 传个整数来分辨。