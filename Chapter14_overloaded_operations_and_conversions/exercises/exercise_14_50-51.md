# 📘 C++ 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 14.50 | ⭐⭐⭐⭐ (4/5) | 正确识别转换序列及歧义情况，概念理解清晰，但解释可更精确。 |
| 14.51 | ⭐⭐⭐⭐ (4/5) | 正确选择可行函数，理由基本正确，表述可更专业。 |

## 🎯 逐题详细评价

### 题目 14.50

**原题：**  
Exercise 14.50: Show the possible class-type conversion sequences for the initializations of ex1 and ex2. Explain whether the initializations are legal or not.

```cpp
struct LongDouble {
    LongDouble(double = 0.0);
    operator double();
    operator float();
};
LongDouble ldObj;
int ex1 = ldObj;
float ex2 = ldObj;
```

**你的答案：**
```
1. 
    `int ex1 = ldObj;` 
    这个转换路线可以是: LongDouble -> double -> int, LongDouble -> float -> int 都是类类型转换 + 算术类型转换， 优先级相同， 歧义

2. `float ex2 = ldObj;`
    这个转换路线可以是: LongDouble -> float, 没有歧义， 因为一个还需要多余的算术类型转换然而一个不需要
```

**批改结果：** ⭐⭐⭐⭐ (4/5)

- **概念理解：** ✅ 正确识别了两种可能的转换序列，并指出了 `ex1` 的歧义性和 `ex2` 的合法性。理解类类型转换后跟标准转换的规则。
- **代码质量：** （不适用，本题为概念分析）
- **逻辑完整：** ✅ 覆盖了两种情形，分析逻辑清晰。
- **表达清晰：** ⚠️ 术语使用可更精确，例如“类类型转换”通常称为“用户定义转换序列”，“优先级”在重载决议中对应“转换序列排名”。

**正确答案：**

- 对于 `int ex1 = ldObj;`：存在两个用户定义转换序列：
  1. `ldObj` 通过 `operator double()` 转换为 `double`，再通过标准转换（浮点整型转换）转换为 `int`。
  2. `ldObj` 通过 `operator float()` 转换为 `float`，再通过标准转换转换为 `int`。
  这两个转换序列的排名相同（都是“用户定义转换 → 标准转换”），导致重载决议产生歧义，因此初始化非法。

- 对于 `float ex2 = ldObj;`：只有一个最合适的转换序列：`ldObj` 通过 `operator float()` 直接转换为 `float`，无需后续标准转换。该转换是精确匹配，无歧义，因此初始化合法。


---

### 题目 14.51

**原题：**  
Exercise 14.51: Show the conversion sequences (if any) needed to call each version of calc and explain why the best viable function is selected.

```cpp
void calc(int);
void calc(LongDouble);
double dval;
calc(dval); // which calc?
```

**你的答案：**
```
这个一定是调用的`void calc(int)`, 因为在参数类型决议上， 一个是double -> int 优先度为5, 另外一个时涉及到类类型的转换优先度为6，优先级别都不一样， 一定是选择void calc(int)
```

**批改结果：** ⭐⭐⭐⭐ (4/5)

- **概念理解：** ✅ 正确判断出调用 `calc(int)`，并理解标准转换优于用户定义转换。
- **代码质量：** （不适用）
- **逻辑完整：** ✅ 答案完整，给出了理由。
- **表达清晰：** ⚠️ 用“优先度为5”和“优先度为6”来表述不够准确，C++标准中转换序列有明确的排名层次，而不是简单的数字等级。

**正确答案：**

调用 `calc(dval)` 时，编译器考虑两个可行函数：
1. `calc(int)`：需要将实参 `double` 转换为 `int`，这是一个**标准转换**（浮点整型转换）。
2. `calc(LongDouble)`：需要将实参 `double` 转换为 `LongDouble`，这可以通过 `LongDouble` 的转换构造函数 `LongDouble(double)` 实现，这是一个**用户定义转换**。

在重载决议中，标准转换的排名高于用户定义转换，因此 `calc(int)` 是更优匹配，最终被选中。

---