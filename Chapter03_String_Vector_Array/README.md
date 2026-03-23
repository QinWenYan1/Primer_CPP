# 📘 Chapter 03 - 字符串、向量和数组 (String, Vector and Array)

> 《C++ Primer》第 3 章学习笔记导航
> 本章涵盖：标准库容器 string 与 vector 的使用，以及内置数组与迭代器

---

## 📑 章节导航

### 3.1 命名空间声明 🏷️
using 声明、命名空间作用域与最佳实践  
[→ 查看笔记](./note_3_1_namespace_declarations.md)

### 3.2 标准库 string 📜
字符串定义、操作、处理与 C 风格字符串对比  
[→ 查看笔记](./note_3_2_library_string.md)

### 3.3 vector 📊
动态数组容器、初始化、操作与内存管理  
[→ 查看笔记](./note_3_3_vector.md)

### 3.4 迭代器 🔄
迭代器概念、使用、类型与迭代器运算  
[→ 查看笔记](./note_3_4_iterator.md)

### 3.5 数组 📋
内置数组定义、初始化、多维数组与指针关系  
[→ 查看笔记](./note_3_5_array.md)

### 3.6 多维数组 🔢
多维数组定义、遍历、指针与数组名的关系  
[→ 查看笔记](./note_3_6_multidimensional_array.md)

### 章节总结 📝
第 3 章核心概念速查表  
[→ 查看总结](./note_3_chapter_summary.md)

### 练习题 💪
本章所有练习代码  
[→ 查看代码](./exercises/)

---

## 🎯 知识点索引

<details>
<summary><b>🏷️ 命名空间声明</b></summary>

- [using 声明](./note_3_1_namespace_declarations.md)
- [命名空间作用域](./note_3_1_namespace_declarations.md)
- [using 编译指令](./note_3_1_namespace_declarations.md)
- [最佳实践建议](./note_3_1_namespace_declarations.md)

</details>

<details>
<summary><b>📜 标准库 string</b></summary>

- [string 定义与初始化](./note_3_2_library_string.md)
- [string 操作](./note_3_2_library_string.md)
- [读写 string](./note_3_2_library_string.md)
- [处理字符](./note_3_2_library_string.md)
- [C 风格字符串转换](./note_3_2_library_string.md)
- [string 比较与拼接](./note_3_2_library_string.md)

</details>

<details>
<summary><b>📊 vector</b></summary>

- [vector 定义与初始化](./note_3_3_vector.md)
- [向 vector 添加元素](./note_3_3_vector.md)
- [vector 其他操作](./note_3_3_vector.md)
- [迭代器失效问题](./note_3_3_vector.md)
- [vector 内存管理](./note_3_3_vector.md)

</details>

<details>
<summary><b>🔄 迭代器</b></summary>

- [迭代器基础](./note_3_4_iterator.md)
- [迭代器运算](./note_3_4_iterator.md)
- [迭代器范围](./note_3_4_iterator.md)
- [begin 与 end](./note_3_4_iterator.md)
- [const_iterator](./note_3_4_iterator.md)

</details>

<details>
<summary><b>📋 数组</b></summary>

- [数组定义与初始化](./note_3_5_array.md)
- [访问数组元素](./note_3_5_array.md)
- [指针与数组](./note_3_5_array.md)
- [数组名与指针区别](./note_3_5_array.md)
- [数组形参](./note_3_5_array.md)

</details>

<details>
<summary><b>🔢 多维数组</b></summary>

- [多维数组定义](./note_3_6_multidimensional_array.md)
- [多维数组初始化](./note_3_6_multidimensional_array.md)
- [多维数组遍历](./note_3_6_multidimensional_array.md)
- [指针与多维数组](./note_3_6_multidimensional_array.md)
- [类型别名简化](./note_3_6_multidimensional_array.md)

</details>

---

## 💡 核心速查

**string 基础操作**
```cpp
#include <string>
using std::string;

string s1;                    // 空字符串
string s2 = "hello";          // 初始化
string s3(s2);                // 拷贝构造
string s4 = s2 + " world";    // 拼接
s4.size();                    // 获取长度
s4.empty();                   // 判断是否为空
s4[n];                        // 访问第 n 个字符
getline(cin, s);              // 读取一行
```

**vector 基础操作**
```cpp
#include <vector>
using std::vector;

vector<int> v1;              // 空 vector
vector<int> v2(10);          // 10 个元素，值初始化
vector<int> v3(10, 1);       // 10 个 1
vector<int> v4 = {1,2,3};    // 列表初始化

v.push_back(42);              // 添加元素
v.size();                     // 元素个数
v.empty();                    // 是否为空
v[n];                         // 访问第 n 个元素
```

**迭代器使用**
```cpp
// 使用迭代器遍历
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it;              // 解引用访问元素
}

// 范围 for 循环（底层使用迭代器）
for (auto &elem : v) {
    cout << elem;
}
```

**数组与指针**
```cpp
int arr[10];                  // 定义数组
int *p = arr;                 // 数组名即首元素指针
int *end = arr + 10;          // 尾后指针

// 标准库函数 begin/end
int *beg = std::begin(arr);
int *last = std::end(arr);
```

---

## 🔗 相关链接

← [上一章：第 2 章 - 变量和基本类型](../Chapter02_variable_type/README.md)  
→ [下一章：第 4 章 - 表达式](../Chapter04_expression/README.md)  
↑ [返回根目录](../README.md)

---

> 🕊️ *"string、vector 和数组是 C++ 程序的基石，掌握它们是高效编程的关键。"*
