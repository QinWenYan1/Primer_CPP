# 📊 练习批改与分析

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 9.21 | 4/5 ⭐⭐⭐⭐ | 核心概念理解正确，代码语法正确，但解释可以更完整 |
| Exercise 9.22 | 2/5 ⭐⭐ | 基本理解迭代器失效问题，但修正方案存在概念性错误 |

## 🎯 逐题详细评价

### Exercise 9.21 解释list到vector的转换

**原题：** Explain how the loop from page 345 that used the return from insert to add elements to a list would work if we inserted into a vector instead.

```cpp
list<string> lst;
auto iter = lst.begin();
while (cin >> word)
    iter = lst.insert(iter, word); // same as calling push_front
```

**你的答案：**
```cpp
vector<string> v; 
auto iter = v.begin(); 
while(cin >> word)
    iter = v.insert(iter, word); 

我们先获得最开头的vector的那个迭代器
我们就可以使用insert指定在开头这个迭代器前插入，将后面的元素依次往后移动，并返回新插入元素的迭代器。
以此类推我们就可以持续在vector里面实现push_front的效果
```

**批改结果：** ⭐⭐⭐⭐ 4/5
- **概念理解：** ✅ 理解了insert返回值的用法和如何在vector前端插入元素
- **代码质量：** ✅ 代码语法正确，但缺少必要的头文件包含和变量声明
- **逻辑完整：** ⚠️ 解释了基本思路，但未提到性能问题和vector与list的差异
- **表达清晰：** ✅ 解释基本清晰，但可以更结构化

**详细分析：**
- ✅ 正确理解了insert返回新元素迭代器的概念
- ✅ 知道如何利用insert在vector前端持续插入
- ⚠️ 未提到vector前端插入的性能问题（O(n)复杂度）
- ⚠️ 未完整解释原代码中`iter = lst.begin()`的作用
- ⚠️ 代码示例中变量`c`未定义，应为`v`

**正确答案：**
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> v;
    auto iter = v.begin();  // 对于空vector，begin()等于end()
    string word;
    
    while (cin >> word) {
        // insert在iter指向位置之前插入新元素
        // 返回指向新插入元素的迭代器
        iter = v.insert(iter, word);
        // 此时iter指向新插入的元素（现在在vector前端）
        // 后续插入会继续在前端进行，实现push_front效果
    }
    return 0;
}
```

**关键知识点：**
1. **insert返回值**：`insert`返回指向新插入元素的迭代器
2. **迭代器有效性**：vector插入元素可能导致所有迭代器失效（如果发生重分配）
3. **性能差异**：list前端插入是O(1)，vector前端插入是O(n)，因为需要移动所有后续元素
4. **空容器begin()**：对于空容器，`begin()`和`end()`返回相同的迭代器

---

### Exercise 9.22 修正vector迭代问题

**原题：** Assuming iv is a vector of ints, what is wrong with the following program? How might you correct the problem(s)?

```cpp
vector<int>::iterator iter = iv.begin(),
mid = iv.begin() + iv.size()/2;
while (iter != mid)
    if (*iter == some_val)
        iv.insert(iter, 2 * some_val);
```

**你的答案：**
```cpp
问题非常简单，就是当我们在对vector遍历的时候，其实将会有风险将vector的迭代器变得失效，因为vector容器的内存在增长，那么就有可能reallocation

为此，我们做出一下修改
vector<int>::iterator iter = iv.begin(),
mid = iv.size()/2;
int count =0; 
while (count != mid)
    if (*iter == some_val)
        auto iter = iv.insert(iter, 2 * some_val);
    ++ count;
```

**批改结果：** ⭐⭐ 2/5
- **概念理解：** ⚠️ 部分理解了迭代器失效问题，但修正方案存在严重错误
- **代码质量：** ❌ 修正后的代码有多个语法和逻辑错误
- **逻辑完整：** ❌ 未能正确识别原代码的所有问题
- **表达清晰：** ⚠️ 解释过于简单，未详细分析问题

**详细分析：**
- ✅ 识别到了迭代器失效的基本问题
- ❌ **严重错误**：将`mid`从迭代器改为整数，但仍在while条件中与整数比较
- ❌ **逻辑错误**：修正后的代码中，`iter`只在插入时更新，其他情况不会递增
- ❌ **作用域错误**：在if语句内重新声明`iter`，遮蔽了外层的`iter`
- ❌ **无限循环风险**：如果发生插入，`count`递增但`iter`可能未正确前进
- ⚠️ 未识别原代码的其他问题：缺少`iter`递增，可能导致无限循环

**问题分析：**
原代码存在三个主要问题：
1. **迭代器失效**：插入元素后，所有迭代器（包括`iter`和`mid`）都可能失效
2. **缺少迭代器递增**：没有`++iter`，当`*iter != some_val`时会无限循环
3. **逻辑错误**：插入后未更新`mid`，循环终止条件可能改变

**正确答案：**
```cpp
#include <vector>
using namespace std;

void fix_vector_problem(vector<int>& iv, int some_val) {
    // 方法1：使用索引代替迭代器（推荐）
    vector<int>::size_type i = 0;
    vector<int>::size_type mid = iv.size() / 2;
    
    while (i < mid) {
        if (iv[i] == some_val) {
            iv.insert(iv.begin() + i, 2 * some_val);
            ++i;  // 跳过新插入的元素
            ++mid; // 因为插入了一个元素，mid位置后移
        }
        ++i;
    }
    
}
```

