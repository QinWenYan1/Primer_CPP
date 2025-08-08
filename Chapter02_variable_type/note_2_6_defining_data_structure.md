# 📘 2.6 Section — 定义我们自己的数据结构 (Defining Our Own Data Structures)

> 本章笔记基于《C++ Primer》第五版整理，详细介绍了如何在 C++ 中定义自定义数据结构。

---

## 🧠 本章核心概念

- ✯ 数据结构的基本概念
  - 将相关数据元素组合在一起
  - 提供使用这些数据的策略
- ✯ struct 关键字定义类
  - 类体 (class body) 的基本语法
  - 数据成员 (data members) 的定义
  - 类内初始化器 (in-class initializer)
- ✯ 使用自定义数据结构
  - 直接访问数据成员
  - 点运算符 (dot operator) 的使用
- ✯ 头文件的编写和管理
  - 预处理器 (preprocessor) 介绍
  - 头文件保护 (header guards)

---

## ✅ 数据结构基础概念

**什么是数据结构？**
在最基本的层面上，数据结构就是：
- 将相关数据元素组合在一起的方式
- 使用这些数据的策略

例如，`Sales_item` 类将以下内容组合在一起：
- ISBN（书号）
- 销售册数统计
- 相关的收入数据
- 一系列操作（如 `isbn` 函数和 `>>`, `<<`, `+`, `+=` 运算符）

**C++ 中的数据类型定义**
在 C++ 中，我们通过定义**类 (class)** 来定义自己的数据类型：
- 标准库类型 `string`、`istream`、`ostream` 都是类
- `Sales_item` 也是一个类
- C++ 对类的支持非常丰富（第三部分和第四部分专门讲述类相关特性）

---

## ✅ 2.6.1 定义 Sales_data 类型

虽然我们还不能完全定义 `Sales_item` 类，但可以编写一个更具体的类来组合相同的数据元素。

### 📝 设计策略

我们的策略是：
- 用户可以直接访问数据元素
- 用户必须自己实现所需的操作

因为我们的数据结构不支持任何操作，所以将其命名为 `Sales_data` 以区别于 `Sales_item`。

### 📝 基本类定义语法

```cpp
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```

**语法要点**：
- 以 `struct` 关键字开始
- 后跟类名和类体
- 类体用花括号 `{}` 包围，形成新的作用域
- 类体内的名称在类内必须唯一，但可以重用类外定义的名称
- **类体结束的花括号后必须有分号！**

⚠️ **常见错误警告**：忘记类定义结尾的分号是新手程序员的常见错误！

### 📝 定义变量的灵活性

可以在类定义后面直接定义变量：
```cpp
struct Sales_data { /* ... */ } accum, trans, *salesptr;
// 等价于但更好的方式：
struct Sales_data { /* ... */ };
Sales_data accum, trans, *salesptr;
```

**最佳实践**：通常**不建议**在类定义中同时定义变量，这会让代码变得难以理解。

### 📝 类数据成员 (Class Data Members)

**数据成员的特点**：
- 定义类的内容
- 每个对象都有自己的数据成员副本
- 修改一个对象的数据成员不影响其他 `Sales_data` 对象

**数据成员定义方式**：
- 与普通变量定义相同：指定基础类型，后跟声明符列表
- 我们的类有三个数据成员：
  - `bookNo`：`string` 类型
  - `units_sold`：`unsigned` 类型  
  - `revenue`：`double` 类型

### 📝 类内初始化器 (In-class Initializer)

C++11 新标准允许为数据成员提供**类内初始化器**：
```cpp
unsigned units_sold = 0;    // 类内初始化器
double revenue = 0.0;       // 类内初始化器
```

**初始化规则**：
- 创建对象时，类内初始化器用来初始化数据成员
- **没有初始化器的成员被默认初始化**
- 因此 `units_sold` 和 `revenue` 会初始化为 0，`bookNo` 会初始化为空字符串

**语法限制**：
- 类内初始化器**必须用** `=` 或花括号 `{}` 形式
- **不能用圆括号**

💡 **关于 struct vs class**：
- C++ 有 `struct` 和 `class` 两个关键字定义类
- 在第 7.2 节会解释为什么这里使用 `struct`
- 在学习更多类相关特性之前，应该使用 `struct` 定义数据结构

---

## ✅ 2.6.2 使用 Sales_data 类

与 `Sales_item` 类不同，我们的 `Sales_data` 类不提供任何操作。用户需要编写所需的操作。

### 📝 程序结构示例

假设我们重写之前的程序来计算两个交易的和：

```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
int main()
{
    Sales_data data1, data2;
    // 读取 data1 和 data2 的代码
    // 检查 data1 和 data2 是否有相同 ISBN 的代码
    // 如果是，打印 data1 和 data2 的和
}
```

**重要说明**：
- 需要包含 `string` 头文件（与 `Sales_item` 版本不同）
- 因为我们的代码需要管理 `bookNo` 成员（`string` 类型）

### 📝 读取数据到 Sales_data 对象

虽然我们还没详细学习 `string` 类型，但需要了解基本操作：
- `string` 类型存储字符序列
- 支持 `>>`、`<<` 和 `==` 操作符来读取、写入和比较字符串

**读取第一个交易的代码**：
```cpp
double price = 0;   // 每本书的价格，用于计算总收入
// 读取第一个交易：ISBN、销售册数、每本书价格
std::cin >> data1.bookNo >> data1.units_sold >> price;
// 计算总收入
data1.revenue = data1.units_sold * price;
```

**关键概念**：
- 使用**点运算符 (dot operator)** 访问对象成员
- `std::cin >> data1.bookNo` 读取数据到 `data1` 的 `bookNo` 成员
- 我们的交易包含每本书的价格，但数据结构存储总收入
- 需要从价格和销售数量计算收入

**读取第二个交易**：
```cpp
// 读取第二个交易
std::cin >> data2.bookNo >> data2.units_sold >> price;
data2.revenue = data2.units_sold * price;
```

### 📝 打印两个 Sales_data 对象的和

检查交易是否为相同 ISBN，如果是则打印总和：

```cpp
if (data1.bookNo == data2.bookNo) {
    unsigned totalCnt = data1.units_sold + data2.units_sold;
    double totalRevenue = data1.revenue + data2.revenue;
    // 打印：ISBN、总销量、总收入、平均价格
    std::cout << data1.bookNo << " " << totalCnt 
              << " " << totalRevenue << " ";
    if (totalCnt != 0)
        std::cout << totalRevenue/totalCnt << std::endl;
    else
        std::cout << "(no sales)" << std::endl;
    return 0;  // 表示成功
} else {  // 交易不是同一个 ISBN
    std::cerr << "Data must refer to the same ISBN" 
              << std::endl;
    return -1; // 表示失败
}
```

**代码说明**：
- 首先比较两个对象的 `bookNo` 成员
- 如果 ISBN 相同，执行花括号内的代码
- 计算总销量和总收入
- 为了防止除零错误，检查是否有销售再计算平均价格

---

## ✅ 2.6.3 编写我们自己的头文件

### 📝 为什么需要头文件？

**类定义的限制**：
- 虽然可以在函数内定义类，但这样的类功能有限
- 类通常**不在函数内定义**
- 在函数外定义的类，在任何给定源文件中只能有一个定义
- 如果在多个文件中使用同一个类，类的定义在每个文件中必须相同

**解决方案**：
- 通常在**头文件**中定义类
- 类的头文件名通常与类名**相同**
- 例如，`string` 库类型定义在 `string` 头文件中
- 我们将在名为 `Sales_data.h` 的头文件中定义 `Sales_data` 类

### 📝 头文件的特点和要求

**头文件内容**：
- 头文件通常包含只能定义一次的实体（如类定义、`const` 和 `constexpr` 变量）

**依赖关系处理**：
- 头文件经常需要使用其他头文件的功能
- 例如，`Sales_data` 类有 `string` 成员，所以 `Sales_data.h` 必须 `#include <string>` 头文件
- 使用 `Sales_data` 的程序也需要包含 `string` 头文件来使用 `bookNo` 成员

**多重包含问题**：
- 使用 `Sales_data` 的程序会包含 `string` 头文件两次：
  1. 直接包含（为了使用 `bookNo` 成员）
  2. 间接包含（作为包含 `Sales_data.h` 的副作用）
- 头文件可能被多次包含，需要编写安全的头文件

📝 **重要提醒**：当头文件更新时，使用**该头文件的源文件必须重新编译**以获得新的或更改的声明。

### 📝 预处理器简介 (A Brief Introduction to the Preprocessor)

确保头文件多次包含安全的最常用技术依赖于**预处理器**。

**预处理器的工作原理**：
- 预处理器是 C++ 从 C 继承的程序
- **在编译器运行之前运行，改变程序的源文本**
- 我们已经使用了一个预处理器功能：`#include`
- 当预处理器看到 `#include` 时，会用指定头文件的内容替换 `#include`

### 📝 头文件保护 (Header Guards)

C++ 程序还使用预处理器定义**头文件保护**。头文件保护依赖于预处理器变量。

**预处理器变量的状态**：
- 预处理器变量有两种状态：已定义或未定义
- `#define` 指令接受一个名称并定义该名称为预处理器变量
- `#ifdef` 和 `#ifndef` 指令测试给定的预处理器变量是否已定义：
  - `#ifdef`：如果变量已定义则为真
  - `#ifndef`：如果变量未定义则为真
- 如果测试为真，则处理到匹配的 `#endif` 前为止的所有内容

**头文件保护的实现**：
```cpp
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
#endif
```

**工作机制**：
- 第一次包含 `Sales_data.h` 时，`#ifndef` 测试成功
- 预处理器处理到 `#endif` 的行，结果是定义预处理器变量 `SALES_DATA_H` 并将 `Sales_data.h` 的内容复制到程序中
- 如果稍后在同一文件中再次包含 `Sales_data.h`，`#ifndef` 指令为假
- 在它和 `#endif` 之间的行将被忽略

⚠️ **重要警告：预处理器变量名不遵守 C++ 作用域规则**。

**命名约定**：
- **全局唯一**：预处理器变量在整个程序中不能重名
- **基于类名命名**：通常用头文件中的类名来构造保护变量名
- **全大写约定**：避免与程序中的其他标识符冲突，提高可读性

🌟 **最佳实践**：
- 头文件应该有保护，即使它们（还）没有被另一个头文件包含
- 头文件保护编写简单，习惯性地定义它们就不需要决定是否需要它们

---

## 🍃 小结

### 📚 核心知识体系

**数据结构设计**：
- 将相关数据组合在一起，提供使用策略
- C++ 通过类来实现自定义数据类型
- `struct` 关键字适合简单数据聚合

**类定义要点**：
- 基本语法：`struct` + 类名 + 类体 + 分号
- 数据成员定义与普通变量相同
- 类内初始化器提供默认值
- 点运算符访问成员

**头文件管理**：
- 类定义通常放在头文件中
- 头文件保护防止多重包含
- 预处理器变量全局唯一，通常全大写

### ⚡ 关键概念精要

**struct vs class**：
- 都可以定义类，但有微妙区别
- 简单数据聚合推荐使用 `struct`
- 完整的类功能需要后续章节的知识

**成员访问**：
- 点运算符 `.` 访问对象成员
- 每个对象有自己的数据成员副本
- 修改一个对象不影响其他对象

**预处理器机制**：
- `#include` 实现文件包含
- `#ifndef`/`#define`/`#endif` 实现头文件保护
- 预处理器在编译前运行，进行文本替换

### 🛡️ 实践指导原则

**类设计建议**：
- 明确数据和操作的分离
- 合理使用类内初始化器
- 注意类定义结尾的分号

**头文件编写**：
- 总是添加头文件保护
- 包含必要的依赖头文件
- 头文件名与类名保持一致

**代码组织**：
- 头文件包含声明，源文件包含实现
- 避免在类定义中同时定义变量
- 使用有意义的预处理器变量名

这些基础知识为后续学习完整的类功能打下了坚实基础，特别是成员函数、访问控制和构造函数等高级特性。