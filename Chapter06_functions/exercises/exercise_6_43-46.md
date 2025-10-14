# 📘 C++ Primer Exercises 6.43-6.46 完整解答

## Exercise 6.43

**题目：** Which one of the following declarations and definitions would you put in a header? In a source file? Explain why.
```cpp
(a) inline bool eq(const BigInt&, const BigInt&) {...}
(b) void putValues(int *arr, int size);
```

**解答：**

**(a) `inline bool eq(const BigInt&, const BigInt&) {...}`**
- **放置位置：头文件**
- **原因：** 内联函数的定义必须对每个使用它的翻译单元可见，编译器需要看到完整的函数体才能进行内联展开。

**(b) `void putValues(int *arr, int size);`**
- **声明放在头文件，定义放在源文件**
- **原因：** 这是普通函数声明，定义应该放在 `.cpp` 文件中以避免多重定义错误。

---

## Exercise 6.44

**题目：** Rewrite the `isShorter` function from § 6.2.2 (p. 211) to be `inline`.

**解答：**
```cpp
#include <iostream>
#include <string>

using namespace std;

// 内联版本的 isShorter 函数
inline bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

int main() {
    string str1 = "short", str2 = "longer string";
    
    cout << "Is '" << str1 << "' shorter than '" << str2 << "'? "
         << isShorter(str1, str2) << endl;  // 输出: 1 (true)
    
    cout << "Is '" << str2 << "' shorter than '" << str1 << "'? " 
         << isShorter(str2, str1) << endl;  // 输出: 0 (false)
    
    return 0;
}
```

---

## Exercise 6.45

**题目：** Review the programs you've written for the earlier exercises and decide whether they should be defined as `inline`. If so, do so. If not, explain why they should not be `inline`.

**解答：**

`isShorter` 函数**应该**定义为内联函数，原因如下：

1. **函数体简短**：只有一行返回语句，没有复杂逻辑
2. **无复杂控制流**：没有循环、递归等复杂结构
3. **调用可能频繁**：字符串比较是常见操作
4. **性能考虑**：避免函数调用开销对性能有利

虽然现代编译器会自动内联小函数，但显式加上 `inline` 关键字可以：
- 明确表达设计意图
- 确保所有编译器都考虑内联
- 提高代码可读性

---

## Exercise 6.46

**题目：** Would it be possible to define `isShorter` as a `constexpr`? If so, do so. If not, explain why not.

**解答：**

`isShorter` **不能**定义为 `constexpr` 函数，原因如下：

### 关键限制1：参数类型不是字面值类型
```cpp
const string &s1, const string &s2  // ❌ 不是字面值类型
```
- `std::string` 涉及动态内存分配
- 有非平凡的构造函数和析构函数
- 不是编译时可确定的类型

### 关键限制2：成员函数调用是运行时操作
```cpp
s1.size() < s2.size()  // ❌ 运行时操作
```
- `size()` 成员函数调用发生在运行时
- 字符串长度在运行时才能确定
- 不符合 `constexpr` 函数的编译时求值要求

### 验证代码（无法编译）：
```cpp
// 这个定义会导致编译错误
constexpr bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();  // 错误：不能在constexpr函数中调用非constexpr函数
}
```

### 替代方案（如果确实需要编译时字符串比较）：
```cpp
// 使用C++17的string_view（仍然有限制）
constexpr bool isShorter(std::string_view s1, std::string_view s2) {
    return s1.size() < s2.size();  // 在C++17中可能可行
}
```

但即使使用 `string_view`，也有其他限制，且 `std::string` 版本的 `isShorter` 绝对不能定义为 `constexpr`。

---

## 🎯 总结

- **Exercise 6.43**：理解内联函数必须在头文件中定义
- **Exercise 6.44**：正确将小函数改写为内联版本
- **Exercise 6.45**：合理判断函数是否适合内联
- **Exercise 6.46**：准确理解 `constexpr` 函数的严格限制