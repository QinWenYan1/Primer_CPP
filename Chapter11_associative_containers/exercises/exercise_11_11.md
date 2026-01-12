## 📊 练习批改与分析

### Exercise 11.11 不使用decltype重定义bookstore

---

**原题：**
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
```

**你的答案：**
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

typedef bool compareIsbnType(const Sales_data &lhs, const Sales_data &rhs);  

multiset<Sales_data, compareIsbnType>;
```

**批改：** ⭐⭐ (2/5) 基本理解，但存在概念性错误和不完整之处

**详细分析：**
- ✅ **语法基本正确**：typedef语法使用正确，定义了函数类型的别名。
- ✅ **理解了类型别名的使用**：你意识到了可以使用typedef代替decltype。
- ⚠️ **概念理解不准确**：`compareIsbnType`是函数类型（`bool(const Sales_data&, const Sales_data&)`），但multiset的模板参数需要的是**函数指针类型**或**函数对象类型**。在C++中，函数类型不能直接作为模板参数。
- ⚠️ **代码不完整**：答案缺少了bookstore的变量名和初始化参数。
- ⚠️ **语义差异**：即使这个代码能编译，它的含义与原始代码不同。原始代码使用的是函数指针类型，而你的代码使用的是函数类型。

**正确答案：**
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

// 方法1：使用typedef定义函数指针类型
typedef bool(*CompareIsbnFunc)(const Sales_data&, const Sales_data&);
multiset<Sales_data, CompareIsbnFunc> bookstore(compareIsbn);

// 方法2：使用using声明函数指针类型（C++11）
using CompareIsbnFunc = bool(*)(const Sales_data&, const Sales_data&);
multiset<Sales_data, CompareIsbnFunc> bookstore(compareIsbn);

// 方法3：直接使用函数指针类型
multiset<Sales_data, bool(*)(const Sales_data&, const Sales_data&)> bookstore(compareIsbn);
```
