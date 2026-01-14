## 📊 练习批改与分析

### Exercise 11.19 显式定义multiset迭代器类型

**原题：** Define a variable that you initialize by calling begin() on the multiset named bookstore from § 11.2.2 (p. 425). Write the variable's type without using auto or decltype.

**题目上下文：**
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

using CompareIsbnFunc = bool(*)(const Sales_data&, const Sales_data&);
multiset<Sales_data, CompareIsbnFunc> bookstore(compareIsbn);
```

**你的答案：**
```cpp
multiset<Sales_data, CompareIsbnFunc>::iterator iter = bookstore.begin();
```

**批改：** ⭐⭐⭐⭐⭐ 5/5 完美答案！正确写出了multiset迭代器的完整类型

**详细分析：**
- ✅ **概念理解准确**：正确理解了multiset的迭代器类型定义
- ✅ **语法完全正确**：使用了multiset的嵌套类型`iterator`
- ✅ **类型匹配正确**：begin()返回iterator类型，与变量类型一致
- ✅ **初始化正确**：使用bookstore.begin()正确初始化变量
 
---