# 📘 Chapter 01 - 开始 (Get Started)

> 《C++ Primer》第 1 章学习笔记导航  
> 本章涵盖：编写、编译、运行简单 C++ 程序的基础知识

---

## 📑 章节导航

### 1.1 快速上手 ⚡
编译运行、退出状态、编译器选择  
[→ 查看笔记](./note_1_1_compile_execute.md)

### 1.2 初识 I/O 💻
标准输入输出、`<<`/`>>` 运算符、命名空间  
[→ 查看笔记](./note_1_2_IO.md)

### 1.3 注释 📝
单行注释 `//`、多行注释 `/* */`、注释规范  
[→ 查看笔记](./note_1_3_comment.md)

### 1.4 控制流 🔄
`while`、`for`、`if`、读取未知数量输入、编译器错误类型  
[→ 查看笔记](./note_1_4_flow_control.md)

### 1.5 初识类 🏗️
类定义、对象创建、成员函数、文件重定向  
[→ 查看笔记](./note_1_5_class.md)

### 练习题 💪
本章所有练习代码  
[→ 查看代码](./exercises/)

---

## 🎯 知识点索引

<details>
<summary><b>🔧 编译与执行</b></summary>

- [编写并运行 C++ 程序](./note_1_1_compile_execute.md#-1-编写并运行-c-程序)
- [使用 C++ 编译器](./note_1_1_compile_execute.md#-2-使用-c-编译器)
- [程序退出状态](./note_1_1_compile_execute.md#-1-编写并运行-c-程序)
- [C++11 编译选项](./note_1_1_compile_execute.md#-2-使用-c-编译器)

</details>

<details>
<summary><b>💻 输入输出</b></summary>

- [标准 I/O 对象：cin, cout, cerr, clog](./note_1_2_IO.md#-标准输入和输出类)
- [输出运算符 `<<`](./note_1_2_IO.md#-输出运算符--的工作机制)
- [输入运算符 `>>`](./note_1_2_IO.md#️-输入运算符--的工作机制)
- [std::endl 与缓冲区刷新](./note_1_2_IO.md#-stdendl-与缓冲区刷新)
- [命名空间 std](./note_1_2_IO.md#-名称空间-如-stdcout)

</details>

<details>
<summary><b>📝 注释规范</b></summary>

- [单行注释 `//`](./note_1_3_comment.md#-单行注释-)
- [成对注释 `/* */`](./note_1_3_comment.md#-成对注释--)
- [注释不可嵌套](./note_1_3_comment.md#-注意注释成对无法嵌套)

</details>

<details>
<summary><b>🔄 控制流语句</b></summary>

- [while 循环](./note_1_4_flow_control.md#-141-while-语句)
- [for 循环](./note_1_4_flow_control.md#-142-for-语句)
- [读取未知数量输入](./note_1_4_flow_control.md#-143-读取未知数量的输入)
- [if 条件语句](./note_1_4_flow_control.md#-144-条件语句-if-statement)
- [编译器常见错误类型](./note_1_4_flow_control.md#️-编译器常见错误)
- [编码风格建议](./note_1_4_flow_control.md#-编码风格建议)

</details>

<details>
<summary><b>🏗️ 类与对象</b></summary>

- [什么是类](./note_1_5_class.md#-什么是类)
- [定义类对象](./note_1_5_class.md#-如何定义类对象)
- [Sales_item 类操作](./note_1_5_class.md#-类支持的操作以-sales_item-为例)
- [成员函数调用](./note_1_5_class.md#-什么是成员函数)
- [文件重定向](./note_1_5_class.md#-使用文件重定向redirection)

</details>

---

## 💡 核心速查

**编译运行**
```bash
g++ -std=c++11 -o prog prog.cpp   # 编译
./prog                             # 运行
echo $?                           # 查看退出状态
```

**基础 I/O**
```cpp
std::cout << "输出" << std::endl;   // 输出
std::cin >> value;                  // 输入
```

**控制流**
```cpp
while (condition) { }      // while 循环
for (init; cond; upd) { }  // for 循环
if (condition) { }         // 条件判断
```

**类基础**
```cpp
Sales_item item;           // 定义对象
item.isbn();               // 调用成员函数
```

---

## 🔗 相关链接

← [返回根目录](../README.md)  
→ [下一章：Chapter 02 - 变量和基本类型](../Chapter02_variable_type/)

---

> 🕊️ *"第一章是 C++ 旅程的起点，掌握基础，方能远行。"*
