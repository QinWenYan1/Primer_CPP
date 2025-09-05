### ✅ Exercise 4.23 答案

**题目：** The following expression fails to compile due to operator precedence. Using Table 4.12 (p. 166), explain why it fails. How would you fix it?

```cpp
string s = "word";
string pl = s + s[s.size() - 1] == 's' ? "" : "s"; // 编译错误
```

**失败原因：**
根据运算符优先级（`+` > `==` > `?:`），表达式被解析为：
```cpp
string pl = ((s + s[s.size() - 1]) == 's') ? "" : "s";
```
执行顺序：
1. 计算 `s[s.size() - 1]` → 得到字符 `'d'`
2. 计算 `s + 'd'` → 生成新字符串 `"wordd"`
3. 尝试计算 `("wordd" == 's')` → 比较 `string` 和 `char`，类型不匹配，导致编译错误。

**修正方法：**
使用括号确保条件运算符先于加法运算：
```cpp
string pl = s + (s[s.size() - 1] == 's' ? "" : "s");
```
修正后的执行顺序：
1. 判断 `s[s.size() - 1] == 's'` → `'d' == 's'` → `false`
2. 计算条件表达式 → `false ? "" : "s"` → 结果为 `"s"`
3. 计算 `s + "s"` → `"words"`

---

### ✅ Exercise 4.24 答案

**题目：** Our program that distinguished between high pass, pass, and fail depended on the fact that the conditional operator is right associative. Describe how that operator would be evaluated if the operator were left associative.

**原代码（右结合）：**
```cpp
finalgrade = (grade > 90) ? "high pass" 
                         : (grade < 60) ? "fail" : "pass";
// 分组方式: (grade > 90) ? "high pass" : ((grade < 60) ? "fail" : "pass")
```

**如果条件运算符是左结合的：**
表达式将被分组为：
```cpp
finalgrade = ((grade > 90) ? "high pass" : (grade < 60)) ? "fail" : "pass";
```

**求值过程与后果：**
1.  首先计算内层条件表达式：`(grade > 90) ? "high pass" : (grade < 60)`
    *   此表达式两个分支类型不兼容（`const char*` 与 `bool`），可能产生编译警告或错误。
    *   如果编译器允许，其结果取决于 `grade`：
        *   若 `grade > 90`，结果为 `"high pass"`（非空指针，在条件判断中为 `true`）
        *   若 `grade <= 90`，结果为布尔值 `(grade < 60)`（`true` 或 `false`）

2.  用第一步的结果作为条件，计算整个表达式：`(第一步结果) ? "fail" : "pass"`
    *   **情况A：`grade > 90`**
        *   条件为 `"high pass"`（`true`），最终结果为 `"fail"`
        *   **灾难性错误**：高分学生被判定为不及格
    *   **情况B：`grade <= 90`**
        *   条件为 `(grade < 60)`：
            *   若 `grade < 60`（条件为 `true`），最终结果为 `"fail"`（正确）
            *   若 `grade >= 60`（条件为 `false`），最终结果为 `"pass"`（正确）

**结论：**
如果条件运算符是左结合的，不仅会产生类型安全问题，更会导致严重的逻辑错误（ specifically 将高分成绩误判为失败）。这表明**右结合性**对于正确实现多分支条件逻辑至关重要。