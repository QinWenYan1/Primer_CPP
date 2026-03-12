## 📘 第15章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 15.4 | ⭐⭐⭐ (3/5) | 基本判断正确，但对声明语法细节掌握不足 |

---

## 🎯 逐题详细评价

### Exercise 15.4: 以下声明哪些是错误的？解释原因。

**原题：** Which of the following declarations, if any, are incorrect? Explain why.

**(a)** `class Derived : public Derived { ... };`  
**(b)** `class Derived : private Base { ... };`  
**(c)** `class Derived : public Base;`

**你的答案：**
> (a) 不行错误， 不能从自己的类派生  
> (b) 可以  
> (c) 可以

**批改结果：** ⭐⭐⭐ (3/5)

**详细分析：**
- ✅ **(a) 正确判断**：准确识别出类不能从自身派生，这是循环继承，会导致编译错误
- ✅ **(b) 正确判断**：private继承是合法的继承方式，只是继承的访问级别为private
- ❌ **(c) 错误判断**：声明 `class Derived : public Base;` 是**错误的**，这是本题的陷阱所在
- ⚠️ **解释不够深入**：对(a)和(b)仅给出结论，缺乏语法层面的解释；对(c)的判断失误源于对类声明语法规则的掌握不够精确

**正确答案解析：**

```cpp
// (a) 错误：类不能从自身派生
class Derived : public Derived { /*...*/ };
// 编译错误：循环继承（circular inheritance）
// 原因：Derived作为基类时必须是完整定义的类，而此处Derived正在定义中

// (b) 正确：private继承是合法的
class Derived : private Base { /*...*/ };
// 这是完全有效的声明，表示Base的public成员在Derived中变为private
// 注意：不同于"protected/private成员"，这是继承访问控制

// (c) 错误：带继承列表的类声明必须同时提供类体
class Derived : public Base;
// 编译错误：如果类声明包含基类列表（: public Base），
// 它必须是完整定义（包含{...}类体），而不能是分号结束的前向声明
// 正确的前向声明应该是：class Derived;
```

**关键知识点：**

1. **循环继承禁止**：C++禁止类从自身派生（直接 or 间接），因为基类必须是完全定义的类型

2. **继承访问控制**：`public`/`protected`/`private`继承都是合法的，只是改变基类成员在派生类中的访问级别：
   - `public`继承：is-a关系，接口继承
   - `private`继承：has-a实现，实现继承（Derived只能用Base功能，不暴露接口）
   - `protected`继承：用于派生类的派生类还能访问基类接口

3. **类声明语法规则**（重点！）：
   - **前向声明**：`class Derived;` —— 只能有类名，不能有继承列表，不能有类体
   - **完整定义**：`class Derived : public Base { /*成员*/ };` —— 如果有继承列表，必须有类体



---
