# 练习 5.7 解答

## 题目原文
Correct the errors in each of the following code fragments:

(a) 
```cpp
if (ival1 != ival2)
    ival1 = ival2
    else ival1 = ival2 = 0;
```

(b) 
```cpp
if (ival < minval)
    minval = ival;
    occurs = 1;
```

(c) 
```cpp
if (int ival = get_value())
    cout << "ival = " << ival << endl;
    if (!ival)
    cout << "ival = 0\n";
```

(d) 
```cpp
if (ival = 0)
    ival = get_value();
```

## 修正后的代码

### (a) 修正
```cpp
if (ival1 != ival2)
    ival1 = ival2;  // 添加分号
else 
    ival1 = ival2 = 0;
```

**问题分析**：
- 缺少分号：`ival1 = ival2` 语句缺少结束分号
- 虽然 `else` 部分语法正确，但添加换行和缩进可以提高可读性

### (b) 修正
```cpp
if (ival < minval) {
    minval = ival;
    occurs = 1;
}  // 添加花括号将两条语句组合成块
```

**问题分析**：
- 缺少花括号：根据缩进，`occurs = 1;` 应该是 `if` 语句的一部分，但没有花括号，它实际上在 `if` 语句之后执行
- 在 C++ 中，缩进不影响实际执行流程，必须使用花括号明确代码块

### (c) 修正
```cpp
int ival;
if (ival = get_value())  // 在外部声明ival，使其在后续if中可见
    cout << "ival = " << ival << endl;
if (!ival)  // 使用 !ival 而不是 ival == 0
    cout << "ival = 0\n";
```

**问题分析**：
1. 作用域问题：在 `if` 条件中声明的 `ival` 只在该 `if` 语句及其关联的 `else` 中可见
2. 第二个 `if` 语句中的 `ival` 不在作用域内，会导致编译错误
3. 使用 `!ival` 是更符合 C++ 惯用法的零值检查方式

### (d) 修正
```cpp
if (!ival)  // 使用 !ival 而不是 ival == 0 或 ival = 0
    ival = get_value();
```

**问题分析**：
1. 赋值而非比较：原代码使用赋值运算符 `=` 而不是比较运算符 `==`
2. 这会将 `0` 赋给 `ival`，然后检查 `ival` 的值（总是 `false`）
3. 使用 `!ival` 是更简洁且符合 C++ 惯用法的零值检查方式


---

## 练习 5.8 解答

**悬空else (Dangling Else)** 是指当嵌套的if语句中if比else多时，else子句与哪个if匹配的歧义问题。

在C++中，**else子句总是与最近的前一个未匹配的if匹配**。这个规则解决了悬空else问题，但也意味着缩进可能不能反映实际的执行流程。

例如：
```cpp
if (condition1)
    if (condition2)
        statement1;
else  // 这个else与内层的if匹配，而不是外层的if
    statement2;
```

为了避免悬空else问题，应该使用花括号明确指定代码块的范围：
```cpp
if (condition1) {
    if (condition2) {
        statement1;
    }
} else {
    statement2;  // 现在else明确与外层if匹配
}
```

## 关键点总结

1. **分号**：确保所有语句以分号结束
2. **花括号**：当需要执行多条语句时，必须使用花括号创建代码块
3. **变量作用域**：在 `if` 条件中声明的变量只在该 `if` 语句及其关联的 `else` 中可见
4. **赋值与比较**：注意区分赋值运算符 `=` 和比较运算符 `==`
5. **零值检查**：在 C++ 中，使用 `!variable` 检查零值比 `variable == 0` 更符合惯用法
6. **代码风格**：适当的缩进和换行可以提高代码可读性，但不影响实际执行
