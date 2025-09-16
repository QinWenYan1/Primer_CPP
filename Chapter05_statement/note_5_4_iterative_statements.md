# 📘 5.4 迭代语句 (Iterative Statements)

> 来源说明：C++ Primer 第5章第4节 | 本节涵盖：C++中的循环结构，包括while、for、范围for和do while语句

---

## 🧠 本节核心概念（提纲目录）
*   while循环的基本结构和使用场景
*   传统for循环的语法和执行流程
*   范围for循环的语法和限制
*   do while循环的特点和适用场景
*   循环控制变量的作用域规则

---

## ✅ 知识点 1: while 语句
**定义 / 理论**
*   `while` 语句在条件为真时重复执行目标语句
*   语法形式：`while (condition) statement`
*   条件可以是**表达式**或**已初始化的变量声明**
*   条件不能为空，如果第一次求值就为假，语句不会执行

**教材示例代码 / 过程**
```cpp
// 读取输入直到文件结束或其他输入失败
vector<int> v;
int i;
while (cin >> i)
    v.push_back(i);

// 查找第一个负元素
auto beg = v.begin();
while (beg != v.end() && *beg >= 0)
    ++beg;
if (beg == v.end())
    // 我们知道v中所有元素都大于等于零
```

**注意点**
*   ⚠️ 循环条件或循环体必须改变表达式的值，否则可能导致无限循环
*   💡 `while` 循环适用于不确定迭代次数的情况，如读取输入
*   💡 在 `while` 条件中定义和循环体中定义的变量在**每次迭代时都会创建和销毁**

---

## ✅ 知识点 2: 传统 for 语句
**定义 / 理论**
*   语法形式：`for (init-statement; condition; expression) statement`
*   执行流程：
    1. 执行初始化语句（仅一次）
    2. 检查条件，如果为假则退出循环
    3. 执行循环体
    4. 执行表达式，然后回到第2步
*   初始化语句可以是声明语句、表达式语句或空语句

**教材示例代码 / 过程**
```cpp
// 处理字符直到用完字符或遇到空白字符
for (decltype(s.size()) index = 0;
     index != s.size() && !isspace(s[index]); ++index)
    s[index] = toupper(s[index]); // 将当前字符大写

// 在for头中定义多个变量
for (decltype(v.size()) i = 0, sz = v.size(); i != sz; ++i)
    v.push_back(v[i]);
```

**注意点**
*   ⚠️ 在 `for` 头中定义的变量其作用域仅限于 `for` 循环体
*   💡 可以省略 `for` 头的任何部分（初始化、条件或表达式）
*   💡 省略条件相当于条件始终为 `true`，必须在循环体内提供退出机制

---

## ✅ 知识点 3: 范围 for 语句
**定义 / 理论**
*   语法形式：`for (declaration : expression) statement`
*   用于遍历容器或其他序列的元素
*   `expression` 必须表示一个序列（如初始化列表、数组、vector、string等）
*   循环变量应该是引用类型，以便修改序列中的元素

**教材示例代码 / 过程**
```cpp
vector<int> v = {0,1,2,3,4,5,6,7,8,9};

// 范围变量必须是引用，以便我们可以写入元素
for (auto &r : v)    // 对于v中的每个元素
    r *= 2;          // 将每个元素的值加倍
```

**注意点**
*   ⚠️ **不能使用范围 for 循环向容器添加或删除元素**，因为 `end()` 的值会被缓存
*   💡 使用 `auto` 类型说明符让编译器推断正确的类型
*   💡 范围 for 循环在底层转换为等效的传统 for 循环

---

## ✅ 知识点 4: do while 语句
**定义 / 理论**
*   语法形式：`do statement while (condition);`
*   先执行语句，然后评估条件
*   无论条件值如何，循环至少执行一次
*   条件中使用的变量必须在 `do while` 语句体外部定义

**教材示例代码 / 过程**
```cpp
string rsp; // 在条件中使用；不能在do内部定义
do {
    cout << "please enter two values: ";
    int val1 = 0, val2 = 0;
    cin >> val1 >> val2;
    cout << "The sum of " << val1 << " and " << val2
         << " = " << val1 + val2 << "\n\n"
         << "More? Enter yes or no: ";
    cin >> rsp;
} while (!rsp.empty() && rsp[0] != 'n');
```

**注意点**
*   ⚠️ `do while` 语句在条件后的括号后需要分号
*   ⚠️ 不允许在条件中定义变量，因为任何使用都会发生在变量定义之前
*   💡 `do while` 适用于至少需要执行一次循环体的情况

---

## 🔑 本节总结
1.  **while循环**：条件先于循环体检查，适用于不确定迭代次数的情况。
2.  **for循环**：提供初始化、条件和表达式三部分，适用于已知迭代次数的情况。
3.  **范围for循环**：简化容器遍历语法，但不能在循环内修改容器大小。
4.  **do while循环**：循环体先于条件检查，保证至少执行一次。
5.  **变量作用域**：在循环头中定义的变量作用域限于循环体内，每次迭代可能重新创建。

---

## 📌 考试速记版
*   **while**：`while (condition) statement` - 先检查后执行
*   **for**：`for (init; condition; expr) statement` - 四步执行流程
*   **范围for**：`for (decl : seq) statement` - 简化遍历，不能增删元素
*   **do while**：`do statement while (condition);` - 先执行后检查，至少一次
*   **作用域规则**：循环头中变量只在循环体内可见
*   **省略部分**：for头各部分都可省略，省略条件⇒无限循环
*   **口诀**："while先判后执行，for控制三步曲，范围for简遍历，do while保一次"