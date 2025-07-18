# 📘 1.5 Section — 初识类（Introducing Classes）

> 本节讲解如何在 C++ 中定义类（class），以及如何使用类创建对象、调用成员函数。

---

## 🧠 本章核心概念

- ✦ 什么是类?
- ✦ 如何定义类对象？
- ✦ 类支持的操作
- ✦ 合并两个 Sales_item 对象
- ✦ 加入判断：if 条件控制
- ✦ 什么是成员函数？

---

## 🔍 知识点详解

### ✅ 什么是类？

类是一种自定义的数据结构，
它不仅定义数据的布局，还定义可对数据执行的操作。
类是 C++ 的核心机制之一，使得我们可以像使用内置类型一样自然地使用自定义类型。

> 例：`Sales_item` 是一个类，表示图书销售的记录，包括销售数量、总收入等。

要使用一个类，我们需知道：
- 它的名字（如 `Sales_item`）
- 它在哪定义（如 `Sales_item.h`）
- 它支持哪些操作（如输入输出、加法等）

---

### ✅ 如何定义类对象？

```cpp
Sales_item item;
```
表示定义了一个 `Sales_item` 类型的对象 `item`。
类的名字本身就是类型名。

---

### ✅ 类支持的操作（以 Sales_item 为例）

- 调用 `isbn()` 成员函数获取 ISBN
- 使用 `>>` 和 `<<` 操作符读取和输出对象
- 使用 `=` 赋值操作
- 使用 `+` 进行合并（必须 ISBN 相同）
- 使用 `+=` 复合合并

> 💡 注意：这些操作是由类作者定义的，类作者决定类支持哪些操作。

---

### ✅ 示例程序：读取并输出 Sales_item

```cpp
#include <iostream>
#include "Sales_item.h"
int main() {
    Sales_item book;
    std::cin >> book;  // 输入 ISBN、数量、价格
    std::cout << book << std::endl;  // 输出结果
    return 0;
}
```
来自标准库的头文件，引用使用尖括号 `<>`。 那些不来自于标准库的头文件使用引号来引入 `""`。

输入：
```
0-201-70353-X 4 24.99
```
输出：
```
0-201-70353-X 4 99.96 24.99
```

---

### ✅ 合并两个 Sales_item 对象

```cpp
Sales_item item1, item2;
std::cin >> item1 >> item2;
std::cout << item1 + item2 << std::endl;
```

前提：两个对象的 ISBN 必须相同。

#### 📁 使用文件重定向（Redirection）

重复输入测试数据可能很繁琐，因此可以使用**文件重定向**将标准输入输出流转向文件：

```bash
$ addItems < infile > outfile
```
这条命令会将文件 `infile` 的内容作为程序的输入，程序运行结果则写入 `outfile` 文件中。

📌 注意：`<` 表示输入重定向，`>` 表示输出重定向。该技巧适用于 Unix、Linux、Windows 等操作系统的命令行环境。


---

### ✅ 加入判断：if 条件控制

```cpp
if (item1.isbn() == item2.isbn()) {
    std::cout << item1 + item2 << std::endl;
    return 0;
} else {
    std::cerr << "Data must refer to same ISBN" << std::endl;
    return -1;
}
```

📌 判断是否可以合并，否则输出错误信息。

---

### ✅ 什么是成员函数？

- `item1.isbn()` 表示调用 `item1` 对象的 `isbn` 函数。
- `.` 是 **成员访问运算符**，用于访问类中的成员（变量或函数）。
- `()` 是 **调用运算符**，表示执行函数。

> `isbn` 是不带参数的函数，返回该对象的 ISBN。

当我们写：
```cpp
item1.isbn() == item2.isbn()
```
表示比较两个对象的 ISBN 是否相同。

---

## 🕊️ 小结

- 类定义了新的数据类型，封装数据与行为
- 类对象可以像内置类型一样使用，但操作由类定义
- 成员函数通过 `对象.函数()` 调用
- 理解输入输出、加法、条件判断在类上的实现
- `Sales_item` 是一个实践类用法的好例子
