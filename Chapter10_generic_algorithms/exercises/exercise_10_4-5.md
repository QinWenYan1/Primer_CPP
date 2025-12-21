# 📘 第10章 泛型算法 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 10.4 | ⭐⭐ 2/5 | 理解存在偏差，混淆了问题的关键点 |
| 10.5 | ⭐ 1/5 | 答案错误，对C风格字符串和==运算符的理解不准确 |

## 🎯 逐题详细评价

### Exercise 10.4: accumulate的类型匹配问题
**原题：** Assuming v is a vector<double>, what, if anything, is wrong with calling accumulate(v.cbegin(), v.cend(), 0)?

**你的答案：**
```
在accumulate算法中， 第三个函数不能时字面值， 因为字面值都有const性质
也就是无法叠加， 导致报错
```

**批改结果：** ⭐⭐ 2/5
- **概念理解：** 1/2 - 知道有问题但理解不准确，混淆了关键问题
- **代码质量：** 1/2 - 表述不够准确（"第三个函数"应为"第三个参数"）
- **逻辑完整：** 0/2 - 没有抓住问题的核心
- **表达清晰：** 0.5/1 - 语句可理解但有语法问题

**正确答案：**
问题不在于字面值有const性质（实际上字面值0是右值，可以用于初始化），**真正的核心问题是类型不匹配**：

```cpp
std::vector<double> v = {1.1, 2.2, 3.3};
// 问题：0是int类型，accumulate的返回值类型由第三个参数的类型决定
double sum1 = std::accumulate(v.cbegin(), v.cend(), 0);   // 错误用法
//         ↑ accumulate内部：0 + 1.1 → int(1) + 2.2 → int(3) + 3.3 → int(6)
//         最终得到int(6)，然后转换为double(6.0)，精度丢失！

// 正确用法：使用double类型的字面值
double sum2 = std::accumulate(v.cbegin(), v.cend(), 0.0); // 正确用法
//         ↑ accumulate内部：0.0 + 1.1 → 1.1 + 2.2 → 3.3 + 3.3 → 6.6
```

**详细分析：**
- ✅ **做得好的方面**：你意识到使用字面值0可能存在问题，这是对的
- ❌ **核心问题**：你混淆了问题的本质。错误不是因为"字面值有const性质无法叠加"，而是因为**类型不匹配导致的精度丢失**
- ⚠️ **表述问题**："第三个函数"应为"第三个参数"；"时"应为"是"

---


### Exercise 10.5: equal算法与C风格字符串
**原题：** In the call to equal on rosters, what would happen if both rosters held C-style strings, rather than library strings?

**你的答案：**
```
报错，因为C-style strings是不支持直接的 == 运算符的
```

**批改结果：** ⭐ 1/5
- **概念理解：** 0/2 - 完全错误，C风格字符串指针支持==运算符
- **代码质量：** 0/2 - 没有理解底层机制
- **逻辑完整：** 0/2 - 答案与实际情况相反
- **表达清晰：** 0.5/1 - 表达清晰但内容错误

**正确答案：**
```cpp
std::vector<const char*> roster1 = {"hello", "world"};
std::vector<const char*> roster2 = {"hello", "world"};
std::vector<std::string> roster3 = {"hello", "world"};

// 情况1：C风格字符串（const char*） - 不会报错，但逻辑错误！
bool result1 = std::equal(roster1.begin(), roster1.end(), roster2.begin());
// equal会比较const char*指针的值（地址），而不是字符串内容
// 即使字符串内容相同，如果地址不同（通常如此），也会返回false

// 情况2：std::string - 正确工作
bool result2 = std::equal(roster3.begin(), roster3.end(), roster3.begin());
// equal会比较std::string对象，这会调用string的==运算符比较内容
```

**详细分析：**
- ❌ **完全错误**：C风格字符串（`const char*`）**支持**`==`运算符，但比较的是指针值（地址），而不是字符串内容
- 💡 **关键区别**：问题不是"是否支持=="，而是"==的比较语义"不同：
  - `const char*`的`==`：比较指针地址
  - `std::string`的`==`：比较字符串内容
- ⚠️ **正确理解**：不会编译报错，但会产生**逻辑错误**（错误的结果）

**关键知识点：**
1. **指针比较语义**：指针的`==`比较的是地址，不是指向的内容
2. **`std::equal`的工作方式**：它对元素直接使用`==`运算符
3. **C风格字符串比较**：需要使用`strcmp()`函数比较内容
4. **类型与语义分离**：语法上支持（编译通过）≠ 语义正确（逻辑正确）

