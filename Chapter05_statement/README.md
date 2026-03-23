# 📘 Chapter 05 - 语句 (Statements)

> 《C++ Primer》第 5 章学习笔记导航  
> 本章涵盖：C++ 语句结构、控制流、异常处理

---

## 📑 章节导航

### 5.1 简单语句 📝
表达式语句、空语句、复合语句  
[→ 查看笔记](./note_5_1_simple_statements.md)

### 5.2 语句作用域 🎯
块作用域、变量生命周期  
[→ 查看笔记](./note_5_2_statement_scope.md)

### 5.3 条件语句 ❓
if 语句、switch 语句、条件判断最佳实践  
[→ 查看笔记](./note_5_3_conditional_statements.md)

### 5.4 迭代语句 🔄
while、for、do-while 循环与范围 for 语句  
[→ 查看笔记](./note_5_4_iterative_statements.md)

### 5.5 跳转语句 ⤴️
break、continue、goto、return 语句  
[→ 查看笔记](./note_5_5_jump_statements.md)

### 5.6 异常处理 ⚠️
try-catch、throw、异常类与 noexcept  
[→ 查看笔记](./note_5_6_blocks_exception_handling.md)

### 章节总结 📝
第 5 章核心概念速查表  
[→ 查看总结](./note_5_chapter_summary.md)

### 练习题 💪
本章所有练习代码  
[→ 查看代码](./exercises/)

---

## 🎯 知识点索引

<details>
<summary><b>📝 简单语句</b></summary>

- [表达式语句](./note_5_1_simple_statements.md)
- [空语句](./note_5_1_simple_statements.md)
- [复合语句（块）](./note_5_1_simple_statements.md)

</details>

<details>
<summary><b>🎯 语句作用域</b></summary>

- [块作用域](./note_5_2_statement_scope.md)
- [变量可见性](./note_5_2_statement_scope.md)
- [生命周期管理](./note_5_2_statement_scope.md)

</details>

<details>
<summary><b>❓ 条件语句</b></summary>

- [if 语句](./note_5_3_conditional_statements.md)
- [if-else 链](./note_5_3_conditional_statements.md)
- [switch 语句](./note_5_3_conditional_statements.md)
- [case 标签与 break](./note_5_3_conditional_statements.md)
- [default 标签](./note_5_3_conditional_statements.md)

</details>

<details>
<summary><b>🔄 迭代语句</b></summary>

- [while 循环](./note_5_4_iterative_statements.md)
- [for 循环](./note_5_4_iterative_statements.md)
- [范围 for 循环](./note_5_4_iterative_statements.md)
- [do-while 循环](./note_5_4_iterative_statements.md)
- [循环控制技巧](./note_5_4_iterative_statements.md)

</details>

<details>
<summary><b>⤴️ 跳转语句</b></summary>

- [break 语句](./note_5_5_jump_statements.md)
- [continue 语句](./note_5_5_jump_statements.md)
- [goto 语句](./note_5_5_jump_statements.md)
- [return 语句](./note_5_5_jump_statements.md)

</details>

<details>
<summary><b>⚠️ 异常处理</b></summary>

- [throw 表达式](./note_5_6_blocks_exception_handling.md)
- [try 语句块](./note_5_6_blocks_exception_handling.md)
- [catch 子句](./note_5_6_blocks_exception_handling.md)
- [标准异常类](./note_5_6_blocks_exception_handling.md)
- [noexcept 说明符](./note_5_6_blocks_exception_handling.md)

</details>

---

## 💡 核心速查

**条件语句**
```cpp
// if-else
if (condition) {
    // statements
} else if (other_condition) {
    // statements
} else {
    // statements
}

// switch
switch (integral_expression) {
    case value1:
        // statements
        break;
    case value2:
        // statements
        break;
    default:
        // statements
}
```

**循环语句**
```cpp
// while
while (condition) {
    // statements
}

// for
for (init; condition; increment) {
    // statements
}

// 范围 for
for (auto &elem : container) {
    // statements
}

// do-while
do {
    // statements
} while (condition);
```

**跳转语句**
```cpp
break;      // 跳出最近一层循环或 switch
continue;   // 跳过当前迭代，进入下一次
return;     // 从函数返回
```

**异常处理**
```cpp
try {
    // 可能抛出异常的代码
    throw runtime_error("Error message");
} catch (const exception &e) {
    // 异常处理
    cerr << e.what() << endl;
}
```

---

## 🔗 相关链接

← [上一章：第 4 章 - 表达式](../Chapter04_expression/README.md)  
→ [下一章：第 6 章 - 函数](../Chapter06_functions/README.md)  
↑ [返回根目录](../README.md)

---

> 🕊️ *"掌握控制流语句是编写结构化程序的基础，异常处理则是编写健壮代码的保障。"*
