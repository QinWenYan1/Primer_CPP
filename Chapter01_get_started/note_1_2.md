# 📘 1.2 Section — 初识 I/O

> 本节笔记基于《C++ Primer》整理，汇总了标准 I/O 类型、输入输出操作等基础知识。

---

## 🧠 本节核心概念

- ✆ 标准输入和输出类
- ✆ I/O 实际使用
  - 输出运算符 `<<` 的工作机制
  - `std::endl` 与缓冲区刷新
  - 命名空间 (如 `std::cout`)
  - 输入运算符 `>>` 的工作机制

---

## 🔍 知识点详解

### ✅ 标准输入和输出类

C++ 本身未定义任何输入或输出语句，但标准库提供了 I/O 功能。

通过 `#include <iostream>` 头文件，可以使用标准流类型 `istream`和 `ostream`。**stream** 指一串字符的读取/写入过程。

标准库定义了下列 4 个 I/O 对象：

1. `std::cin`：标准输入 (`istream`)
2. `std::cout`：标准输出 (`ostream`)
3. `std::cerr`：输出错误信息 (`ostream`)
4. `std::clog`：输出调试/日志信息 (`ostream`)

---

### ✅ I/O 实际使用

示例：两数相加

```cpp
#include <iostream>
int main() {
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1
              << " and " << v2
              << " is " << v1 + v2 << std::endl;
    return 0;
}
```

第一行 `#include <iostream>` 是引入头文件，表明使用标准输入输出功能。

---

#### 📋 输出运算符 `<<` 的工作机制

- `<<` 是流插入运算符，用于将值输出到流对象（如 `std::cout`）中
- 左操作数：输出流对象
- 右操作数：要输出的值
- 返回值：左操作数，可用于链式输出

示例：
```cpp
std::cout << "a = " << a << std::endl;
```
等价于：
```cpp
(std::cout << "a = ") << a << std::endl;
```
或
```cpp
std::cout << "a = ";
std::cout << a << std::endl;
```

---

#### 🔧 `std::endl` 与缓冲区刷新

- `std::endl`：**流操置符 (manipulator)**
- 效果：
  1. 输出换行 (\n)
  2. 刷新缓冲区，立即输出

这有助于调试时输出信息不丢失

示例：
```cpp
std::cout << "Checkpoint A" << std::endl;
```

---

#### ⚠️ 调试提示

> 如果输出未刷新，程序崩溃时输出就不会显示，导致错误评估。

---

#### 📃 名称空间 (如 `std::cout`)

- 标准库的名称都定义在 namespace `std` 中
- 我们通过 `std::cout` 和 `std::endl` 使用它们
- `::` 是 **作用域运算符 (scope operator)**，用于连接 namespace 名和其成员

在例子中，使用 `std::cout` 而不是直接写 `cout`，是因为标准库中的名字都定义在命名空间 `std` 中：

- 避免同名冲突，同一个项目或库可能重名
- 明确指明名字来自标准库

```cpp
std::cout << "Hello" << std::endl;
```

---

#### ⌨️ 输入运算符 `>>` 的工作机制

- `>>` 是流插入运算符，用于从流中读取值
- 左操作数：输入流对象（如 `std::cin`）
- 右操作数：用来接收数据的变量
- 返回值也是左操作数，支持链式输入

示例：
```cpp
std::cin >> a >> b;
```
等价于：
```cpp
(std::cin >> a) >> b;
```

