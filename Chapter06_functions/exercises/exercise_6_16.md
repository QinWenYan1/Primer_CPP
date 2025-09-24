## Exercise 6.16 - 您的答案：✅ **完全正确**

**Exercise 6.16:** 
The following function, although legal, is less useful than it
might be. Identify and correct the limitation on this function:

`bool is_empty(string& s) { return s.empty(); }`


```cpp
// 原函数的问题：
bool is_empty(string& s) { return s.empty(); }

// 您的分析正确：
// 1. 不能接受const string、字符串字面量等
// 2. 函数内不修改参数，应该用const

// 修正后的正确版本：
bool is_empty(const string& s) { return s.empty(); }
```

