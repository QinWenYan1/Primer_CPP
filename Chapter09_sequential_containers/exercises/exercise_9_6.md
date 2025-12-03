### Exercise 9.6 迭代器比较错误

**原题：** What is wrong with the following program? How might you correct it?

```cpp
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
while (iter1 < iter2) /* ... */
```

**你的答案：**
```
这是一个无限循环， iter1永远到达不了iter2, 所以有问题
```

**批改：** ⭐⭐ (2/5) 问题识别不准确，没有抓住核心错误

**详细分析：**
- ❌ **问题识别错误**：这不是无限循环问题
- ✅ **意识到代码有问题**：你正确判断出代码存在缺陷
- ⚠️ **概念理解需要加强**：对迭代器特性和比较操作理解不足
- ⚠️ **解决方案缺失**：没有提供正确的修正方法

**正确答案：**
```cpp
// 错误原因：list的迭代器不支持 < 运算符
// 正确写法：
while (iter1 != iter2) /* ... */

// 完整修正：
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
while (iter1 != iter2) {
    // 循环体
    ++iter1;
}
```

**关键知识点：**

**错误原因分析：**
- `list<int>` 的迭代器是**双向迭代器**，不支持 `<` 关系运算符
- 只有**随机访问迭代器**（如vector、deque、array的迭代器）才支持 `<` 比较
- 代码无法通过编译，是语法错误而不是逻辑错误

**迭代器类别对比：**
| 迭代器类别 | 支持的操作 | 适用容器 |
|-----------|-----------|----------|
| 双向迭代器 | `==`, `!=`, `++`, `--` | list, set, map |
| 随机访问迭代器 | `==`, `!=`, `<`, `>`, `+`, `-` | vector, deque, array |
