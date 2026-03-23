# 📘 Chapter 09 - 顺序容器 (Sequential Containers)

> 《C++ Primer》第 9 章学习笔记导航  
> 本章涵盖：vector、deque、list、forward_list、array、string 的使用与选择

---

## 📑 章节导航

### 9.1 顺序容器概述 📦
容器类型选择、性能特征、通用操作  
[→ 查看笔记](./note_9_1_overview_of_sequential_containers.md)

### 9.2 容器库概览 📚
容器类型成员、begin/end、容器定义与初始化  
[→ 查看笔记](./note_9_2_container_library_overview.md)

### 9.3 顺序容器操作 ➕
添加元素、访问元素、删除元素、forward_list 操作  
[→ 查看笔记](./note_9_3_sequential_container_operations.md)

### 9.4 vector 对象是如何增长的 📈
容量与大小、reserve、shrink_to_fit  
[→ 查看笔记](./note_9_4_how_a_vector_grows.md)

### 9.5 额外的 string 操作 📜
构造 string、改变 string、string 搜索、数值转换  
[→ 查看笔记](./note_9_5_additional_string_operations.md)

### 9.6 容器适配器 🔌
stack、queue、priority_queue  
[→ 查看笔记](./note_9_6_container_adapters.md)

### 章节总结 📝
第 9 章核心概念速查表  
[→ 查看总结](./note_9_chapter_summary.md)

### 练习题 💪
本章所有练习代码  
[→ 查看代码](./exercises/)

---

## 🎯 知识点索引

<details>
<summary><b>📦 顺序容器概述</b></summary>

- [顺序容器类型](./note_9_1_overview_of_sequential_containers.md)
- [vector vs list vs deque](./note_9_1_overview_of_sequential_containers.md)
- [容器选择原则](./note_9_1_overview_of_sequential_containers.md)
- [性能特征对比](./note_9_1_overview_of_sequential_containers.md)

</details>

<details>
<summary><b>📚 容器库概览</b></summary>

- [容器类型成员](./note_9_2_container_library_overview.md)
- [迭代器范围](./note_9_2_container_library_overview.md)
- [容器定义与初始化](./note_9_2_container_library_overview.md)
- [赋值与 swap](./note_9_2_container_library_overview.md)
- [容器大小操作](./note_9_2_container_library_overview.md)

</details>

<details>
<summary><b>➕ 顺序容器操作</b></summary>

- [向容器添加元素](./note_9_3_sequential_container_operations.md)
- [push_back/push_front](./note_9_3_sequential_container_operations.md)
- [insert/emplace](./note_9_3_sequential_container_operations.md)
- [访问元素 front/back/at](./note_9_3_sequential_container_operations.md)
- [删除元素 pop_back/pop_front/erase](./note_9_3_sequential_container_operations.md)
- [forward_list 特殊操作](./note_9_3_sequential_container_operations.md)

</details>

<details>
<summary><b>📈 vector 增长机制</b></summary>

- [capacity 与 size](./note_9_4_how_a_vector_grows.md)
- [reserve 预留空间](./note_9_4_how_a_vector_grows.md)
- [shrink_to_fit 收缩空间](./note_9_4_how_a_vector_grows.md)
- [重新分配策略](./note_9_4_how_a_vector_grows.md)

</details>

<details>
<summary><b>📜 string 额外操作</b></summary>

- [构造 string](./note_9_5_additional_string_operations.md)
- [substr 子串](./note_9_5_additional_string_operations.md)
- [append/replace/assign](./note_9_5_additional_string_operations.md)
- [insert/erase](./note_9_5_additional_string_operations.md)
- [字符串搜索 find/rfind/find_first_of](./note_9_5_additional_string_operations.md)
- [数值转换 to_string/stoi/stod](./note_9_5_additional_string_operations.md)

</details>

<details>
<summary><b>🔌 容器适配器</b></summary>

- [stack 栈](./note_9_6_container_adapters.md)
- [queue 队列](./note_9_6_container_adapters.md)
- [priority_queue 优先队列](./note_9_6_container_adapters.md)
- [适配器底层容器](./note_9_6_container_adapters.md)

</details>

---

## 💡 核心速查

**顺序容器选择**
```cpp
vector<T>          // 快速随机访问，尾部插入快
deque<T>           // 双端队列，首尾插入都快
list<T>            // 双向链表，任意位置插入删除快
forward_list<T>    // 单向链表，内存占用小
array<T, N>        // 固定大小数组，栈上分配
string             // 专门处理字符序列
```

**常用操作**
```cpp
// 添加元素
c.push_back(x);     // 尾部添加
c.push_front(x);    // 头部添加（list/deque）
c.insert(p, x);     // 在迭代器 p 前插入
c.emplace(p, args); // 原位构造

// 访问元素
c.front();          // 首元素引用
c.back();           // 尾元素引用
c[n];               // 下标访问（vector/array/string/deque）
c.at(n);            // 带边界检查的下标访问

// 删除元素
c.pop_back();       // 删除尾部
c.pop_front();      // 删除头部（list/deque）
c.erase(p);         // 删除迭代器指向元素
c.clear();          // 清空容器
```

**vector 容量管理**
```cpp
vector<int> v;
v.reserve(1000);        // 预留 1000 个元素空间
v.capacity();           // 当前容量（不重新分配可存储的元素数）
v.size();               // 当前元素个数
v.shrink_to_fit();      // 请求释放多余容量（C++11）
```

**string 操作**
```cpp
string s = "Hello World";

// 子串
s.substr(0, 5);         // "Hello"

// 查找
s.find("World");        // 6
s.find_first_of("aeiou"); // 1 (e)

// 数值转换
string num = "42";
int n = stoi(num);          // 42
double d = stod("3.14");    // 3.14
string str = to_string(42); // "42"
```

**容器适配器**
```cpp
#include <stack>
#include <queue>

// 栈：LIFO
stack<int> stk;
stk.push(1); stk.push(2);
int top = stk.top();  // 2
stk.pop();

// 队列：FIFO
queue<int> q;
q.push(1); q.push(2);
int front = q.front(); // 1
q.pop();

// 优先队列
priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(2);
int max = pq.top();    // 3 (最大元素)
```

---

## 🔗 相关链接

← [上一章：第 8 章 - IO 库](../Chapter08_IO_library/README.md)  
→ [下一章：第 10 章 - 泛型算法](../Chapter10_generic_algorithms/README.md)  
↑ [返回根目录](../README.md)

---

> 🕊️ *"选择合适的容器是高效编程的第一步，理解各容器的性能特征是做出正确选择的基础。"*
