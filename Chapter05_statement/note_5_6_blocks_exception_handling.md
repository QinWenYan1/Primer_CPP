# 📘 5.6 try Blocks and Exception Handling (try块和异常处理)

> 来源说明：C++ Primer 5.6 | 本节涵盖：异常处理的基本概念、throw表达式、try-catch块的使用，以及C++标准库中的异常类体系。

## 🧠 本节核心概念（提纲目录）
*   异常处理的基本概念和用途
*   throw表达式：抛出异常
*   try-catch块：捕获和处理异常
*   异常传播和查找处理器的过程
*   C++标准异常类体系

---

## ✅ 异常处理基础
**定义 / 理论**
*   异常是运行时异常情况，存在于程序正常功能之外（如数据库连接丢失、意外输入等）
*   异常处理用于程序的一部分检测到无法解决的问题，且检测部分无法继续执行的情况
*   异常处理涉及三个组件：
    *   `throw`表达式：检测部分使用，表示遇到无法处理的情况
    *   `try`块：处理部分使用，包含可能抛出异常的代码和异常处理器
    *   异常类：用于在`throw`和`catch`之间传递关于异常的信息

---

## ✅ throw 表达式
**定义 / 理论**
*   检测部分使用`throw`表达式抛出异常
*   语法：`throw`关键字后跟一个表达式，决定抛出异常的类型
*   `throw`表达式通常以分号结尾，使其成为表达式语句
*   抛出异常会终止当前函数，并将控制权转移给能处理该异常的处理器

**教材示例代码 / 过程**
```cpp
#include <stdexcept> // 包含runtime_error定义

// 检查两个Sales_item是否代表相同的书
if (item1.isbn() != item2.isbn())
    throw std::runtime_error("Data must refer to same ISBN"); // 抛出runtime_error异常

// 如果执行到这里，说明ISBN相同
cout << item1 + item2 << endl;
```
*   如果`ISBN`不同，我们会`throw`一个以`runtime_error`为对象的表达式
*   `runtime_error`是标准库异常类型之一，定义在 <b> `<stdexcept>`</b>头文件中
*   必须使用**字符串或C风格字符串**初始化`runtime_error`来给予更多信息

**注意点**
*   ⚠️ 抛出异常会立即终止当前函数的执行
*   💡 异常对象中包含的信息可以通过`what()`成员函数获取

---

## ✅ try-catch 块
**定义 / 理论**
*   `try`块包含可能抛出异常的代码, 里面主要是包含程序逻辑
*   如同其他块一样，在`try`块声明的变量是**无法**被块外面访问的, 尤其是`catch`块中
*   一个`try`块后跟一个或多个`catch`子句（异常处理器）
*   `catch`语块包含三部分：关键字catch, **括号和括号中的对象声明（可能是无名的）**，块
*   当`try`块中的代码抛出异常时，控制权转移到匹配的`catch`子句
*   完成`catch`处理后，执行继续到`try`块后最后一个`catch`子句之后的语句

**基本语法**
```cpp
try {
    // 程序语句（可能抛出异常）
} catch (exception-declaration) {
    // 处理语句
} catch (exception-declaration) {
    // 处理另一个异常类型
} // ...
```

**教材示例代码 / 过程**
```cpp
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::runtime_error;

while (cin >> item1 >> item2) {
    try {
        // 执行添加两个Sales_item的代码
        // 如果添加失败，代码会抛出runtime_error异常
        if (item1.isbn() != item2.isbn())
            throw runtime_error("Data must refer to same ISBN");
        cout << item1 + item2 << endl;
    } catch (runtime_error err) {
        // 提醒用户ISBN必须匹配，并提示输入另一对
        cout << err.what() << "\nTry Again? Enter y or n" << endl;
        char c;
        cin >> c;
        if (!cin || c == 'n')
            break; // 跳出while循环
    }
}
```
*   `try`有一个`catch`子句来处理类型`runtime_error`的`exception`
*   如果`try`块里面有`runtime_error`扔出，我们的`catch`就会执行其块中的语句来进行处理
*   `err.what()`返回初始化`runtime_error`对象时使用的字符串副本
*   任何`exception`标准库里面的类都有`what()`成员函数
*   `what()`不接受参数，会返回一个C风格的字符串(`const char*`)
*   在这个例子中，`runtime_error`会返回我们之前用于初始化这个对象的`string`副本


**注意点**
*   ⚠️ `try`块中声明的变量在`catch`子句中不可访问
*   💡 可以有多个`catch`子句处理不同类型的异常

---

## ✅ 异常传播与处理器查找
**定义 / 理论**
*   当异常被抛出时，搜索匹配的`catch`处理器的过程沿着**调用链反向进行**
*   首先搜索抛出异常的函数
*   如果没有找到匹配的`catch`，该函数终止
*   然后搜索调用该函数的函数，依此类推，沿着执行路径向上回溯
*   如果找不到合适的`catch`，控制权转移给名为`terminate`的库函数
*   `terminate`的行为是系统相关的，但保证会停止程序的进一步执行
*   对于那些没有`try`块的普通程序在处理`exception`时也是使用`terminate`

**注意点**
*   ⚠️ 没有定义任何`try`块的程序中的异常也以相同方式处理（调用`terminate`）
*   💡 复杂的系统可能有多个嵌套的`try`块，异常处理会沿着调用栈向上查找

--- 

## ✅ 异常安全警告 (Exception safe warning)
**定义 / 理论**
*   异常会中断程序的正常流程
*   在异常发生点，调用者请求的一些计算可能已经完成，而其他计算尚未完成
*   绕过部分程序可能导致对象处于无效或不完整状态，或资源未释放等问题
*   在异常处理期间正确"清理"的程序被称为异常安全
*   **编写异常安全的代码非常困难**，超出了本语言入门书的范围

**注意点**
*   ⚠️ 异常安全是编写健壮程序的重要考虑因素
*   💡 一些程序使用异常只是为了在异常条件下终止程序，这类程序通常不担心异常安全
*   💡 处理异常并继续处理的程序**必须始终意识到可能发生的异常**，并确保对象有效、资源不泄漏

---

## ✅ 知识点 6: 标准异常类
**定义 / 理论**
*   C++库定义了几个类来报告标准库函数中遇到的问题
*   这些异常类也 intended 用于我们编写的程序
*   异常类定义在四个头文件中：

| 头文件 | 异常类 | 描述 |
|--------|--------|------|
| `<exception>` | `exception` | 最通用的异常类，只通知发生了异常，不提供额外信息 |
| `<stdexcept>` | 多种通用异常类 | 见表5.1 |
| `<new>` | `bad_alloc` | 内存分配失败时抛出 |
| `<type_info>` | `bad_cast` | 动态类型转换失败时抛出 |

### 表5.1: <stdexcept>中定义的标准异常类

| 异常类 | 描述 |
|--------|------|
| `exception` | 最通用的问题类型 |
| `runtime_error` | 只能在运行时检测到的问题 |
| `range_error` | 运行时错误：结果生成在值范围之外 |
| `overflow_error` | 运行时错误：计算溢出 |
| `underflow_error` | 运行时错误：计算下溢 |
| `logic_error` | 程序逻辑错误 |
| `domain_error` | 逻辑错误：参数不存在结果 |
| `invalid_argument` | 逻辑错误：不适当的参数 |
| `length_error` | 逻辑错误：尝试创建大于该类型最大大小的对象 |
| `out_of_range` | 逻辑错误：使用了有效范围之外的值 |

**异常类的操作**
*   只能默认初始化`exception`、`bad_alloc`和`bad_cast`对象，不能提供初始器
*   其他异常类型可以从**字符串或C风格字符串初始化**，但不能默认初始化
*   所有异常类型都定义了一个名为`what`的操作
*   `what()`函数不接受参数，返回一个指向C风格字符串的`const char*`
*   对于接受字符串初始化的类型，`what()`返回该字符串
*   对于其他类型，`what()`返回的字符串值**因异常对象类型**而异

**注意点**
*   ⚠️ 不同的异常类用于不同类型的错误，选择合适的异常类可以提高代码可读性
*   💡 自定义异常类通常应继承自标准异常类，以保持一致性

---

## 🔑 本节总结
*   异常处理是处理运行时异常情况的机制，允许程序在遇到无法本地处理的问题时通知其他部分
*   `throw`表达式用于抛出异常，终止当前函数执行
*   `try-catch`块用于捕获和处理异常，可以有多个`catch`子句处理不同类型的异常
*   异常传播沿着调用栈向上查找匹配的处理器，如果找不到则调用`terminate`
*   C++标准库提供了一组异常类，定义在`<exception>`、`<stdexcept>`、`<new>`和`<type_info>`头文件中
*   编写异常安全的代码很困难，需要确保在异常发生时资源正确释放，对象处于一致状态

---

## 📌 考试速记版
*   **异常处理**: `throw`抛出 → `try`尝试 → `catch`捕获
*   **throw**: `throw exception_object;` (如`throw runtime_error("message");`)
*   **try-catch**: 
    ```cpp
    try { /* 可能抛出异常的代码 */ } 
    catch (exception_type e) { /* 处理代码 */ }
    ```
*   **异常传播**: 沿调用栈向上查找处理器，找不到则`terminate`
*   **标准异常**:
    *   `<exception>`: `exception` (最通用)
    *   `<stdexcept>`: `runtime_error`, `logic_error`等（见表5.1）
    *   `<new>`: `bad_alloc` (内存分配失败)
    *   `<type_info>`: `bad_cast` (转换失败)
*   **异常安全**: 难但重要，确保异常时资源不泄漏、对象状态一致
*   **what()**: 异常类的成员函数，返回描述异常的C风格字符串