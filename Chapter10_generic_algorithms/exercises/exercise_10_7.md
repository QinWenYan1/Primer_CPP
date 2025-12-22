# 📘 C++ 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 10.7 | ⭐⭐⭐⭐ (4/5) | 核心问题识别准确，但缺少具体修正代码 |
| 10.8 | ⭐⭐⭐ (3/5) | 理解基本机制，但关键概念阐述不完整 |

---

## 🎯 逐题详细评价

### Exercise 10.7 程序错误分析

**原题：** Determine if there are any errors in the following programs and, if so, correct the error(s):

a. 
```cpp
vector<int> vec; list<int> lst; int i;
while (cin >> i)
    lst.push_back(i);
copy(lst.cbegin(), lst.cend(), vec.begin());
```

b.
```cpp
vector<int> vec;
vec.reserve(10); // reserve is covered in § 9.4 (p. 356)
fill_n(vec.begin(), 10, 0);
```

**你的答案：**

a中出现的问题是，他没有保证复制到的目标序列的大小至少需要等于赋值的序列，这里的vector是空的，表现未定义

b不行，reserve只是扩张的capacity, 而不是size, 即使使用了reserve, 依然没有元素可以写入，所以表现未定义

**批改结果：** ⭐⭐⭐⭐ (4/5)

**详细分析：**
- ✅ **概念理解：** 准确抓住了两个程序的核心问题——目标容器大小不足导致的未定义行为，以及`size`与`capacity`的区别
- ✅ **逻辑完整性：** 正确分析了`copy`和`fill_n`对目标容器的要求，以及`reserve`不创建元素的特性
- ⚠️ **表达清晰度：** 问题描述准确，但缺少**具体的修正方案**，原题明确要求"correct the error(s)"
- ⚠️ **代码质量：** 未提供修改后的正确代码示例，回答停留在"不能这样做"而非"应该这样做"

**正确答案：**

```cpp
// a) 修正方案：
vector<int> vec;
list<int> lst;
int i;
while (cin >> i)
    lst.push_back(i);
    
// 方法1：先调整vector大小
vec.resize(lst.size()); 
copy(lst.cbegin(), lst.cend(), vec.begin());

// 方法2（推荐）：使用插入迭代器
copy(lst.cbegin(), lst.cend(), back_inserter(vec));

// b) 修正方案：
vector<int> vec;
vec.reserve(10); // 可选：预分配内存避免重新分配

// 方法1：先调整大小
vec.resize(10);
fill_n(vec.begin(), 10, 0);

// 方法2：使用插入迭代器
fill_n(back_inserter(vec), 10, 0);

// 方法3（最简单）：直接初始化
vector<int> vec(10, 0);
```

**知识点解析：**
- **容器大小 vs 容量：** `size()`是实际元素数量，`capacity()`是无需重新分配就能容纳的元素数量。`reserve()`只影响后者
- **算法的前提条件：** 大多数标准库算法要求目标范围有足够空间，不会自动创建元素（`back_inserter`等特殊迭代器除外）
- **未定义行为：** 向未初始化的迭代器位置写入会导致内存越界，程序可能崩溃或产生不可预测结果

**改进建议：**
- 💡 回答"找出并纠正错误"类问题时，**务必提供实际可运行的修正代码**，而非仅描述问题
- 💡 推荐使用`back_inserter`等插入迭代器，它们能自动处理容器扩容，代码更简洁安全
- 💡 养成习惯：使用算法前检查目标容器是否`empty()`，或优先使用插入迭代器

---

### Exercise 10.8 back_inserter 机制分析

**原题：** We said that algorithms do not change the size of the containers over which they operate. Why doesn't the use of back_inserter invalidate this claim?

**你的答案：**
back_insert返回的是一个绑定容器的插入迭代器，每一次给这个得带起赋值的时候会调用push_back，然而并不是每个容器都支持push_back

**批改结果：** ⭐⭐⭐ (3/5)

**详细分析：**
- ✅ **基本理解：** 正确指出`back_inserter`创建插入迭代器，且赋值会调用`push_back`
- ❌ **概念理解：** **核心逻辑不完整**。未解释为什么这不违背"算法不改变容器大小"的原则
- ⚠️ **表达准确性：** "并不是每个容器都支持push_back"是事实，但**未说明这与题目有何关联**。题目问的是"为何不违背声明"，而非"back_inserter的局限性"
- ⚠️ **术语使用：** "得带起"应为"迭代器"，打字错误影响专业性

**正确答案：**
```cpp
// back_inserter不违背原则的关键在于职责分离：
// 1. 算法本身（如copy）只负责通过迭代器读写数据，不关心迭代器的行为
// 2. 迭代器适配器（back_inserter）在赋值时自动调用容器的push_back()
// 3. 真正改变容器大小的是push_back()成员函数，而非算法

copy(lst.begin(), lst.end(), back_inserter(vec));
// 等价于：
// for (auto it = lst.begin(); it != lst.end(); ++it) {
//     *back_inserter(vec) = *it; // 这里调用了vec.push_back(*it)
// }
// 算法copy只是"牵线搭桥"，实际扩容的是vec自己的成员函数
```

