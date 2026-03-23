# 📘 Chapter 08 - IO 库 (IO Library)

> 《C++ Primer》第 8 章学习笔记导航  
> 本章涵盖：标准 IO 类、文件操作、字符串流与格式化输出

---

## 📑 章节导航

### 8.1 IO 类 📥
IO 类继承体系、条件状态、缓冲区管理  
[→ 查看笔记](./note_8_1_IO_class.md)

### 8.2 文件输入输出 📁
文件流、文件模式、fstream 操作  
[→ 查看笔记](./note_8_2_file_IO.md)

### 8.3 字符串流 📜
字符串流类、字符串转换、字符串处理  
[→ 查看笔记](./note_8_3_string_stream.md)

### 章节总结 📝
第 8 章核心概念速查表  
[→ 查看总结](./note_8_chapter_summary.md)

### 练习题 💪
本章所有练习代码  
[→ 查看代码](./exercises/)

---

## 🎯 知识点索引

<details>
<summary><b>📥 IO 类</b></summary>

- [IO 类继承体系](./note_8_1_IO_class.md)
- [条件状态 good/fail/eof/bad](./note_8_1_IO_class.md)
- [清除错误状态](./note_8_1_IO_class.md)
- [缓冲区刷新](./note_8_1_IO_class.md)
- [unitbuf 与 nounitbuf](./note_8_1_IO_class.md)
- [关联输入输出流 tie](./note_8_1_IO_class.md)

</details>

<details>
<summary><b>📁 文件输入输出</b></summary>

- [fstream 类](./note_8_2_file_IO.md)
- [ifstream 与 ofstream](./note_8_2_file_IO.md)
- [文件模式 in/out/app/ate/trunc/binary](./note_8_2_file_IO.md)
- [打开文件 open](./note_8_2_file_IO.md)
- [关闭文件 close](./note_8_2_file_IO.md)
- [自动构造与析构](./note_8_2_file_IO.md)

</details>

<details>
<summary><b>📜 字符串流</b></summary>

- [stringstream 类](./note_8_3_string_stream.md)
- [istringstream 与 ostringstream](./note_8_3_string_stream.md)
- [字符串到数值转换](./note_8_3_string_stream.md)
- [格式化字符串输出](./note_8_3_string_stream.md)
- [使用字符串流处理数据](./note_8_3_string_stream.md)

</details>

---

## 💡 核心速查

**标准 IO 类继承**
```cpp
ios_base
    └── ios
         ├── istream  ─── ifstream, istringstream
         ├── ostream  ─── ofstream, ostringstream
         └── iostream ─── fstream, stringstream
```

**条件状态检查**
```cpp
// 检查流状态
if (cin) { /* OK */ }
if (cin.good()) { /* 无错误 */ }
if (cin.eof()) { /* 遇到文件尾 */ }
if (cin.fail()) { /* 逻辑错误 */ }
if (cin.bad()) { /* 系统级错误 */ }

// 清除错误
cin.clear();           // 复位所有条件状态
cin.clear(cin.rdstate() & ~cin.failbit);  // 清除特定状态
```

**文件操作**
```cpp
#include <fstream>

// 读文件
ifstream infile("data.txt");
if (infile) {  // 检查是否成功打开
    string line;
    while (getline(infile, line)) {
        // 处理每一行
    }
}

// 写文件
ofstream outfile("output.txt");
outfile << "Hello, World!" << endl;

// 追加模式
ofstream appendfile("log.txt", ios::app);
```

**文件模式**
```cpp
// 文件模式标志
ios::in      // 读方式打开
ios::out     // 写方式打开
ios::app     // 追加到文件尾
ios::ate     // 打开后定位到文件尾
ios::trunc   // 截断文件
ios::binary  // 二进制模式

// 组合使用
ofstream file("data.bin", ios::out | ios::binary | ios::trunc);
```

**字符串流**
```cpp
#include <sstream>

// 字符串到数值转换
string s = "42 3.14";
istringstream iss(s);
int i; double d;
iss >> i >> d;  // i = 42, d = 3.14

// 数值到字符串转换
ostringstream oss;
oss << "The answer is " << 42;
string result = oss.str();

// 处理行数据
string line = "John 25 85.5";
istringstream record(line);
string name; int age; double score;
record >> name >> age >> score;
```

---

## 🔗 相关链接

← [上一章：第 7 章 - 类](../Chapter07_classes/README.md)  
→ [下一章：第 9 章 - 顺序容器](../Chapter09_sequential_containers/README.md)  
↑ [返回根目录](../README.md)

---

> 🕊️ *"IO 库是程序与外部世界交互的桥梁，掌握文件与字符串流处理是数据操作的基础。"*
