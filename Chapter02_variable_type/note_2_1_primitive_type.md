# 📘 2.1 Section — 原始内置类型 (Primitive Built-in Types)

> 本章笔记基于《C++ Primer》第五版整理，详细介绍了 C++ 中的原始类型类型系统。

---

## 🧠 本章核心概念

- ✯ 原始类型类别
- ✯ 类型全览
    - ✯ 字符
    - ✯ 浮点
    - ✯ 整型 
- ✯ 机器级表示
- ✯ 符号型 vs 无符号型
- ✯ 策略建议：如何选择类型
- ✯ 类型转换 (Type Conversions) 
  - 基本概念
  - 数学类型之间的赋值转换
  - 重要警告：避免未定义和实现定义的行为
  - 条件中的类型转换
  - 涉及无符号类型的表达式
  - 减法运算的陷阱
  - 循环中的unsigned类型问题
  - 不要混合signed和unsigned类型
- ✯ 字面值(Literals)
  - 基本概念
  - 整型和浮点型字面值
  - 浮点型字面值
  - 字符和字符串字面值
  - 字符串字面值特性
  - 多行字符串字面值
  - 转义序列 (Escape Sequences)
  - 指定字面值类型
  - 后缀组合规则
  - 布尔和指针字面值


---

### ✅ 原始类型类别

- **Arithmetic types (数学类型)**：
  - **Integral types (整型)**: 包括字符和布尔类型
    - 字符类型：`char`, `wchar_t`, `char16_t`, `char32_t`
    - 布尔类型：`bool`
    - 整数类型：`short`, `int`, `long`, `long long`
  - **Floating-point types (浮点型)**: `float`, `double`, `long double`
- **void 类型**：无关联值的特殊类型，通常用作不返回值的函数返回类型

### ✅ 类型全览

C++ 标准保证最小大小，编译器可使用更大尺寸：

| Type         | Meaning                          | Minimum Size       |
|--------------|----------------------------------|--------------------|
| `bool`       | boolean                          | NA                 |
| `char`       | character                        | 8 bits             |
| `wchar_t`    | wide character                   | 16 bits            |
| `char16_t`   | Unicode character                | 16 bits            |
| `char32_t`   | Unicode character                | 32 bits            |
| `short`      | short integer                    | 16 bits            |
| `int`        | integer                          | 16 bits            |
| `long`       | long integer                     | 32 bits            |
| `long long`  | long integer                     | 64 bits            |
| `float`      | single-precision floating-point  | 6 significant digits |
| `double`     | double-precision floating-point  | 10 significant digits |
| `long double`| extended-precision floating-point| 10 significant digits |

> - 实际大小因机器而异，可使用 `sizeof` 查看类型实际大小
> - `bool` 类型只有 `true` 和 `false` 两个值

---

#### 字符

- `char` 是基本字符类型，**保证足够大以存储机器基本字符集中任何字符的数值编码**
- **char 的大小等于单个机器字节**
- `wchar_t`：保证足够大以存储机器最大扩展字符集中的任何字符
- `char16_t`、`char32_t`：专为 Unicode 字符设计，支持国际化

#### 浮点

浮点型表示单精度、双精度和扩展精度值：
- 标准规定最小有效数字位数，大多数编译器提供超过最小要求的精度
- **典型实现**：
  - `float`：1 字 (32 位)，约 7 位有效数字
  - `double`：2 字 (64 位)，约 16 位有效数字  
  - `long double`：3 或 4 字 (96 或 128 位)，精度因实现而异

#### 整型

语言保证整型之间的大小关系：
- `int` 至少与 `short` 一样大
- `long` 至少与 `int` 一样大  
- `long long` 至少与 `long` 一样大
- `long long` 类型由新标准引入

---

### ✅ 机器级表示 (Machine-Level Representation)

计算机以 **bit 序列** 存储数据，每个 bit 存储 0 或 1：
- 内存被组织为 **2 的幂次大小的块**
- 最小可寻址内存块称为 **"字节" (byte)**
- 基本存储单位（通常是少量字节）称为 **"字" (word)**
- 在 C++ 中，一个字节至少包含存储基本字符集字符所需的位数
- 大多数机器上：1 字节 = 8 位，1 字 = 32 或 64 位（4 或 8 字节）

#### 地址和内存解释

- 每个字节都有一个 **地址 (address)**
- 可以用地址引用从该地址开始的不同大小的位集合
- **类型决定了使用多少位以及如何解释这些位**

---

### ✅ 符号型 vs 无符号型

- **signed (符号型)**：表示负数、正数（包括零）
- **unsigned (无符号型)**：仅表示大于等于零的值

#### 类型规则

- `int`、`short`、`long`、`long long` 默认为 signed
- 通过在类型前加 `unsigned` 获得无符号版本
- `unsigned int` 可简写为 `unsigned`

#### 数值范围示例

- 8 位 `unsigned char`：可存储 0 到 255 的值
- 8 位 `signed char`：标准保证能存储 -127 到 127 的值
- 现代机器通常允许 -128 到 127 的值

#### char 字符类型特殊性

**重要概念**：`char` 有三种**独立的**基本字符类型：
- `char`
- `signed char`  
- `unsigned char`

**关键点**：
- `char` **不等同于** `signed char`
- 虽然有三种字符类型，但只有两种表示：signed 和 unsigned
- `char` 类型使用其中一种表示，具体取决于编译器
- 标准没有规定符号类型如何表示，但规定了范围必须在正数和负数之间平分 <!-- 修正：表达更准确 -->

---

### 📚 策略建议：如何选择类型
C++ 提供多种算术类型以适应不同硬件，但大多数程序员只需遵循简单规则选择常用类型，无需深入理解底层复杂性。

### 🎯 类型选择原则

- **无符号类型**：当确定值不可能为负数时使用
- **整数运算**：使用 `int`。`short` 通常太小，`long` 在实践中通常与 `int` 大小相同。如果数据值超过 `int` 的最小保证大小，使用 `long long`
- **算术表达式中避免使用 `char` 或 `bool`**：仅用于存储字符或真值。计算中使用 `char` 特别有问题，因为某些机器上 `char` 是 signed，某些是 unsigned。如需要微小整数，明确指定 `signed char` 或 `unsigned char`
- **浮点计算使用 `double`**：`float` 通常精度不足，双精度与单精度计算成本相差无几。实际上，某些机器上双精度运算比单精度更快。`long double` 提供的精度通常不必要且运行时成本相当高

---

### ✅ 类型转换 (Type Conversions)

#### 📝 基本概念
类型定义了对象可能包含的数据以及对象可执行的操作。许多类型支持将给定类型的对象**转换**为其他相关类型的能力。

**自动类型转换**：当我们在期望某种类型对象的地方使用另一种类型的对象时，类型转换会自动发生。

#### 📝 数学类型之间的赋值转换

**转换规则示例**：
```cpp
bool b = 42;                    // b is true
int i = b;                      // i has value 1
i = 3.14;                       // i has value 3
double pi = i;                  // pi has value 3.0
unsigned char c = -1;           // c has value 255 (assuming 8-bit chars)
signed char c2 = 256;           // value of c2 is undefined
```

**具体转换行为主要看目标类型允许的值范围**： <!-- 修正：表达更准确 -->
- **非bool数学类型 → bool**：值为0时结果为`false`，否则为`true`
- **bool → 其他数学类型**：`true`转换为1，`false`转换为0
- **浮点值 → 整型**：值被截断，只保留小数点前的部分
- **整型 → 浮点型**：小数部分为零，如果整数位数超过浮点对象容量可能丢失精度
- **超范围值 → unsigned类型**：结果是该值对目标类型能容纳值的数量取模的余数
- **超范围值 → signed类型**：结果是**undefined（未定义的）**，程序可能会崩溃或产生垃圾值

#### ⚠️ 重要警告：避免未定义和实现定义的行为
- **未定义行为**：由编译器无需（有时无法）检测的错误导致
- **实现定义行为**：如假设`int`大小固定，这样的程序称为**不可移植的**
- 程序可能在某些情况下看起来正确运行，但在不同编译器或输入下可能失败

#### 📝 条件中的类型转换
编译器在期望不同数学类型的地方应用相同的类型转换：
```cpp
int i = 42;
if (i)  // condition will evaluate as true
    i = 0;
```
- 如果值为0，条件为`false`；所有其他（非零）值产生`true`
- 在数学表达式中使用`bool`时，其值总是转换为0或1，因此几乎肯定是错误的

#### 📝  涉及无符号类型的表达式

##### 混合运算的转换规则
当在数学表达式中同时使用`unsigned`和`int`值时，`int`值通常转换为`unsigned`：
```cpp
unsigned u = 10;
int i = -42;
std::cout << i + i << std::endl;    // prints -84
std::cout << u + i << std::endl;    // if 32-bit ints, prints 4294967264 because wrap around
```

#### 📝 减法运算的陷阱
从unsigned中减去一个值时，必须确保结果不能为负：
```cpp
unsigned u1 = 42, u2 = 10;
std::cout << u1 - u2 << std::endl; // ok: result is 32
std::cout << u2 - u1 << std::endl; // ok: but the result will wrap around
```

#### 📝 循环中的unsigned类型问题
**错误示例**：
```cpp
// WRONG: u can never be less than 0; the condition will always succeed
for (unsigned u = 10; u >= 0; --u)
    std::cout << u << std::endl;
```
当`u`为0时，`--u`会使其变为一个非常大的正数（如4294967295）

**正确解决方案**：使用`while`循环
```cpp
unsigned u = 11;  // start the loop one past the first element we want to print
while (u > 0) {
    --u;          // decrement first, so that the last iteration will print 0
    std::cout << u << std::endl;
}
```

#### ⚠️ 注意：不要混合signed和unsigned类型
混合signed和unsigned值的表达式在signed值为负时会产生令人惊讶的结果。**signed值会自动转换为unsigned**。

---

### ✅ 字面值 (Literals)

#### 基本概念

像 42 这样的值称为 **字面值**，因为其值是不言自明的。每个字面值都有类型，字面值的形式和值决定了其类型。字面值也不是对象。

---

#### 📝 整型和浮点型字面值

##### 整型字面值表示法

整型以 `0` 开头的是八进制，`0x` 开头的是十六进制。比如使用十进制、八进制和十六进制表示 20：

```cpp
20     // decimal
024    // octal
0x14   // hexadecimal
```

---

##### 整型字面值类型推断

* **十进制字面值**（如 `42`）：

  * 默认是 **signed** 类型
  * 使用能容纳其值的最小类型，匹配顺序如下：

    ```cpp
    int → long → long long
    ```

* **八进制和十六进制字面值**（如 `052`, `0x2A`）：

  * 可以是 signed 或 unsigned 类型
  * 使用能容纳其值的最小类型，匹配顺序如下：

    ```cpp
    int → unsigned int → long → unsigned long → long long → unsigned long long
    ```

⚠️ 如果字面值太大，超出了最大支持类型（如 `unsigned long long`）的范围，编译器将报错。

⚠️ C++ 中没有类型为 `short` 的字面值。

⚠️ 负号**不是**字面值的一部分，负号是一个对字面值取反的**运算符**。 <!-- 修正：字面符→字面值 -->

---

##### 整数字面值类型后缀（Suffix）

我们可以通过添加后缀来显式指定整数字面值的类型：

| 后缀          | 含义   | 最小类型        |
| ----------- | ---- | ----------- |
| `u` / `U`   | 无符号  | `unsigned`  |
| `l` / `L`   | 长整型  | `long`      |
| `ll` / `LL` | 长长整型 | `long long` |

示例：

```cpp
42U     // unsigned int
42L     // long
42LL    // long long
42UL    // unsigned long
```

---

##### 字符和字符串字面值前缀（Prefix）

| 前缀   | 含义             | 类型         |
| ---- | -------------- | ---------- |
| `u`  | Unicode 16 字符  | `char16_t` |
| `U`  | Unicode 32 字符  | `char32_t` |
| `L`  | 宽字符（wide char） | `wchar_t`  |
| `u8` | UTF-8 字符串字面量   | `char`     |

---

#### 📝 浮点型字面值
- 两种方法表示：包含**小数点**或用**科学记数法**指定的指数
- 科学记数法中，指数用`E`或`e`表示
- **默认类型**：`double`
- 我们也可以通过以下后缀覆盖默认类型： <!-- 修正：前缀→后缀 -->

| 后缀        | 类型            |
| --------- | ------------- |
| `f` / `F` | `float`       |
| `l` / `L` | `long double` |

**示例**：
```cpp
3.14159    3.14159E0    0.    0e0    .001
```

#### 📝 字符和字符串字面值

##### 字符字面值
- 单引号内的字符是`char`类型的字面值
- 双引号内的零个或多个字符是字符串字面值

```cpp
'a'           // character literal
"Hello World!" // string literal
```

#### 字符串字面值特性
- 字符串字面值的类型是**常量char的数组**
- 编译器在每个字符串字面值末尾追加一个空字符('\0')，因此实际长度会多一位 <!-- 修正：真实值→实际长度 -->
- 字符字面值'A'表示单个字符A，而字符串字面值"A"表示包含字母A和空字符的两个字符数组

#### 多行字符串字面值
相邻的仅由空格、制表符或换行分隔的字符串字面值会连接成一个字面值：
```cpp
// multiline string literal
std::cout << "a really, really long string literal "
             "that spans two lines" << std::endl;
```

#### 转义序列 (Escape Sequences)

##### 不可打印字符
某些字符（如退格或控制字符）没有可见图像，这些字符是**不可打印的**。其他字符在语言中有特殊含义。我们使用**转义序列**表示这些字符。

##### 预定义转义序列
| 转义序列 | 含义 | 转义序列 | 含义 |
|---------|------|---------|------|
| `\n` | newline | `\t` | horizontal tab |
| `\v` | vertical tab | `\b` | backspace |
| `\\` | backslash | `\?` | question mark |
| `\r` | carriage return | `\f` | formfeed |
| `\a` | alert (bell) | `\"` | double quote |
| `\'` | single quote |  |  |

##### 通用转义序列
- **八进制**：`\`后跟1、2或3个八进制数字
- **十六进制**：`\x`后跟1个或多个十六进制数字

**示例**：
```cpp
\7 (bell)     \12 (newline)    \40 (blank)
\0 (null)     \115 ('M')       \x4d ('M')
```

**使用示例**：
```cpp
std::cout << '\n';              // prints a newline
std::cout << "\tHi!\n";         // prints a tab followed by "Hi!" and a newline
std::cout << "Hi \x4d0\115!\n"; // prints Hi MOM! followed by a newline
std::cout << '\115' << '\n';    // prints M followed by a newline
```
⚠️ 如果 `\` 后面跟了超过三个八进制数时，只有前三个数字与 `\` 构成转义序列。 <!-- 修正：表达更准确 -->

#### 指定字面值类型

可以通过添加后缀或前缀来覆盖整型、浮点型或字符字面值的默认类型：

**示例**：
```cpp
L'a'        // wide character literal, type is wchar_t
u8"hi!"     // utf-8 string literal (utf-8 encodes a Unicode character in 8 bits)
42ULL       // unsigned integer literal, type is unsigned long long
1E-3F       // single-precision floating-point literal, type is float
3.14159L    // extended-precision floating-point literal, type is long double
```

#### 后缀组合规则
可以独立指定整型字面值的符号性和大小。如果后缀包含`U`，则字面值为unsigned类型；如果包含`L`，则类型至少为`long`；如果包含`LL`，则类型为`long long`或`unsigned long long`。可以将`U`与`L`或`LL`组合使用。

⚠️ 当你想通过 `L` 来写一个 `long` 的字面值时，使用**大写**而不是小写以区分和数字1的差异 <!-- 修正：语法 -->

#### 布尔和指针字面值
- `true`和`false`是`bool`类型的字面值
- `nullptr`是指针字面值

#### ⭐ 最佳实践
编写`long`字面值时，使用大写的`L`；小写字母`l`容易与数字1混淆。

---

## 🍃 小结

### 📚 核心知识体系

**类型系统架构**：
- C++ 原始类型分为算术类型（整型、浮点型）和void类型
- 标准规定最小尺寸保证，实际大小依赖于硬件实现
- 类型决定内存中数据的解释方式和支持的操作集合

**内存与表示**：
- 计算机以二进制位序列存储数据，通过字节寻址
- 类型系统提供了从位模式到有意义数据的映射机制
- 理解机器级表示有助于优化程序性能和调试

### ⚡ 关键概念精要

**符号性处理**：
- signed/unsigned类型的本质区别在于值域范围
- char类型的三种独立形式（char、signed char、unsigned char）
- 类型转换中的截断、环绕和未定义行为风险

**字面值系统**：
- 字面值的类型推断规则：十进制vs八/十六进制的不同策略
- 前缀后缀机制：精确控制字面值类型，避免隐式转换
- 转义序列：处理特殊字符的标准化方法

### 🛡️ 实践防护策略

**类型选择智慧**：
- **默认选择**: int用于整数、double用于浮点数
- **特殊场景**: unsigned仅用于确定非负的场合
- **避免陷阱**: 禁止char/bool参与算术运算，防止可移植性问题

**转换安全准则**：
- 理解自动类型转换的触发时机和转换规则
- 警惕signed/unsigned混合运算的意外结果
- 掌握循环中unsigned类型的边界问题及解决方案

**代码质量保障**：
- 避免依赖实现定义行为，提升跨平台兼容性
- 识别和预防未定义行为，确保程序健壮性
- 合理使用字面值前缀后缀，增强代码可读性和准确性

### 🔗 学习路径指引

这些基础知识为后续章节奠定根基：
- **变量和对象**: 类型与存储管理的结合
- **表达式和语句**: 类型转换在实际计算中的应用
- **函数**: 参数类型匹配和返回值处理
- **类和模板**: 用户定义类型的设计原则

掌握原始类型是理解C++类型系统的第一步，为编写高质量、可维护的C++程序建立坚实基础。