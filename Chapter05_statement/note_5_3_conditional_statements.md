# 📘 5.3 条件语句 (Conditional Statements)

> 来源说明：C++ Primer 第5章第3节 | 本节涵盖：C++中的if语句和switch语句，用于基于条件执行不同代码路径

---

## 🧠 本节核心概念（提纲目录）
*   if语句的基本形式和使用
*   使用if-else语句的实际示例（字母等级计算）
*   Nested if Statements（嵌套if语句）
*   Watch Your Braces（注意花括号）
*   Dangling Else（悬空else问题）
*   Controlling the Execution Path with Braces（用花括号控制执行路径）
*   switch语句的结构和执行流程
*   switch语句的操作流 (control flow within a switch)
*   Forgetting a Break Is a Common Source of Bugs（忘记break是常见错误来源）
*   The Default Label（default标签）
*   switch语句中的变量定义和作用域规则

---

## ✅ if语句的基本形式
**定义 / 理论**
*   `if`语句根据指定条件的真假有条件地执行另一条语句
*   有两种形式：带`else`分支和不带`else`分支
*   条件必须用括号括起来，可以是**表达式**或**已初始化的变量声明**
*   条件必须可转换为`bool`类型

**教材示例代码 / 过程**
```cpp
// 简单if语句
if (grade < 60)
    lettergrade = scores[0];

// if-else语句
if (grade < 60)
    lettergrade = scores[0];
else
    lettergrade = scores[(grade - 50)/10];
```

**注意点**
*   ⚠️ 条件表达式或变量必须可转换为`bool`类型
*   💡 语句部分可以是单个语句或代码块（用花括号括起来的多条语句）

---

## ✅ 使用if-else语句的实际示例
**定义 / 理论**
*   通过计算字母等级的例子展示if-else语句的实际应用
*   根据数字分数（0-100）确定对应的字母等级
*   使用vector存储可能的字母等级

**教材示例代码 / 过程**
```cpp
vector<string> scores = {"F", "D", "C", "B", "A", "A++"};

string lettergrade;
if (grade < 60)
    lettergrade = scores[0];  // 低于60分为F
else
    lettergrade = scores[(grade - 50)/10]; // 计算对应的等级下标
```

**注意点**
*   💡 使用整数除法 `(grade - 50)/10` 来将分数映射到对应的等级下标
*   💡 通过减去50来调整分数范围，因为F等级占据了0-59的较大范围

---

## ✅ Nested if Statements（嵌套if语句）
**定义 / 理论**
*   在一个if语句内部可以嵌套另一个if语句，用于处理更复杂的条件判断
*   嵌套if语句允许我们基于多个条件进行分级决策

**教材示例代码 / 过程**
```cpp
// 为通过的成绩添加加号或减号
if (grade % 10 > 7)
    lettergrade += '+';   // 以8或9结尾的成绩获得加号
else if (grade % 10 < 3)
    lettergrade += '-';   // 以0、1或2结尾的成绩获得减号

// 将上述逻辑整合到主条件中
if (grade < 60) {
    lettergrade = scores[0];
} else {
    lettergrade = scores[(grade - 50)/10];  // 获取字母等级
    if (grade != 100) {  // 如果不是A++，则添加加号或减号
        if (grade % 10 > 7)
            lettergrade += '+';
        else if (grade % 10 < 3)
            lettergrade += '-';
    }
}
```

**注意点**
*   💡 嵌套if语句可以处理多层次的条件判断
*   ⚠️ 注意嵌套if语句的缩进，保持代码清晰可读
*   ⚠️ 嵌套过深会影响代码可读性，应考虑是否可以使用其他结构（如switch或函数）替代

---

## ✅ Watch Your Braces（注意花括号）
**定义 / 理论**
*   当需要执行多条语句时，必须使用花括号 `{}` 创建代码块
*   忘记花括号是常见错误，会导致逻辑错误，因为缩进不影响实际执行

**教材示例代码 / 过程**
```cpp
// 错误示例：忘记花括号导致逻辑错误
if (grade < 60)
    lettergrade = scores[0];
else // 错误：缺少花括号
    lettergrade = scores[(grade - 50)/10];
// 尽管缩进暗示这是else的一部分，但实际上总是会执行
if (grade != 100)
    if (grade % 10 > 7)
        lettergrade += '+';
    else if (grade % 10 < 3)
        lettergrade += '-';
```

**注意点**
*   ⚠️ **严重错误**：依赖缩进而不是花括号来确定代码结构
*   💡 **最佳实践**：即使只有一条语句，也始终使用花括号
*   💡 使用花括号可以避免后续修改代码时引入错误
*   💡 推荐去使用开发环境工具去进行自动缩进

---

## ✅ Dangling Else（悬空else问题）
**定义 / 理论**
*   当嵌套的if语句中if比else多时出现的匹配歧义问题
*   C++规定：**else与最近的前一个未匹配的if匹配**
*   这是许多编程语言的共同问题，不同语言有不同解决方案

**教材示例代码 / 过程**
```cpp
// 悬空else示例 - 实际执行与缩进暗示的不同
if (grade % 10 >= 3)
    if (grade % 10 > 7)
        lettergrade += '+';
else // 这个else实际上与内层if匹配，而不是外层if
    lettergrade += '-';

// 实际执行等价于：
if (grade % 10 >= 3) {
    if (grade % 10 > 7) {
        lettergrade += '+';
    } else {
        lettergrade += '-'; // 给3-7分的成绩添加减号！
    }
}
```

**注意点**
*   ⚠️ **悬空else陷阱**：else总是与最近的前一个未匹配的if匹配
*   💡 缩进不影响else的匹配，只影响代码可读性

---

## ✅ Controlling the Execution Path with Braces（用花括号控制执行路径）
**定义 / 理论**
*   使用花括号可以明确指定else的匹配关系
*   通过将内层if语句放在花括号中，可以强制else与外层if匹配

**教材示例代码 / 过程**
```cpp
// 使用花括号强制else与外层if匹配
if (grade % 10 >= 3) {
    if (grade % 10 > 7)
        lettergrade += '+';
} else { // 花括号强制这个else与外层if匹配
    lettergrade += '-'; // 现在只为小于3分的成绩添加减号
}
```

**注意点**
*   💡 花括号不仅创建作用域，还影响else的匹配
*   💡 使用花括号可以明确编程意图，避免悬空else问题

---

## ✅ switch语句的结构

*   `switch`语句提供了一种在多个固定选项中选择的便捷方式
*   计算跟在`switch`关键字后的括号内的表达式，该表达式转换为整型
*   将表达式结果与每个`case`标签的值进行比较
*   如果匹配到`case`标签，从该标签后的第一条语句开始执行
*   使用`break`语句中断当前控制流，跳出`switch`语句
*   如果没有匹配的， 执行会进入到`switch`结构后的第一条语句

**示例代码 / 过程**
```cpp
// 统计元音字母数量的switch语句
unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
char ch;
while (cin >> ch) {
    switch (ch) {
        case 'a': ++aCnt; break;
        case 'e': ++eCnt; break;
        case 'i': ++iCnt; break;
        case 'o': ++oCnt; break;
        case 'u': ++uCnt; break;
    }
}
```

**注意点**
*   ⚠️ `case`标签必须是**整型常量表达式**
*   💡 如果没有匹配的`case`，执行会跳转到`default`标签（如果有）
*   ⚠️ 两个标签不可拥有相同的值
*   ⚠️ 一个标签不可有多个值，如 `case 1, 11, 12:`这是错误的

---

## ✅ switch语句的操作流 (control flow within a switch)
*   如果匹配到某个case标签，会将后续剩下的cases全部执行直到结束
*   去避免执行后续cases，我们需要添加`break`在下一个case前面去告诉编译器不要继续执行
*   不过在一些情况下， 我们需要这种默认的`switch`表现
*   比如有**多个cases需要分享共同行为**，这种情况下我们不需要`break`

**示例代码 / 过程**

```cpp
unsigned vowelCnt = 0;
// ...
switch (ch)
{
// any occurrence of a, e, i, o, or u 都会增加vowelcnt
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        ++vowelCnt;
        break;
}
```

**解析**
*   这样可以计算总共元音出现次数
*   由于C++是自由格式，标签不用必须出现在不同行，为了方便阅读， 我们还可以写为：

```cpp
switch (ch)
{
// alternative legal syntax
    case 'a': case 'e': case 'i': case 'o': case 'u':
        ++vowelCnt;
        break;
}
```

**注意点**
*   ⚠️ 如果cases共享一套操作， 可以考虑抹去`break`
*   ⚠️ 去除`break`的情况非常少，如果你去除了， 请加上评论解释


---

## ✅ Forgetting a Break Is a Common Source of Bugs（忘记break是常见错误来源）
**定义 / 理论**
*   在switch语句中，匹配到一个case后会继续执行后续的所有case，除非遇到break
*   忘记写break语句是switch语句中最常见的错误之一
*   这种错误通常很难发现，因为代码看起来是正确的

**教材示例代码 / 过程**
```cpp
// 错误示例：忘记break导致意外贯穿
switch (ch) {
    case 'a': ++aCnt;  // 错误：应该有break
    case 'e': ++eCnt;  // 错误：应该有break
    case 'i': ++iCnt;  // 错误：应该有break
    case 'o': ++oCnt;  // 错误：应该有break
    case 'u': ++uCnt; break;
}

// 当ch为'e'时，会执行eCnt、iCnt、oCnt、uCnt都加1！
```

**注意点**
*   ⚠️ **常见误解**：认为只有匹配的case语句会被执行
*   💡 **最佳实践**：即使最后一个case也要写break，方便以后添加新case
*   💡 故意省略break时，必须添加注释说明原因

---

## ✅ The Default Label（default标签）

*   `default`标签处理没有`case`标签匹配`switch`表达式值的情况
*   即使`default` case没有工作要做，定义空的`default`部分也是有用的
*   标签不能单独存在，必须后面跟语句或另一个case标签

**教材示例代码 / 过程**
```cpp
// 使用default标签处理非元音字母
switch (ch) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        ++vowelCnt;
        break;
    default:
        ++otherCnt;  // 处理所有非元音字母
        break;
}

// 空的default部分 - 表明考虑了这种情况但不需要操作
switch (ch) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        ++vowelCnt;
        break;
    default:
        ; // 空语句，表示考虑了default情况
}
```

**注意点**
*   💡 **最佳实践**：即使没有工作要做，也应该包含default标签
*   💡 空的default部分向后续读者表明这种情况已被考虑
*   ⚠️ 如果default case没有操作，default标签后必须跟空语句或空块

---

## ✅ switch语句中的变量定义
**定义 / 理论**
*   在`switch`内部，执行可以跨`case`标签跳转
*   如果跳过的代码包括变量定义，特别是带有初始化器的变量，会出现问题
*   C++ 禁止在 `switch` 语句中跳过带初始化的变量定义，否则会造成变量处于作用域中却没初始化的危险情况。

**教材示例代码 / 过程**
```cpp
// 错误示例：控制流可能绕过初始化
case true:
    string file_name; // 错误：控制绕过隐式初始化的变量
    int ival = 0;     // 错误：控制绕过显式初始化的变量
    int jval;         // 正确：因为jval未初始化
    break;
case false:
    jval = next_num(); // 正确：给jval赋值
    if (file_name.empty()) // file_name在作用域内但未初始化
    // ...

// 正确做法：将变量定义在块内
case true:
    {
        // 正确：语句块内的声明语句
        string file_name = get_file_name();
        // ...
    }
    break;
```

**解析**
*   在 C++ 里，`switch` 语句只有一层语句块作用域，而不是每个 `case` 单独一个作用域
*   一旦编译器看到 `int jval`, `string file_name`, `int ival = 0`;就认为从这一行到整个 `switch` 语句块结束， 他们都在作用域里。
*   所以 `case false` 里面能看到这些变量
*   因此，编译器为了**防范可能的变量初始化被跳过**如`int ival = 0`会报错只要有任何有初始化的变量定义被跳过





**注意点**
*   ⚠️ 不允许跳过带有初始化器的变量定义
*   💡 如果需要为特定case定义和初始化变量，可以在块内定义，确保变量在后续标签点超出作用域

---

## 🔑 本节总结
1.  **if语句**根据条件真假选择执行路径，有简单if和if-else两种形式。
2.  **实际应用**：if-else语句常用于多条件判断场景，如成绩等级计算。
3.  **嵌套if语句**：允许基于多个条件进行分级决策，但要注意避免过度嵌套。
4.  **花括号重要性**：必须使用花括号明确代码块结构，避免依赖缩进导致的逻辑错误。
5.  **悬空else**问题通过"else与最近未匹配的if匹配"规则解决，使用花括号可以明确匹配关系。
6.  **switch语句**基于整型表达式值选择执行路径，case标签必须是整型常量表达式。
7.  **贯穿行为**是switch的默认特性，需要使用break语句显式中断，忘记break是常见错误来源。
8.  **default标签**处理没有case匹配的情况，即使没有操作也应该考虑包含default case。
9.  **变量定义**在switch中受到限制，不能跳过带初始化的变量定义，可以通过块作用域解决。

---

## 📌 考试速记版
*   **if语句**：`if (condition) statement` 或 `if (condition) statement else statement2`
*   **成绩计算**：使用if-else实现分数到等级的映射
*   **嵌套if**：用于多层次条件判断，注意避免过度嵌套
*   **花括号规则**：多条语句必须用花括号，单条语句也推荐使用
*   **悬空else**：else总是与最近的前一个未匹配的if匹配
*   **switch结构**：`switch (expr) { case value: statements; break; default: statements; }`
*   **case标签**：必须是整型常量表达式，不能有重复值
*   **贯穿行为**：匹配case后继续执行后续case，除非遇到break
*   **default标签**：处理无匹配case的情况，应始终包含
*   **变量定义**：不能跳过带初始化的变量定义，使用块作用域限制变量可见性
*   **口诀**："if看条件，switch看整值；花括号定范围，else配最近if；case需常量break防贯穿，default不能少"
