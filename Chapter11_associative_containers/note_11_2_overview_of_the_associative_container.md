# 📘 11.2. 关联容器概述 (Overview of the Associative Containers)

> 来源说明：《C++ Primer》 11.2 | 本节涵盖：关联容器的通用操作、定义、键类型要求及pair类型的介绍

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 关联容器概述*](#id1)
* [*知识点2: 定义关联容器*](#id2)
* [*知识点3: 初始化map和set*](#id3)
* [*知识点4: 初始化multimap和multiset*](#id4)
* [*知识点5: 练习标题*](#id5)
* [*知识点6: 键类型的要求*](#id6)
* [*知识点7: 有序容器的键类型要求与严格弱序*](#id7)
* [*知识点8: 使用自定义比较函数*](#id8)
* [*知识点9: 定义带自定义比较函数的容器*](#id9)
* [*知识点10: pair类型*](#id10)
* [*知识点11: 表11.2 pair的操作*](#id11)
* [*知识点12: 创建和返回pair对象的函数*](#id12)

---

<a id="id1"></a>
## ✅ 知识点1: 关联容器概述

**理论**
* **核心主旨总结**：介绍关联容器(associative containers)支持和不支持的通用容器操作。关联容器支持《C++ Primer》第9.2节（p.328）和表9.2（p.330）列出的通用容器操作。
* **不支持的操作**：
    * 不支持顺序容器(sequential container)的位置相关操作，如 `push_front` 或 `back`。因为元素是基于其**键(key)**存储的，这些操作对关联容器没有意义。
    * 不支持那些接受一个元素值和一个计数的构造函数或插入操作。
* **额外支持的操作**：
    * 关联容器提供一些顺序容器没有的操作（表11.7, p.438）和类型别名（表11.3, p.429）。
    * 无序容器(unordered containers)还提供了调整哈希性能的操作（在11.4节介绍，p.444）。
* **迭代器类型**：关联容器的迭代器是**双向迭代器(bidirectional)**。

**注意点**
* 📋 **术语提醒**：关联容器(associative containers)，顺序容器(sequential containers)，键(key)，无序容器(unordered containers)，双向迭代器(bidirectional iterator)。

---

<a id="id2"></a>
## ✅ 知识点2: 定义关联容器

**理论**
* **核心主旨总结**：介绍定义关联容器时如何指定类型，以及可用的初始化方式。
    * 定义 `map` 时，必须指出**键(key)类型**和**值(value)类型**。
    * 定义 `set` 时，只指定键类型（因为`set`没有单独的值类型）。
* **初始化方式**：
    1. **默认构造函数**：创建一个指定类型的空容器。
    2. **拷贝初始化**：作为另一个同类型容器的副本。
    3. **范围初始化**：从一个值的范围初始化，只要这些值可以转换为容器的类型。
    4. **列表初始化**：在新标准下，可以使用列表初始化。

---

<a id="id3"></a>
## ✅ 知识点3: 初始化map和set

**理论**
* **核心主旨总结**：通过具体示例展示如何初始化`map`和`set`。
* **`map`初始化**：必须提供键值对。每个键值对用花括号包裹 `{key, value}`。其中键是`pair`的第一个元素，值是第二个元素。
* **`set`初始化**：元素类型就是键类型，直接提供元素值列表即可。

**教材示例代码**
```cpp
map<string, size_t> word_count; // 空map
// 列表初始化
set<string> exclude = {"the", "but", "and", "or", "an", "a",
                       "The", "But", "And", "Or", "An", "A"};
// 三个元素：authors将姓氏映射到名字
map<string, string> authors = { {"Joyce", "James"},
                                {"Austen", "Jane"},
                                {"Dickens", "Charles"} };
```

**注意点**
* 💡 **理解技巧**：`map`的元素是`pair`，初始化时用两层花括号 `{ {key1, value1}, {key2, value2}, ... }`。
* 🔄 **知识关联**：初始值必须能转换为容器元素的类型。

---

<a id="id4"></a>
## ✅ 知识点4: 初始化multimap和multiset

**理论**
* **核心主旨总结**：解释`map`/`set`与`multimap`/`multiset`在键唯一性上的关键区别，并通过示例说明。
* **键的唯一性**：
    * **`map` 和 `set`**：键必须唯一，每个键只能有一个元素。
    * **`multimap` 和 `multiset`**：无此限制，允许多个元素拥有相同的键。
* **示例**：用包含重复元素的`vector`初始化`set`和`multiset`，`set`会自动去重，而`multiset`会保留所有副本。

**教材示例代码**
```cpp
// 定义一个包含20个元素的vector，存有两份0到9的数字
vector<int> ivec;
for (vector<int>::size_type i = 0; i != 10; ++i) {
    ivec.push_back(i);
    ivec.push_back(i); // 每个数字的重复副本
}
// iset持有ivec中的唯一元素；miset持有全部20个元素
set<int> iset(ivec.cbegin(), ivec.cend());
multiset<int> miset(ivec.cbegin(), ivec.cend());
cout << ivec.size() << endl; // 打印 20
cout << iset.size() << endl; // 打印 10
cout << miset.size() << endl; // 打印 20
```

**注意点**
* ⚠️ **重要区别**：`set`自动去重，`multiset`保留所有副本。`map`和`multimap`同理。
* 📋 **术语提醒**：multimap, multiset。

---

<a id="id5"></a>
## ✅ 知识点5: 练习标题

**理论**
* **核心主旨总结**：教材中练习题目标题的占位。根据指南，练习题的具体内容将被排除在笔记之外。
* 练习 11.5: 解释map和set的区别。何时使用它们？
* 练习 11.6: 解释set和list的区别。何时使用它们？
* 练习 11.7: 定义一个map，其键是家庭的姓氏，值是一个存储孩子名字的vector。编写代码来添加新家庭和为现有家庭添加新孩子。
* 练习 11.8: 编写一个程序，将排除词存储在一个vector而非set中。使用set有什么优势？

**注意点**
* 📋 **内容说明**：根据指南要求，此处仅保留练习标题作为原文内容的一部分，不展开详细问题。

---

<a id="id6"></a>
## ✅ 知识点6: 键类型的要求

**理论**
* **核心主旨总结**：关联容器对用作键的类型有约束。
* **有序容器 vs 无序容器**：
    * **无序容器**：对键的要求在11.4节（p.445）介绍。
    * **有序容器（map, multimap, set, multiset）**：键类型必须定义一种比较元素的方法。
* **默认比较方式**：默认情况下，库使用键类型的 `<` 运算符来比较键。
    * 对于`set`，键就是元素类型。
    * 对于`map`，键是`pair`的第一个类型。

**注意点**
* ⚠️ **重要关联**：传递给排序算法（§ 10.3.1, p.386）的可调用对象(callable object)必须满足与关联容器中键相同的要求。
* 📋 **术语提醒**：有序容器(ordered containers)，无序容器(unordered containers)，可调用对象(callable object)。

---

<a id="id7"></a>
## ✅ 知识点7: 有序容器的键类型要求与严格弱序

**理论**
* **核心主旨总结**：详细说明可以为有序容器提供自定义的比较操作以替代 `<` 运算符，但该操作必须定义在键类型上的“严格弱序(strict weak ordering)”。
* **严格弱序的性质**（可以理解为“小于”关系，但可以更复杂）：
    1. **反对称性**：两个键不能同时“小于”对方。如果k1“小于”k2，那么k2绝不能“小于”k1。
    2. **传递性**：如果k1“小于”k2，且k2“小于”k3，那么k1必须“小于”k3。
    3. **等价传递性**：如果两个键，任何一个都不“小于”另一个，则称它们“等价(equivalent)”。如果k1等价于k2，且k2等价于k3，那么k1必须等价于k3。
* **实际意义**：如果两个键等价，容器将它们视为相等。在`map`中，将只有一个元素与这些键关联，并且任一键都可用于访问对应的值。

**注意点**
* 💡 **实用建议**：在实践中，如果一个类型定义了行为正常的 `<` 运算符，就可以用作键。
* 📋 **术语提醒**：严格弱序(strict weak ordering)，等价(equivalent)。

---

<a id="id8"></a>
## ✅ 知识点8: 使用自定义比较函数

**理论**
* **核心主旨总结**：说明如何指定自定义比较操作的类型。操作类型是容器类型的一部分，必须在定义容器类型时在尖括号内提供。创建容器对象时，再将具体的比较操作作为构造函数参数传入。
* **示例背景**：不能直接定义`Sales_data`的`multiset`，因为`Sales_data`没有 `<` 运算符。但可以使用基于ISBN比较的`compareIsbn`函数。
* **比较函数示例**：`compareIsbn`函数定义了两个`Sales_data`对象之间的严格弱序。

**教材示例代码**
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}
```

**注意点**
* 🔄 **知识关联**：比较操作的类型是一种**函数指针类型(function pointer type)**。

---

<a id="id9"></a>
## ✅ 知识点9: 定义带自定义比较函数的容器

**理论**
* **核心主旨总结**：展示如何定义一个使用自定义比较函数`compareIsbn`的`multiset<Sales_data>`。
* **类型指定**：需要提供两个类型——键类型(`Sales_data`)和比较类型（指向`compareIsbn`的函数指针类型）。使用`decltype`获取函数类型，并加上`*`表示指针。
* **构造函数参数**：将函数名`compareIsbn`作为构造函数参数传入，函数名会自动转换为指针。

**教材示例代码**
```cpp
// bookstore可以有多个具有相同ISBN的交易
// bookstore中的元素将按ISBN顺序排列
multiset<Sales_data, decltype(compareIsbn)*>
    bookstore(compareIsbn);
```

**注意点**
* ⚠️ **语法细节**：使用`decltype(compareIsbn)*`来声明函数指针类型。`compareIsbn`和`&compareIsbn`作为构造函数参数效果相同。
* 📋 **术语提醒**：`decltype`， 函数指针(function pointer)。

---

<a id="id10"></a>
## ✅ 知识点10: pair类型

**理论**
* **核心主旨总结**：介绍标准库`pair`类型，它定义在`utility`头文件中。`pair`是一个模板，包含两个数据成员，类型可以不同。
* **定义与初始化**：
    * **默认构造函数**：值初始化成员。
    * **提供初始化器**：可以直接为两个成员提供初始值。
* **数据成员**：`pair`的数据成员是`public`的，分别命名为`first`和`second`。

**教材示例代码**
```cpp
pair<string, string> anon;        // 保存两个string，都为空
pair<string, size_t> word_count;  // 保存一个string和一个size_t，string为空，size_t为0
pair<string, vector<int>> line;   // 保存string和vector<int>，都为空

pair<string, string> author{"James", "Joyce"}; // 创建一个名为author的pair，用"James"和"Joyce"初始化

// 访问成员（来自单词计数程序的示例）
cout << w.first << " occurs " << w.second
     << ((w.second > 1) ? " times" : " time") << endl;
```

**注意点**
* 📋 **术语提醒**：`pair`, `first`, `second`。
* 🔄 **知识关联**：`map`的元素就是`pair`类型。

---

<a id="id11"></a>
## ✅ 知识点11: 表11.2 pair的操作

**理论**
* **核心主旨总结**：完整呈现教材中表11.2的内容，列出了`pair`支持的操作。

**教材表格内容**
| 操作 | 描述 |
| :--- | :--- |
| `pair<T1, T2> p;` | `p`是一个`pair`，其`first`和`second`成员分别类型为`T1`和`T2`，并进行值初始化。 |
| `pair<T1, T2> p(v1, v2);` | `p`是一个`pair`，其`first`和`second`成员分别用`v1`和`v2`初始化。 |
| `pair<T1, T2> p = {v1, v2};` | 等价于 `p(v1, v2)`。 |
| `make_pair(v1, v2)` | 返回一个用`v1`和`v2`初始化的`pair`。`pair`的类型从`v1`和`v2`的类型推断。 |
| `p.first` | 返回`p`的名为`first`的（public）数据成员。 |
| `p.second` | 返回`p`的名为`second`的（public）数据成员。 |
| `p1 relop p2` | 关系运算符（`<`, `<=`, `>`, `>=`）按字典序定义。例如，`p1 < p2` 为真当 `p1.first < p2.first` 或 `(!(p2.first < p1.first) && p1.second < p2.second)`。使用元素的 `<` 运算符。 |
| `p1 == p2` `p1 != p2` | 当`first`和`second`成员分别相等时，两个`pair`相等。使用元素的 `==` 运算符。 |

**注意点**
* ⚠️ **重要操作**：`make_pair`可用于方便地创建`pair`对象，编译器会自动推断类型。关系运算符按**字典序(lexicographical order)**比较。

---

<a id="id12"></a>
## ✅ 知识点12: 创建和返回pair对象的函数

**理论**
* **核心主旨总结**：展示函数如何返回`pair`对象，对比新旧标准下的写法。
* **新标准（列表初始化）**：可以直接使用花括号列表返回`pair`。
* **旧标准写法**：
    1. **显式构造**：直接调用`pair`的构造函数。
    2. **使用`make_pair`**：让编译器推断`pair`的类型。

**教材示例代码**
```cpp
// 新标准：列表初始化
pair<string, int>
process(vector<string> &v)
{
    // 处理v
    if (!v.empty())
        return {v.back(), v.back().size()}; // 列表初始化
    else
        return pair<string, int>(); // 显式构造的返回值
}

// 旧标准：显式构造
if (!v.empty())
    return pair<string, int>(v.back(), v.back().size());

// 旧标准：使用make_pair
if (!v.empty())
    return make_pair(v.back(), v.back().size());
```

**注意点**
* 🔄 **知识关联**：`make_pair`在需要编译器类型推断时非常方便，例如在泛型编程中。

---

## 🔑 核心要点总结
1. **操作支持**：关联容器支持通用容器操作，但不支持顺序容器的位置相关操作（如`push_back`），因为其元素基于键组织。
2. **键的唯一性**：`map`和`set`的键必须唯一；`multimap`和`multiset`允许多个元素拥有相同键。
3. **键类型要求**：有序容器的键类型必须定义比较方式（默认为`<`），或提供一个满足**严格弱序**的自定义比较操作。
4. **pair类型**：`pair`是包含两个`public`数据成员（`first`, `second`）的实用模板。`map`的元素就是`pair`。可使用列表初始化、构造函数或`make_pair`来创建。

## 📌 考试速记版
* **定义**：`map<Key, Value>`， `set<Key>`。`multimap`/`multiset`允许多键。
* **初始化**：`map = { {k1,v1}, {k2,v2} };` `set = {e1, e2};`
* **键比较**：有序容器键需支持 `<` 或自定义**严格弱序**比较函数。
* **自定义比较**：定义时需在模板参数中指定比较类型（如函数指针），构造时传入函数。
* **pair操作**：`p.first`, `p.second`, `make_pair(a,b)`, 关系运算符按**字典序**比较。

**记忆口诀**：关联容器键当家，`map`存对`set`存它。键若唯一定`set`，多键请用`multiset`。有序键需比大小，自定义序要记牢。`pair`成员`first`、`second`，`make_pair`推断好。