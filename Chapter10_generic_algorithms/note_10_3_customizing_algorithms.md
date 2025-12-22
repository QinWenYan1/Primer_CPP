# 📘 10.3 自定义操作 (Customizing Operations)

> 来源说明：C++ Primer 第10.3节 | 本节涵盖：如何通过传递函数、lambda表达式和bind函数自定义算法行为

---

## 🗺️ 知识体系图

```mermaid
graph TD
    A[自定义操作] --> B[传递函数给算法]
    A --> C[Lambda表达式]
    A --> D[绑定参数bind]
    
    B --> B1[谓词概念]
    B --> B2[sort和stable_sort]
    
    C --> C1[lambda基本语法]
    C --> C2[捕获列表]
    C --> C3[可变lambda]
    C --> C4[返回类型]
    
    D --> D1[bind基本用法]
    D --> D2[占位符]
    D --> D3[参数重排]
    D --> D4[绑定引用参数]
```

## 🧠 核心概念总览

* [*知识点1: 传递函数给算法*](#id1)：使用谓词自定义算法行为
    * [*知识点1.1: 谓词概念*](#id2)：理解一元谓词和二元谓词
* [*知识点1.2: 谓词在排序算法应用*](#id3)：使用isShorter函数自定义排序
* [*知识点2: Lambda表达式*](#id4)：创建匿名函数对象
    * [*知识点2.1: Lambda基本语法*](#id5)：Lambda表达式的组成结构
    * [*知识点2.2: 使用Lambda进行排序*](#id6)：用Lambda替代isShorter函数
    * [*知识点2.3: 捕获列表*](#id7)：访问外部变量的机制
    * [*知识点2.4: 隐式捕获*](#id8)：让编译器推断捕获的变量
    * [*知识点2.5: 可变Lambda*](#id9)：修改按值捕获的变量
    * [*知识点2.6: 指定返回类型*](#id10)：处理复杂返回类型的情况
    * [*知识点2.7: 捕获引用参数*](#id11)：捕获不能复制的对象
* [*知识点3: 绑定参数bind函数*](#id12)：创建参数绑定的调用对象
    * [*知识点3.1: bind基本用法*](#id13)：绑定固定参数值
    * [*知识点3.2: 使用占位符*](#id14)：_n占位符的使用方法
    * [*知识点3.3: 参数重排*](#id15)：重新排列参数顺序
    * [*知识点3.4: 绑定引用参数*](#id16)：使用ref绑定不可复制的对象

---

<a id="id1"></a>
## ✅ 知识点1: 传递函数给算法

**理论**
* 许多算法默认使用元素类型的`<`或`==`运算符进行比较
* 当需要不同排序方式或元素类型没有定义运算符时，可以传递自定义函数
* 这种自定义函数称为**谓词**（predicate）

**教材示例代码**
```cpp
// 比较函数：按单词长度排序
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// 使用自定义比较函数排序
sort(words.begin(), words.end(), isShorter);
```


---

<a id="id2"></a>
### ✅ 知识点1.1: 谓词概念

**理论**
* **谓词**是可调用的表达式，返回可以作为条件使用的值
* **一元谓词**：接受一个参数（如`find_if`使用的谓词）
* **二元谓词**：接受两个参数（如`sort`使用的谓词）
* 谓词**必须**定义一致的顺序关系


---

<a id="id3"></a>
### ✅ 知识点1.2: 谓词在排序算法应用

**理论**
* `sort`算法默认使用`<`运算符，但可以传递二元谓词替代
* `stable_sort`是稳定排序，保持相等元素的原有的相对顺序
* 稳定排序在需要多重排序标准时非常有用
    * 例如：`stable_sort`确保相同长度的单词保持字母顺序

**教材示例代码**
```cpp
// 先按字母顺序排序并去重
elimDups(words);

// 再按长度稳定排序，保持相同长度的字母顺序
stable_sort(words.begin(), words.end(), isShorter);

// 输出结果
for (const auto &s : words)
    cout << s << " ";
cout << endl;
```

**注意点**
* ⚠️ 稳定排序性能可能略低于不稳定排序


---

<a id="id4"></a>
## ✅ 知识点2: Lambda表达式

**理论**
* Lambda表达式是可调用的代码单元，可以视为**内联的匿名函数**
* 主要用途：创建简单的一次性操作，避免定义单独的函数
* Lambda可以在函数内部定义，并能捕获所在函数的局部变量

**教材示例代码**
```cpp
// 最简单的lambda：无参数，返回42
auto f = [] { return 42; };
cout << f() << endl;  // 输出42
```

**注意点**
* ⚠️ Lambda必须包含捕获列表和函数体，参数列表和返回类型可以省略
* 💡 Lambda最常用于算法参数，简化代码编写
* 🔄 Lambda表达式会生成一个未命名的类类型对象

---

<a id="id5"></a>
### ✅ 知识点2.1: Lambda基本语法

**理论**
* Lambda表达式语法：`[capture list] (parameter list) -> return type { function body }`
* 捕获列表：定义lambda可以访问的外部变量
* 参数列表：与普通函数参数类似
* 返回类型：使用尾置返回类型，可省略（根据函数体推断）
* 函数体：包含要执行的代码

**教材示例代码**
```cpp
// 完整形式的lambda
auto add = [](int a, int b) -> int { return a + b; };

// 省略返回类型的lambda（编译器推断）
auto shorter = [](const string &a, const string &b) 
               { return a.size() < b.size(); };
```

**注意点**
* ⚠️ 省略参数列表时表示空参数列表，不是可变的
* ⚠️ 当函数体包含非return语句时，默认返回类型为void
* 💡 简单lambda通常省略返回类型，让编译器推断

---

<a id="id6"></a>
### ✅ 知识点2.2: 使用Lambda进行排序

**理论**
* Lambda可以直接作为算法参数，替代独立的比较函数
* 对于简单比较逻辑，使用Lambda比定义单独函数更简洁

**教材示例代码**
```cpp
// 使用lambda替代isShorter函数
stable_sort(words.begin(), words.end(),
            [](const string &a, const string &b)
            { return a.size() < b.size(); });
```

**注意点**
* 💡 Lambda特别适合只在一处使用的简单操作
* 🔄 Lambda可以直接看到上下文，代码更易理解

---

<a id="id7"></a>
### ✅ 知识点2.3: 捕获列表

**理论**
* 捕获列表允许Lambda访问所在函数的局部变量
* 捕获方式：按值捕获`[var]`或按引用捕获`[&var]`
* Lambda只能使用在捕获列表中明确指定的局部变量

**教材示例代码**
```cpp
// 按值捕获sz
auto wc = find_if(words.begin(), words.end(),
                  [sz](const string &a)
                  { return a.size() >= sz; });

// 错误示例：未捕获sz
auto wc = find_if(words.begin(), words.end(),
                  [](const string &a)
                  { return a.size() >= sz; }); // 错误：sz未捕获
```

**注意点**
* ⚠️ Lambda只能捕获所在函数的非static局部变量
* ⚠️ 静态局部变量和全局变量可以直接使用，无需捕获
* 💡 捕获发生在Lambda创建时，而不是调用时
* 🔄 按值捕获的变量在Lambda创建时复制，后续修改不影响Lambda内的值

---

<a id="id8"></a>
### ✅ 知识点2.4: 隐式捕获

**理论**
* 可以让编译器推断需要捕获的变量
* `[=]`：隐式按值捕获所有使用的局部变量
* `[&]`：隐式按引用捕获所有使用的局部变量
* 可以混合隐式和显式捕获

**教材示例代码**
```cpp
// 隐式按值捕获所有使用的局部变量
auto wc = find_if(words.begin(), words.end(),
                  [=](const string &s) 
                  { return s.size() >= sz; });

// 混合捕获：os隐式按引用，c显式按值
for_each(words.begin(), words.end(),
         [&, c](const string &s) { os << s << c; });

// 混合捕获：os显式按引用，c隐式按值  
for_each(words.begin(), words.end(),
         [=, &os](const string &s) { os << s << c; });
```

**注意点**
* ⚠️ 混合捕获时，第一个元素必须是`&`或`=`
* ⚠️ 显式捕获的变量必须使用与隐式捕获不同的方式
* 💡 隐式捕获简化了代码，但可能意外捕获不需要的变量

---

<a id="id9"></a>
### ✅ 知识点2.5: 可变Lambda

**理论**
* 默认情况下，按值捕获的变量在Lambda内是const的
* 使用`mutable`关键字允许修改按值捕获的变量
* 可变Lambda不能省略参数列表

**教材示例代码**
```cpp
void fcn3()
{
    size_t v1 = 42; // 局部变量
    // f可以修改它捕获的变量
    auto f = [v1]() mutable { return ++v1; };
    v1 = 0;
    auto j = f(); // j是43
}
```

**注意点**
* ⚠️ `mutable`关键字放在参数列表后，返回类型前
* ⚠️ 按引用捕获的变量是否可以修改，取决于引用是否指向const
* 💡 可变Lambda主要用于需要维护状态的场景

---

<a id="id10"></a>
### ✅ 知识点2.6: 指定返回类型

**理论**
* Lambda使用尾置返回类型
* 当函数体只有return语句时，返回类型可以省略（编译器推断）
* 当函数体包含其他语句时，默认返回void，需要显式指定返回类型

**教材示例代码**
```cpp
// 编译器推断返回类型
transform(v1.begin(), v1.end(), v1.begin(),
          [](int i) { return i < 0 ? -i : i; });

// 需要显式指定返回类型（因为包含if语句）
transform(v1.begin(), v1.end(), v1.begin(),
          [](int i) -> int 
          { 
              if (i < 0) 
                  return -i; 
              else 
                  return i; 
          });
```

**注意点**
* ⚠️ 包含非return语句的Lambda默认返回void
* 💡 当Lambda体复杂时，最好显式指定返回类型
* 🔄 使用尾置返回类型语法：`-> return_type`

---

<a id="id11"></a>
### ✅ 知识点2.7: 捕获引用参数

**理论**
* 有些对象（如ostream）不能复制，只能通过引用或指针捕获
* 引用捕获需要注意对象的生命周期
* 返回Lambda的函数不能返回包含引用捕获的Lambda

**教材示例代码**
```cpp
void biggies(vector<string> &words, 
             vector<string>::size_type sz,
             ostream &os = cout, char c = ' ')
{
    // 其他处理代码...
    
    // 正确：通过引用捕获os（ostream不能复制）
    for_each(words.begin(), words.end(),
             [&os, c](const string &s) { os << s << c; });
}
```

**注意点**
* ⚠️ 必须确保引用捕获的对象在Lambda执行时仍然存在
* ⚠️ 返回Lambda时，不能返回包含引用捕获的Lambda
* 💡 对于不可复制的对象，引用捕获是唯一选择

---

<a id="id12"></a>
## ✅ 知识点3: 绑定参数bind函数

**理论**
* `bind`函数是通用函数适配器，生成新的可调用对象
* 主要用途：调整参数顺序、绑定固定参数值
* 当需要在多个地方使用相同操作时，bind比重复写Lambda更合适

**教材示例代码**
```cpp
// 使用bind生成调用check_size的可调用对象
auto check6 = bind(check_size, _1, 6);
bool b1 = check6("hello"); // 调用check_size("hello", 6)
```

**注意点**
* ⚠️ `bind`定义在`<functional>`头文件中
* 💡 `bind`适合将多元函数适配为一元函数，用于需要一元谓词的算法
* 🔄 `bind`返回的可调用对象可以存储和传递

---

<a id="id13"></a>
### ✅ 知识点3.1: bind基本用法

**理论**
* `bind`调用形式：`auto newCallable = bind(callable, arg_list);`
* `newCallable`是一个新的可调用对象
* `arg_list`是逗号分隔的参数列表，对应原始可调用对象的参数
* 参数可以是值、占位符或表达式

**教材示例代码**
```cpp
// 绑定check_size的第二个参数为sz
auto wc = find_if(words.begin(), words.end(),
                  bind(check_size, _1, sz));
```

**注意点**
* ⚠️ `bind`的参数在绑定时求值并存储
* 💡 `bind`可以创建满足算法参数要求的可调用对象
* 🔄 对于简单操作，Lambda通常更直观；对于复杂操作或多处复用，bind更有优势

---

<a id="id14"></a>
### ✅ 知识点3.2: 使用占位符

**理论**
* 占位符`_n`表示`newCallable`的第n个参数
* 占位符定义在`std::placeholders`命名空间中
* 每个使用的占位符都需要单独的using声明或使用整个命名空间

**教材示例代码**
```cpp
// 为占位符提供using声明
using std::placeholders::_1;

// 或者使用整个命名空间
using namespace std::placeholders;

// 使用占位符绑定参数
auto g = bind(f, a, b, _2, c, _1);
```

**注意点**
* ⚠️ 占位符需要包含`<functional>`头文件
* ⚠️ 占位符从`_1`开始，表示第一个参数
* 💡 使用`using namespace std::placeholders;`可以避免为每个占位符单独声明

---

<a id="id15"></a>
### ✅ 知识点3.3: 参数重排

**理论**
* `bind`可以重新排列参数顺序
* 通过调整占位符位置，可以改变参数传递顺序
* 这在适配不同接口时特别有用

**教材示例代码**
```cpp
// 原始调用：isShorter(a, b)返回a是否比b短
// 使用bind反转参数：实现从长到短排序
sort(words.begin(), words.end(), 
     bind(isShorter, _2, _1)); // 相当于isShorter(b, a)
```

**注意点**
* ⚠️ 参数重排需要仔细对应占位符位置
* 💡 参数重排可以复用现有函数，避免编写新函数
* 🔄 占位符的位置决定了`newCallable`参数如何映射到原始函数

---

<a id="id16"></a>
### ✅ 知识点3.4: 绑定引用参数

**理论**
* 默认情况下，`bind`的参数被复制到返回的可调用对象中
* 对于不可复制的对象（如ostream），需要使用`ref`或`cref`函数
* `ref`返回对象的引用包装，可以复制

**教材示例代码**
```cpp
// 错误：尝试复制os
for_each(words.begin(), words.end(),
         bind(print, os, _1, ' '));

// 正确：使用ref传递引用
for_each(words.begin(), words.end(),
         bind(print, ref(os), _1, ' '));
```

**注意点**
* ⚠️ `ref`和`cref`也定义在`<functional>`头文件中
* ⚠️ `ref`用于非const引用，`cref`用于const引用
* 💡 当需要绑定不能复制的对象时，必须使用`ref`或`cref`

---

## 🔑 核心要点总结

1. **谓词是自定义算法的关键**：通过传递谓词函数，可以改变算法的默认行为，实现自定义排序、查找等操作

2. **Lambda表达式提供就地定义函数的能力**：
   - 基本语法：`[捕获列表](参数列表)->返回类型{函数体}`
   - 捕获列表控制对局部变量的访问（按值/按引用）
   - 简单Lambda可省略参数列表和返回类型

3. **捕获机制区分不同使用场景**：
   - 按值捕获：创建时复制，后续修改不影响Lambda内值
   - 按引用捕获：直接引用变量，需注意生命周期
   - 隐式捕获：让编译器推断捕获的变量

4. **bind函数用于参数绑定和适配**：
   - 绑定固定参数值，减少函数参数数量
   - 使用占位符`_n`重新排列参数顺序
   - 通过`ref`/`cref`绑定不可复制的对象

5. **Lambda vs bind选择原则**：
   - 简单、一次性操作：使用Lambda
   - 复杂操作或多处复用：考虑使用bind适配现有函数
   - 需要捕获局部变量：优先使用Lambda

## 📌 考试速记版

**口诀**：Lambda就地定义，bind适配复用

**关键对比**：
| 特性 | Lambda | bind |
|------|--------|------|
| 定义位置 | 使用处就地定义 | 适配现有函数 |
| 局部变量访问 | 通过捕获列表 | 通过参数绑定 |
| 参数重排 | 直接定义参数顺序 | 使用占位符重排 |
| 典型用途 | 简单一次性操作 | 适配函数接口 |

**必记规则**：
1. Lambda捕获列表必须包含要使用的局部非static变量
2. 按值捕获在Lambda创建时复制，按引用捕获直接引用
3. bind默认复制参数，不可复制对象需用ref/cref
4. 占位符`_n`对应新可调用对象的第n个参数
5. 稳定排序保持相等元素的原始顺序