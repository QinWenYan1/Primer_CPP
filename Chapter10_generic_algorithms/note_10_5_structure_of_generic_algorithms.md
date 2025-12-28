# 📘 10.5 通用算法的结构 (Structure of Generic Algorithms)

> 来源说明：C++ Primer 10.5 | 本节涵盖：迭代器类别、算法参数模式及命名约定

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 迭代器类别概述与分类方式*](#id1)
* [*知识点2: 五种迭代器类别的层次关系*](#id2)
* [*知识点3: 输入迭代器*](#id3)
* [*知识点4: 输出迭代器*](#id4)
* [*知识点5: 前向迭代器*](#id5)
* [*知识点6: 双向迭代器*](#id6)
* [*知识点7: 随机访问迭代器*](#id7)
* [*知识点8: 算法参数模式*](#id8)
* [*知识点9: 算法命名约定*](#id9)

---

<a id="id1"></a>
## ✅ 知识点1: 迭代器类别概述与分类方式

**理论**
* **理解算法的关键**：每个算法本质上就是一份"需求清单"(operation list)，告诉你它需要迭代器(iterator)提供哪些操作能力。
* **简单算法需求少**：像 `find` 这样的算法很"朴素"，它只需要迭代器做三件事：
  1. 能通过迭代器访问元素
  2. 能让迭代器往前走一步(increment)
  3. 能比较两个迭代器是不是指向同一个地方(equality comparison)
* **复杂算法需求多**：相比之下，`sort` 算法就很"挑剔"，它需要：
  1. 能读取元素值(read)
  2. 能写入元素值(write)
  3. 能随机跳到任意位置(random access)
* **五大类别**：根据这些需求差异，迭代器被分成**五大迭代器类别**(five iterator categories)。
* **明确要求**：每个算法都会明确告诉你要提供什么类别的迭代器。

**核心对照表**
| 迭代器类别(Iterator Category) | 一句话说清楚 |
|---|---|
| **输入迭代器(Input Iterator)** | **只能看不能改，看一遍就结束** |
| **输出迭代器(Output Iterator)** | **只能改不能看，改一次就完事** |
| **前向迭代器(Forward Iterator)** | **能看能改，还能多看几遍** |
| **双向迭代器(Bidirectional Iterator)** | **能看能改，还能往前看也能往后看** |
| **随机访问迭代器(Random-access Iterator)** | **能看能改，想看哪就看哪，还能算距离** |

**注意点**
* 🔄 **另一种分类思路**：你还可以根据算法"对数据做什么"来分类：是只读数据？是修改数据？还是重新排列元素(reorder the elements)？
* 📖 **系统学习**：想全面了解所有算法？原书附录Appendix A已经按这种思路帮你整理好了
* 📋 **还有更多约定**：除了迭代器类别，算法还有很多其他约定俗成的规则，后面会慢慢讲

---

<a id="id2"></a>
## ✅ 知识点2: 五种迭代器类别的层次关系

**理论**
* **迭代器也有"基本操作"**：就像所有容器(containers)都有一些共同的方法，所有迭代器也都有一些基本的操作。
* **不同迭代器能力不同**：但有些高级操作只有特定迭代器才有。
  * **例子**：`ostream_iterator` 就像个"初级员工"，只会三样：往前走一步(increment)、取值(dereference)、赋值(assignment)。
  * **例子**：`vector` 的迭代器就像个"全能选手"，除了基本三样，还会：往后退一步(decrement)、比较位置(relational operators)、做算术运算(arithmetic operators)。
* **能力有高下之分**：迭代器按照能力高低排成队。
  * **重要规则**：高级迭代器**包含**低级迭代器的所有能力（输出迭代器是个例外）。
* **算法有最低要求**：每个算法都会写明"我需要至少什么级别的迭代器"(minimum category)。
  * `find`：我只需要最基础的"输入迭代器"(Input Iterator)，因为我就是简单地找东西。
  * `replace`：我需要"前向迭代器"(Forward Iterator)，因为我要一边读一边写。
  * `replace_copy`：前两个参数要"前向迭代器"(Forward Iterator)，第三个目标参数至少要"输出迭代器"(Output Iterator)。
* **硬性规定**：**必须提供算法要求的最低级别或更高级别的迭代器**，给低级别的就错了。

**注意点**
* ⚠️ **小心编译器不提醒**：很多编译器很"宽容"，即使你给错了迭代器类型，它也不报错，但程序运行时可能出问题。

---

<a id="id3"></a>
## ✅ 知识点3: 输入迭代器

**理论**
* **这是最基础的"只读"迭代器**：就像书店里只能看不能买的读者。
* **必须会的基本功**：
  1. **比较位置**：能判断两个迭代器是不是指向同一个地方(equality and inequality operators: `==`, `!=`)。
  2. **往前走**：能移动到下一个位置(prefix and postfix increment: `++`)。
  3. **读取内容**：能看看当前位置有什么(dereference operator: `*`)，但**只能看不能拿走**。
  4. **访问成员**：如果指向的是对象，还能访问对象的成员(arrow operator: `->` as a synonym for `(*it).member`)。
* **重要限制**：
  * **只能顺序看**：必须从前往后一个接一个地看。
  * **看完就忘**：不能"暂停"后过一会儿再接着看，因为迭代器状态可能已经失效
    * 我们无法保存迭代器状态或者检验这些元素通过保存的迭代器
  * **一次过**：只能完整地看一遍，不能反复看(single-pass algorithms)。
* **常见用途**：`find` 和 `accumulate` 算法用它；`istream_iterator` 就是典型的输入迭代器。

**注意点**
* 🔄 **能力排行榜的底层**：输入迭代器几乎是能力最弱的（只比输出迭代器强一点）。

---

<a id="id4"></a>
## ✅ 知识点4: 输出迭代器

**理论**
* **和输入迭代器"相反"**：如果输入迭代器是"读者"，输出迭代器就是"写手"。
* **必须会的基本功**：
  1. **往前走**：能移动到下一个位置(prefix and postfix increment: `++`)。
  2. **写入内容**：能在当前位置写东西(dereference: `*`)，但**只能写在赋值号的左边**。
* **重要限制**：
  * **只能写一次**：每个位置**只能写一次**，不能反复写。
  * **不能回头看**：写完了就不能回头检查写的是什么。
  * **一次过**：也是只能一次性从头写到尾(single-pass algorithms)。
* **常见用途**：**专门用来接收算法的输出结果**；`copy` 的第三个参数就是它；`ostream_iterator` 是典型的输出迭代器， 经常用于作为destination

**注意点**
* ⚠️ **单向输出管道**：把它想象成一个只能出不能进的管道，数据从算法流向目标位置。

---

<a id="id5"></a>
## ✅ 知识点5: 前向迭代器

**理论**
* **升级版迭代器**：既继承了输入迭代器的"读"能力，又继承了输出迭代器的"写"能力。
* **关键进步**：
  * **能反复读写**：同一个位置可以读多次、写多次。
  * **能"暂停"**：**可以保存**当前状态，过一会儿再回来继续。
* **这意味着**：**使用前向迭代器的算法可以对数据做多轮处理**(multi-pass algorithms)。
* **常见用途**：`replace` 算法用它；`forward_list` 容器的迭代器就是前向迭代器。

**注意点**
* 🔄 **质的飞跃**：从"一次过"(single-pass)到"反复看"(multi-pass)，这是前向迭代器和输入/输出迭代器的根本区别。

---

<a id="id6"></a>
## ✅ 知识点6: 双向迭代器

**理论**
* **更灵活的迭代器**：在前向迭代器的基础上，**增加了后退的能力**。
* **新增技能**：**既能往前移动(increment: `++`)，也能往后移动(decrement: `--`)**。
* **这很实用**：很多算法需要来回遍历数据。
* **大多数容器都支持**：除了 `forward_list`，其他标准库容器(containers)的迭代器至少都是双向迭代器。
* **常见用途**：`reverse` 算法必须用它，因为反转需要前后来回移动。

**注意点**
* 💡 **很常见**：实际编程中，你用到的大部分迭代器都是双向迭代器或更好的。

---

<a id="id7"></a>
## ✅ 知识点7: 随机访问迭代器

**理论**
* **迭代器中的"战斗机"**：能力最全面，使用最方便。
* **在双向迭代器基础上新增了三大能力**：
  1. **任意跳转**：可以直接跳到任意位置(addition and subtraction operators: `+`, `+=`, `-`, `-=` on an iterator and an integral value)。
  2. **计算距离**：能算出两个迭代器之间隔了多少个元素(subtraction operator: `-` when applied to two iterators)。
  3. **下标访问**：可以用 `iter[n]` 直接访问第n个元素(subscript operator: `iter[n]` as a synonym for `*(iter + n)`)。
* **效率极高**：访问任意位置都是**常数时间**(constant-time access)，就像数组下标一样快。
* **谁有这种能力**：
  * `array`, `deque`, `string`, `vector` 的迭代器。
  * 普通数组的指针也是随机访问迭代器。
* **常见用途**：`sort` 算法必须用它，因为排序需要频繁地随机访问元素。

**注意点**
* ⚠️ **注意限制**：`list` 和 `forward_list` **没有**随机访问迭代器，所以它们不能用 `sort` 算法。

---

<a id="id8"></a>
## ✅ 知识点8: 算法参数模式

**理论**
* **算法调用的"标准姿势"**：大多数算法都遵循下面四种格式之一：
  ```
  // 最基本格式：一个输入范围
  alg(beg, end, other args);
  
  // 带输出目标(destination iterator)：处理完的数据存到哪里
  alg(beg, end, dest, other args);
  
  // 带第二个序列(second input sequence)：处理两个序列的关系
  alg(beg, end, beg2, other args);
  
  // 两个完整序列：精确控制两个序列
  alg(beg, end, beg2, end2, other args);
  ```
* **关于输出目标(dest)**：
  * 算法**假设**目标位置有足够空间，不会越界。
  * 如果 `dest` 直接指向容器，就覆盖原有元素。
  * **更安全的做法**：用插入迭代器(insert iterator)或 `ostream_iterator`，它们会自动扩展空间。
* **关于第二个序列(second input sequence)**：
  * **最规范**：同时提供 `beg2` 和 `end2`，明确给出第二个序列的范围。
  * **简写形式**：只给 `beg2`，算法**默认**第二个序列和第一个序列一样长。

**注意点**
* ⚠️ **两个重要假设**：
  1. **空间足够**：算法认为你提供的输出位置有足够空间。
  2. **序列等长**：如果只给 `beg2`，算法假设第二个序列至少和第一个一样长。
* 💡 **安全第一**：用插入迭代器(insert iterator)最保险，不用担心空间不够。

---

<a id="id9"></a>
## ✅ 知识点9: 算法命名约定

**理论**
* **标准库的"命名哲学"**：看名字就知道这个算法怎么用。

### 第一种：重载版本(Overloading to Pass a Predicate)
* **适用于**：只需要替换比较方式的算法。
* **例子**：
  ```cpp
  unique(begin, end);           // 默认用 `==` 比较
  unique(begin, end, comp); // 用自定义比较函数(comparison function)比较
  ```
* **为什么能重载**：参数个数不同，编译器能分清。

### 第二种：加 `_if` 后缀(_if Versions)
* **适用于**：把"具体值"换成"判断条件"(predicate)的算法。
* **例子**：
  ```cpp
  find(begin, end, 42);         // 找数值42
  find_if(begin, end, pred); // 找符合条件(predicate)的所有元素
  ```
* **为什么不重载**：两个版本参数个数相同，重载会混淆，所以用不同名字。

### 第三种：加 `_copy` 后缀(Distinguishing Versions That Copy)
* **适用于**：不想修改原数据，想要个副本。
* **例子**：
  ```cpp
  reverse(begin, end);               // 原地反转
  reverse_copy(begin, end, dest); // 反转后存到目标位置(destination)，原数据不变
  ```

### 第四种：组合使用
* **最灵活**：`_copy` 和 `_if` 可以组合。
* **例子**：
  ```cpp
  // 从v1中删除所有奇数（直接修改v1）
  remove_if(v1.begin(), v1.end(), [](int x){ return x % 2; });
  
  // 把v1中所有偶数复制到v2（v1不变）
  remove_copy_if(v1.begin(), v1.end(), back_inserter(v2),
                 [](int x){ return x % 2; });
  ```

**实用例子**
```cpp
// 实际使用场景：
// 1. 找出第一个大于10的数
auto it = find_if(vec.begin(), vec.end(), [](int x){ return x > 10; });

// 2. 把vec中所有偶数复制到新容器
vector<int> evens;
remove_copy_if(vec.begin(), vec.end(), back_inserter(evens),
               [](int x){ return x % 2; });  // 注意：remove_copy_if是"保留不满足条件的"
```

**注意点**
* 💡 **命名规律总结**：
  - 默认版本：最简名字。
  - 自定义比较：同名重载(overloading)。
  - 用条件(predicate)代替值：加 `_if`。
  - 输出到别处：加 `_copy`。
  - 既用条件又输出到别处：`_copy_if`。
* 🔄 **设计精妙**：这种命名让代码几乎可以"自解释"(self-explanatory)，看一眼就知道在干什么。

---

## 🔑 核心要点总结
1.  **算法的能力取决于迭代器**：算法能做什么，取决于你给它什么样的迭代器。
2.  **迭代器分等级**：从只能看一遍的输入迭代器(Input Iterator)，到能随意跳转的随机访问迭代器(Random-access Iterator)，能力层层递进。
3.  **记住四个模板**：大多数算法调用都遵循那四种固定格式(parameter patterns)。
4.  **看名字知功能**：`_if` 表示用条件判断(predicate)，`_copy` 表示不修改原数据。

## 📌 考试速记版
* **五类迭代器(Five Iterator Categories)**：
  - 输入(Input)：只读，一次过(single-pass)。
  - 输出(Output)：只写，一次过(single-pass)。
  - 前向(Forward)：读写，可反复(multi-pass)。
  - 双向(Bidirectional)：可进退(increment and decrement)。
  - 随机访问(Random-access)：想哪去哪(full iterator arithmetic)。
* **算法要求**：
  - `find` → 输入迭代器(Input Iterator)。
  - `replace` → 前向迭代器(Forward Iterator)。
  - `reverse` → 双向迭代器(Bidirectional Iterator)。
  - `sort` → 随机访问迭代器(Random-access Iterator)。
* **参数模式(Parameter Patterns)**：`(beg, end, ...)` 是基础，加 `dest` 是输出，加 `beg2` 是第二序列(second input sequence)。
* **命名规律(Naming Conventions)**：
  - 默认：基本功能。
  - `_if`：用条件(predicate)代替具体值。
  - `_copy`：输出副本，保留原数据。
* **重要提醒**：
  - 给算法提供迭代器时，**宁强勿弱**。
  - 编译器可能不检查迭代器类型错误。
  - 用插入迭代器(insert iterator)最安全，不用担心空间不够。

**记忆口诀**：
> 迭代器，五兄弟，能力高低要记清。
> 算法调用四模板，看到名字知功能。
> 输入输出一次过(single-pass)，前向双向多遍行(multi-pass)。
> 随机访问最强大，排序算法必须用。
> 命名后缀有意义，if条件(predicate)copy副本。
> 编译器，不提醒，自己小心别错用。