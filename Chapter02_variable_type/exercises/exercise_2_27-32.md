# Exercises 2.27-2.29 解答

## Exercise 2.27: Which of the following initializations are legal? Explain why.

```cpp
(a) int i = -1, &r = 0;
(b) int *const p2 = &i2;
(c) const int i = -1, &r = 0;
(d) const int *const p3 = &i2;
(e) const int *p1 = &i2;
(f) const int &const r2;
(g) const int i2 = i, &r = i;
```

### 解答分析

**(a) `int i = -1, &r = 0;`**
**结果：非法 (Illegal)**

**原因：**
- `int i = -1` 合法 - 普通整数初始化
- `&r = 0` 非法 - 引用不能绑定到字面值常量
- 引用必须绑定到一个对象，而不能绑定到字面值

**(b) `int *const p2 = &i2;`**
**结果：合法 (Legal，假设 i2 已定义)**

**原因：**
- `p2` 是一个常量指针，指向 `int`
- 常量指针必须初始化，这里用 `&i2` 初始化是合法的
- 假设 `i2` 是一个已定义的 `int` 变量

**(c) `const int i = -1, &r = 0;`**
**结果：合法 (Legal)**

**原因：**
- `const int i = -1` 合法 - const 对象正确初始化
- `const int &r = 0` 合法 - const 引用可以绑定到字面值
- 编译器会创建临时对象来存储字面值 0，然后 r 绑定到该临时对象
- 这正是 const 引用的特殊之处：允许绑定到右值（字面值、表达式结果等）

**(d) `const int *const p3 = &i2;`**
**结果：合法 (Legal，假设 i2 已定义)**

**原因：**
- `p3` 是一个常量指针，指向常量 `int`
- 既有顶层 const（指针本身是常量）又有底层 const（指向常量对象）
- 初始化是必需的且合法的

**(e) `const int *p1 = &i2;`**
**结果：合法 (Legal，假设 i2 已定义)**

**原因：**
- `p1` 是指向常量 `int` 的指针（底层 const）
- 可以指向 const 或非 const 对象
- 初始化合法

**(f) `const int &const r2;`**
**结果：非法 (Illegal)**

**原因：**
- 引用本身不是对象，不能被声明为 const
- 正确的语法是 `const int &r2 = ...;`
- 引用必须初始化

**(g) `const int i2 = i, &r = i;`**
**结果：合法 (Legal，假设 i 已定义)**

**原因：**
- `const int i2 = i` 合法 - 用变量 i 初始化常量
- `&r = i` 合法 - const 引用绑定到变量 i
- 假设变量 `i` 已经定义

---

## Exercise 2.28: Explain the following definitions. Identify any that are illegal.

```cpp
(a) int i, *const cp;
(b) int *p1, *const p2;
(c) const int ic, &r = ic;
(d) const int *const p3;
(e) const int *p;
```

### 解答分析

**(a) `int i, *const cp;`**
**结果：非法 (Illegal)**

**定义说明：**
- `i` 是普通的 `int` 变量
- `cp` 是常量指针，指向 `int`

**非法原因：**
- 常量指针 `cp` 必须在声明时初始化
- 应该写成：`int i, *const cp = &i;`

**(b) `int *p1, *const p2;`**
**结果：非法 (Illegal)**

**定义说明：**
- `p1` 是指向 `int` 的普通指针
- `p2` 是指向 `int` 的常量指针

**非法原因：**
- 常量指针 `p2` 必须初始化
- 应该写成：`int *p1, *const p2 = &someInt;`

**(c) `const int ic, &r = ic;`**
**结果：非法 (Illegal)**

**定义说明：**
- `ic` 是常量整数
- `r` 是对常量整数的引用，绑定到 `ic`

**非法原因：**
- 常量 `ic` 必须初始化
- 应该写成：`const int ic = 0, &r = ic;`

**(d) `const int *const p3;`**
**结果：非法 (Illegal)**

**定义说明：**
- `p3` 是常量指针，指向常量 `int`（既有顶层 const 又有底层 const）

**非法原因：**
- 常量指针必须初始化
- 应该写成：`const int *const p3 = &someConstInt;`

**(e) `const int *p;`**
**结果：合法 (Legal)**

**定义说明：**
- `p` 是指向常量 `int` 的指针（只有底层 const）
- 指针本身不是常量，可以改变指向
- 不需要初始化（虽然最好初始化）

---

## Exercise 2.29: Using the variables in the previous exercise, which of the following assignments are legal? Explain why.

**前提：假设 Exercise 2.28 中的非法定义已经修正为合法形式**

```cpp
// 假设的合法定义：
int i;
int *p1;
const int ic = 0;
const int &r = ic;
const int *const p3 = &ic;
const int *p = nullptr;
```

### 赋值分析

**(a) `i = ic;`**
**结果：合法 (Legal)**

**原因：**
- 将 const int 的值赋给普通 int
- 顶层 const 在拷贝时被忽略
- 只是拷贝值，不会改变 ic

**(b) `p1 = p3;`**
**结果：非法 (Illegal)**

**原因：**
- `p3` 是 `const int *const`（有底层 const）
- `p1` 是 `int *`（没有底层 const）
- 不能将指向 const 的指针赋给指向非 const 的指针

**(c) `p1 = &ic;`**
**结果：非法 (Illegal)**

**原因：**
- `ic` 是 const int，其地址类型是 `const int *`
- `p1` 是 `int *`
- 不能将 `const int *` 赋给 `int *`

**(d) `p3 = &ic;`**
**结果：非法 (Illegal)**

**原因：**
- `p3` 是常量指针（顶层 const）
- 常量指针一旦初始化就不能改变指向

**(e) `p2 = p1;`**
**结果：非法 (Illegal)**

**原因：**
- `p2` 是常量指针（假设已正确定义）
- 常量指针不能被重新赋值

**(f) `ic = *p3;`**
**结果：非法 (Illegal)**

**原因：**
- `ic` 是 const int
- 常量对象不能被赋值，即使赋值的是相同类型的值

---

## Exercise 2.30: For each of the following declarations indicate whether the object being declared has top-level or low-level const.

```cpp
const int v2 = 0;        int v1 = v2;
int *p1 = &v1, &r1 = v1;
const int *p2 = &v2, *const p3 = &i, &r2 = v2;
```

### 变量分析

让我们逐一分析每个声明：

**(1) `const int v2 = 0;`**
- **类型：顶层 const (top-level const)**
- **分析：**`v2` 本身是一个常量整数，不能被修改
- **含义：**对象本身是常量

**(2) `int v1 = v2;`**
- **类型：无 const**
- **分析：**`v1` 是普通的 `int` 变量，用 `v2` 的值初始化
- **注意：**拷贝时顶层 const 被忽略

**(3) `int *p1 = &v1`**
- **类型：无 const**
- **分析：**`p1` 是指向 `int` 的普通指针
- **含义：**既可以改变指针指向，也可以通过指针修改所指对象

**(4) `&r1 = v1`**  
- **类型：无 const**
- **分析：**`r1` 是对 `int` 的普通引用
- **含义：**可以通过引用修改所引用的对象

**(5) `const int *p2 = &v2`**
- **类型：底层 const (low-level const)**
- **分析：**`p2` 是指向常量 `int` 的指针
- **含义：**不能通过 `p2` 修改所指对象，但可以改变 `p2` 的指向

**(6) `*const p3 = &i`**
- **类型：既有顶层 const 又有底层 const (both top-level and low-level const)**
- **完整类型：**`const int *const p3 = &i`
- **分析：**
  - 底层 const：`const int *` - 指向常量 int
  - 顶层 const：`*const` - 指针本身是常量
- **含义：**既不能改变指针的指向，也不能通过指针修改所指对象
- **注意：**假设 `i` 是已定义的变量

**(7) `&r2 = v2`**
- **类型：底层 const (low-level const)**  
- **分析：**`r2` 是对常量 `int` 的引用
- **含义：**不能通过 `r2` 修改所引用的对象

### 总结表格

| 变量 | 类型 | const 类型 | 说明 |
|------|------|-----------|------|
| `v2` | `const int` | 顶层 const | 对象本身是常量 |
| `v1` | `int` | 无 const | 普通变量 |
| `p1` | `int *` | 无 const | 普通指针 |
| `r1` | `int &` | 无 const | 普通引用 |
| `p2` | `const int *` | 底层 const | 指向常量的指针 |
| `p3` | `int *const` | 顶层 const | 常量指针 |
| `r2` | `const int &` | 底层 const | 对常量的引用 |

---

## Exercise 2.31: Given the declarations in the previous exercise determine whether the following assignments are legal. Explain how the top-level or low-level const applies in each case.

```cpp
r1 = v2;
p1 = p2;    p2 = p1;
p1 = p3;    p2 = p3;
```

### 赋值分析

基于 Exercise 2.30 的变量声明，分析以下赋值的合法性：

**(1) `r1 = v2;`**
**结果：合法 (Legal)**

**分析：**
- `r1` 是 `int &`（无 const）
- `v2` 是 `const int`（顶层 const）
- **规则：**顶层 const 在拷贝/赋值时被忽略
- **操作：**将 `v2` 的值赋给 `r1` 引用的对象，这是合法的

**(2) `p1 = p2;`**
**结果：非法 (Illegal)**

**分析：**
- `p1` 是 `int *`（无 const）
- `p2` 是 `const int *`（底层 const）
- **规则：**不能将指向常量的指针赋给指向非常量的指针
- **原因：**这会破坏 const 的保护，允许通过 `p1` 修改本应受保护的常量对象

**(3) `p2 = p1;`**
**结果：合法 (Legal)**

**分析：**
- `p2` 是 `const int *`（底层 const）
- `p1` 是 `int *`（无 const）
- **规则：**可以将指向非常量的指针赋给指向常量的指针
- **原因：**这是安全的类型转换，增强了 const 保护

**(4) `p1 = p3;`**
**结果：合法 (Legal)**

**分析：**
- `p1` 是 `int *`（无 const）
- `p3` 是 `int *const`（顶层 const）
- **规则：**顶层 const 在赋值时被忽略
- **操作：**拷贝 `p3` 中存储的地址值给 `p1`

**(5) `p2 = p3;`**
**结果：合法 (Legal)**

**分析：**
- `p2` 是 `const int *`（底层 const）
- `p3` 是 `int *const`（顶层 const）
- **规则：**
  - 顶层 const 被忽略
  - `int *` 可以转换为 `const int *`（增加底层 const 保护）
- **操作：**拷贝 `p3` 的地址值给 `p2`

### 核心规则总结

#### 顶层 const 规则
- **拷贝/赋值时被忽略**
- 不影响类型兼容性
- 例：`const int` → `int`（拷贝值时合法）

#### 底层 const 规则  
- **必须严格匹配或安全转换**
- 非常量 → 常量：✅ 合法（安全）
- 常量 → 非常量：❌ 非法（不安全）
- 例：`int *` → `const int *` 合法，反之非法

#### 类型转换安全性
| 转换方向 | 安全性 | 原因 |
|----------|--------|------|
| 非 const → const | 安全 ✅ | 增加保护 |
| const → 非 const | 不安全 ❌ | 破坏保护 |
| 顶层 const | 忽略 ✅ | 不影响对象使用 |
| 底层 const | 必须匹配 ⚠️ | 影响通过指针/引用的操作 |


## 题目 Exercise 2.32
Is the following code legal or not? If not, how might you make it legal?

```cpp
int null = 0, *p = null;
```

---

## 分析

### 代码合法性
**结果：非法 (Illegal)**

### 问题分析

这行代码尝试做两件事：
1. `int null = 0` - 定义一个名为 `null` 的整数变量，初始化为 0 ✅
2. `*p = null` - 定义一个指针 `p`，并尝试用 `null` 初始化 ❌

### 错误原因

**类型不匹配：**
- `p` 是 `int *` 类型（指向 int 的指针）
- `null` 是 `int` 类型（整数变量）
- 不能将 `int` 类型的变量直接赋给指针类型

**编译错误：**
```
error: cannot convert 'int' to 'int*' in initialization
```

---

## 修正方案

### 方案 1：使用地址操作符
```cpp
int null = 0, *p = &null;
```
**说明：**
- 使用 `&null` 获取 `null` 变量的地址
- 将地址赋给指针 `p`
- 现在 `p` 指向变量 `null`

### 方案 2：初始化为空指针
```cpp
int null = 0, *p = nullptr;
```
**说明：**
- 如果想要一个空指针，使用 `nullptr`（C++11）
- 或者使用 `0` 或 `NULL`（传统方式）

### 方案 3：使用 0 初始化指针
```cpp
int null = 0, *p = 0;
```
**说明：**
- 数字 `0` 可以隐式转换为空指针
- 但 `nullptr` 是更现代、更安全的选择

### 方案 4：分开声明
```cpp
int null = 0;
int *p = &null;  // 或者 int *p = nullptr;
```
**说明：**
- 将声明分开可能更清晰
- 避免在一行中混合不同类型的初始化

---

## 关键概念

### 指针初始化规则
1. **指针必须指向相同类型的对象**
2. **获取变量地址：**使用 `&` 操作符
3. **空指针初始化：**使用 `nullptr`、`0` 或 `NULL`
4. **类型安全：**不能将整数变量直接赋给指针

### 最佳实践
- **推荐使用 `nullptr`** 而不是 `0` 来表示空指针
- **明确意图：**如果要指向变量，使用 `&`；如果要空指针，使用 `nullptr`
- **避免混淆：**不要使用 `null` 作为变量名，容易与空指针概念混淆

### 正确的指针使用示例
```cpp
// 指向变量
int value = 42;
int *ptr1 = &value;      // ptr1 指向 value

// 空指针
int *ptr2 = nullptr;     // ptr2 是空指针

// 指向数组首元素
int arr[5] = {1,2,3,4,5};
int *ptr3 = arr;         // ptr3 指向 arr[0]
```

## 总结

### 关键规则
1. **常量指针必须初始化**
2. **const 对象必须初始化**
3. **引用必须初始化，且不能是 const**
4. **底层 const 在赋值时不能被忽略**
5. **顶层 const 在拷贝时被忽略**
6. **常量对象和常量指针不能被重新赋值**