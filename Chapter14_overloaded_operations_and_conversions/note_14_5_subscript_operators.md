# 📘 14.5. 下标运算符 (Subscript Operator)

> 来源说明：C++ Primer 5th 14.5节 | 本节涵盖：下标运算符的定义要求、返回引用、const和非const版本、StrVec示例及使用

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 下标运算符的基本概念*](#id1)
* [*知识点2: 下标运算符的成员函数要求和返回引用*](#id2)
* [*知识点3: 定义const和非const版本*](#id3)
* [*知识点4: StrVec下标运算符的定义示例*](#id4)
* [*知识点5: 下标运算符的使用示例*](#id5)

---

<a id="id1"></a>
## ✅ 知识点1: 下标运算符的基本概念

**理论**
* **核心主旨总结**：表示容器的类通常通过定义下标运算符（`operator[]`）来支持按位置访问元素。
* 该运算符使得对象可以像数组一样使用下标语法。

---

<a id="id2"></a>
## ✅ 知识点2: 下标运算符的成员函数要求和返回引用

**理论**
* **必须为成员函数**：下标运算符必须是类的成员函数, 不能是友元或普通函数。
* **通常返回引用**：为了与下标运算符的常规语义兼容，下标运算符通常返回所获取元素的引用。
  * 返回引用允许下标出现在赋值两侧，即可用于读取也可用于写入元素。
* **const对象的行为**：当应用于const对象时，下标运算符应返回`const`引用，以防止通过下标对const对象进行赋值。

**注意点**
* ⚠️ **关键限制**：下标运算符必须是成员函数，这是C++语法的硬性规定。
---

<a id="id3"></a>
## ✅ 知识点3: 最佳实践：定义`const`和非`const`版本

**理论**
* **最佳实践**：如果一个类定义了下标运算符，通常应该定义两个重载版本：
  1. 返回普通引用（`T&`）的非const成员函数。
  2. 返回`const`引用（`const T&`）的const成员函数。
* **作用**：当对象是const时，调用const版本，返回const引用，禁止通过下标修改元素；当对象是非const时，调用非const版本，返回普通引用，允许读写元素。

**注意点**
* 💡 **理解技巧**：这个模式与标准库容器（如`vector`、`array`）的行为一致，保证了const正确性。

---

<a id="id4"></a>
## ✅ 知识点4: `StrVec`下标运算符的定义示例

**理论**
* **示例类**：`StrVec`（一个自定义的类似vector的字符串容器，定义见13.5节）。
* **代码定义**：在类内声明两个重载的`operator[]`函数。
  * 非const版本返回`std::string&`，const版本返回`const std::string&`。
  * 实现均为返回底层数组元素：`elements[n]`，其中`elements`是指向首元素的指针。

**注意点**
* ⚠️ **实现细节**：这里假设`n`是有效索引，实际生产代码可能需要边界检查。

**教材示例代码**
```cpp
class StrVec {
public:
    std::string& operator[](std::size_t n)
    { return elements[n]; }
    const std::string& operator[](std::size_t n) const
    { return elements[n]; }
    // other members as in § 13.5 (p. 526)
private:
    std::string *elements;   // pointer to the first element in the array
};
```


---

<a id="id5"></a>
## ✅ 知识点5: 下标运算符的使用示例

**理论**
* **使用方式**：下标运算符的使用与`vector`或`array`的下标类似。
* **赋值行为**：由于返回引用，非const对象可以通过下标赋值；const对象的下标返回const引用，不能赋值。

**注意点**
* ⚠️ **关键区别**：`svec[0]`调用非const版本，返回`string&`，允许修改；`cvec[0]`调用const版本，返回`const string&`，禁止修改，导致编译错误。
* 💡 **理解技巧**：const对象的下标操作自动选择const重载，这是重载决议（overload resolution）的结果，保证了const对象的只读性。
* 🔄 **知识关联**：与标准库容器（如`vector<int>`）的const版本行为一致，确保接口一致性。

**教材示例代码**
```cpp
// assume svec is a StrVec
const StrVec cvec = svec;   // copy elements from svec into cvec
// if svec has any elements, run the string empty function on the first one
if (svec.size() && svec[0].empty()) {
    svec[0] = "zero";   // ok: subscript returns a reference to a string
    cvec[0] = "Zip";   // error: subscripting cvec returns a reference to const
}
```

---

## 🔑 核心要点总结
1. **下标运算符必须是成员函数**：这是语法要求，不能是友元或非成员函数。
2. **返回引用实现读写两用**：返回元素引用可使下标出现在赋值两侧，既可用于读取也可用于写入。
3. **const版本保护const对象**：同时提供const和非const版本，当对象为const时自动选择const版本，返回const引用防止意外修改。
4. **实现通常简单**：典型实现直接返回底层容器中对应位置的元素，例如`elements[n]`。
5. **与标准库容器保持一致**：自定义容器应模仿标准库的接口风格，提供一致的下标行为。

## 📌 考试速记版
* **语法规定**：`operator[]` 必须为成员函数。
* **返回类型**：
  - 非const对象：`T&`
  - const对象：`const T&`
* **重载决议**：根据对象的const属性自动选择对应版本。
* **常见错误**：忘记定义const版本，导致const对象无法使用下标，或使用时返回非const引用（如果只定义了一个版本且不是const成员）。
* **实现示例**：
  ```cpp
  T& operator[](size_t i) { return data[i]; }
  const T& operator[](size_t i) const { return data[i]; }
  ```

**记忆口诀**：下标必须为成员，返回引用两不误；const对象防修改，两个重载保平安。