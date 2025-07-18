# 📘 1.4 Section — 控制流（Flow of Control）

> 本节讲解 C++ 中顺序执行之外的控制流语句，包括 `while` 循环、`for` 循环和读取未知数量输入的方法。

---

## 🧠 本节核心概念

- ✦ 顺序执行：程序默认从上到下执行语句
- ✦ `while` 语句：当条件为真时重复执行代码块
- ✦ `for` 语句：常用于计数循环，是 `while` 的简化形式
- ✦ 利用流条件读取未知数量的输入
- ✦ 条件语句 if Statement
- ✦ 编译器常见错误
- ✦ 编码风格建议

---

## 🔁 1.4.1 while 语句

```cpp
int sum = 0, val = 1;
while (val <= 10) {
    sum += val;
    ++val;
}
```

- `while` 根据布尔条件判断是否执行循环体。
- 只要 **条件(condition)** 为真，循环体就会不断执行。
- 条件就是一种产出真或者假结果的一种表达式。
- 示例中输出从 1 到 10 的累加和。

📌 使用 `+=` 是复合赋值操作，功能等价于 `sum = sum + val`

---

## 🔂 1.4.2 for 语句

```cpp
int sum = 0;
for (int val = 1; val <= 10; ++val)
    sum += val;
```

- `for` 语句由三部分组成：初始化、条件判断、更新表达式。
- 用于已知循环次数的场景，更加简洁。
- `val` 只在 `for` 循环体内有效。
- `++val` 在 `for`主题执行完以后再执行，请注意这一点。

🧾 执行顺序：初始化 → 条件判断 → 循环体 → 更新 → 重复判断

---

## 📥 1.4.3 读取未知数量的输入

```cpp
int sum = 0, value = 0;
while (std::cin >> value)
    sum += value;
```

- `std::cin >> value` 的结果可以作为条件判断。这个表达式返回`std::cin`，因此，`while` 检查`std::cin` 。当我们用 `istream` 为条件时，我们其实就是在检查输入流的状态。
- 当输入流有效（非 EOF 且无错误）时返回 true。
- 可用于读取任意多的输入，直到文件结束（EOF）或遇到无效输入。

📌 在 Windows 中按 `Ctrl + Z`，Unix/Linux/Mac 用 `Ctrl + D` 输入 EOF

---

## 📗 1.4.4 条件语句 if Statement

> C++ 中的 `if` 语句用于判断条件是否成立，配合循环可实现更复杂的逻辑控制。本节通过一个例子说明如何统计连续数字出现的次数。

```cpp
#include <iostream>
int main() {
    int currVal = 0, val = 0;
    if (std::cin >> currVal) {
        int cnt = 1;
        while (std::cin >> val) {
            if (val == currVal) {
                ++cnt;
            } else {
                std::cout << currVal << " occurs " << cnt << " times" << std::endl;
                currVal = val;
                cnt = 1;
            }
        }
        std::cout << currVal << " occurs " << cnt << " times" << std::endl;
    }
    return 0;
}
```

📥 输入示例：
```
42 42 42 42 42 55 55 62 100 100 100
```
📤 输出结果：
```
42 occurs 5 times
55 occurs 2 times
62 occurs 1 times
100 occurs 3 times
```

📌 说明：
- `if (std::cin >> currVal)` 确保有初始值
- `while` 读取后续输入，统计连续值
- 每当遇到新值时输出上一个值的统计结果
- 最后输出最后一个值的统计

🔸 提示：判断语句中常见错误是误用 `=` 赋值代替 `==` 判断。

---

## ⚠️ 编译器常见错误

### ✘ 语法错误（Syntax errors）
- 括号、分号、引号、拼写错误等

### ✘ 类型错误（Type errors）
- 将字符串传给期望整数的函数

### ✘ 声明错误（Declaration errors）
- 使用未声明的变量
- 忘记加 `std::`

🔁 **建议做法：** 每改完一小处就重新编译一次，形成 `edit-compile-debug` 循环

---

## 💡 编码风格建议

> 🌟 **缩进与格式化习惯对可读性非常重要**

- C++ 的语法对换行、缩进无要求，但良好风格可读性高
- 推荐做法：
  - 保持代码缩进一致
  - 大括号位置保持统一
  - 复杂表达式按操作符对齐

🛠 建议：选择一种风格并保持一致，阅读、调试更轻松。

---

📚 **小结：**
- C++ 提供了灵活的控制流机制来实现复杂的程序逻辑。
- 掌握 `while`、`for`、`if` 的使用方法与嵌套逻辑
- 正确使用 `==` 判断相等，避免与 `=` 混淆
- 输入结束前别忘处理最后一项
- 注意代码格式与风格，有助于阅读与维护
