# 📘 Chapter 11 Associative Containers (关联容器)

> 来源说明：C++ Primer Chapter 11 | 本节涵盖：关联容器与顺序容器的核心区别，以及 `map` 和 `set` 的基本用法。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 关联容器与顺序容器的根本区别*](#id1)
* [*知识点2: 关联容器概述及主要类型*](#id2)
* [*知识点3: 八种关联容器的分类维度*](#id3)
* [*知识点4: 关联容器类型表*](#id4)
* [*知识点5: 使用关联容器 - 动机与map概念*](#id5)
* [*知识点6: 使用map的示例 - 单词计数程序*](#id6)
* [*知识点7: 使用set的示例 - 改进的单词计数程序*](#id7)

---

<a id="id1"></a>
## ✅ 知识点1: 关联容器与顺序容器的根本区别

**理论**
* **顺序容器 (sequential container)**，比如 `vector` 和 `list`，数据是按位置（索引）顺序存放和访问的，就像排队。
* **关联容器 (associative container)**，比如 `map` 和 `set`，数据是按键(**key**)来存取的。每个元素都有一个“钥匙”，通过这把“钥匙”可以高效地找到或存放对应的“数据”。
* 简单说，顺序容器是“按号入座”，关联容器是“按键索值”。
* **保持技术准确性**：关联容器支持高效的查找(**lookup**)和检索(**retrieval**)操作。

**注意点**
* 🔄 **知识关联**：理解这个根本区别是学习本章所有后续内容的基础。

---

<a id="id2"></a>
## ✅ 知识点2: 关联容器概述及主要类型

**理论**

* 关联容器就像是一个智能的字典或集合。
* `map` (映射)存储的是“键-值对(**key-value pairs**)”: 你可以通过一个键（如单词）快速找到对应的值（如定义）。它就像一个字典。
* `set` (集合)只存储键(**key**): 它的主要作用是快速判断某个东西（键）是否存在。它就像一个“黑名单”或“白名单”。
* **保持技术准确性**：
  * **map**中的键充当索引，值是与该索引关联的数据。
  * **set**支持高效的查询，判断给定的键是否存在。

**注意点**
* 📋 **术语提醒**：`map` 常被称为**关联数组(associative array)**，因为它像数组，但下标（键）不一定是整数。

---

<a id="id3"></a>
## ✅ 知识点3: 八种关联容器的分类维度

**理论**
* C++标准库提供了8种关联容器，它们可以通过3个问题来区分：
  1. 是 `set` (只有键) 还是 `map` (有键和值)？
  2. **键是否允许重复**？ (是 **unique** 还是 **multi**)
  3. **元素是否按键排序**？ (是 **ordered** 还是 **unordered**)
* **保持技术准确性**：
  * 允许重复键的容器名字包含 `multi`。
  * **不排序**的容器名字以 `unordered` 开头，它们使用<b>哈希函数(hash function)</b>来组织元素。
  * 例如：`unordered_multiset` 是一个允许重复键且不排序的集合；而 `set` 是一个键唯一且排序的集合。

**注意点**
* ⚠️ **警告注意**：无序容器(**unordered containers**)使用哈希函数，这与有序容器的内部实现（通常是红黑树）有根本不同，会影响性能和元素的遍历顺序。

---

<a id="id4"></a>
## ✅ 知识点4: 关联容器类型表

**理论**
* 此表格是理解8种关联容器的关键。

**Associative Container Types**

| 按键有序的集合 | 描述 |
| :--- | :--- |
| `map` | 关联数组；保存键-值对 |
| `set` | 容器中键即值本身 |
| `multimap` | 键可以出现多次的 map |
| `multiset` | 键可以出现多次的 set |

| 无序集合 | 描述 |
| :--- | :--- |
| `unordered_map` | 由哈希函数组织的 map |
| `unordered_set` | 由哈希函数组织的 set |
| `unordered_multimap` | 哈希 map；键可以出现多次 |
| `unordered_multiset` | 哈希 set；键可以出现多次 |

**注意点**
* 📋 **术语提醒**：
  * `map`, `multimap` 定义在头文件 `<map>` 中。
  * `set`, `multiset` 定义在头文件 `<set>` 中。
  * 无序容器定义在 `<unordered_map>` 和 `<unordered_set>` 中。

---

<a id="id5"></a>
## ✅ 知识点5: 使用关联容器 - 动机与map概念

**理论**
* **核心要点通俗化解释**：很多人熟悉`vector`，但可能没用过`map`和`set`。学习使用它们有助于理解这种强大的数据结构。
* **`map`概念深化**：
  * `map` 是键-值对的集合，例如将人名（键）映射到电话号码（值）。
  * 它就像一个特殊的数组，下标可以是字符串等类型，而不是非得是整数。
* **`set`概念深化**：
  * `set` 只是一个键的集合。
  * 最常用于快速判断一个值是否存在，比如一个“坏支票签发者”的黑名单。

**注意点**
* 💡 **理解技巧**：可以把 `map` 想象成一个**电话簿**，把 `set` 想象成一个**会员名单**。

---

<a id="id6"></a>
## ✅ 知识点6: 使用map的示例 - 单词计数程序

**理论**
* **核心要点通俗化解释**：这是一个经典的例子，统计一段输入中每个单词出现的次数。`map` 的键是单词(string)，值是该单词出现的次数(size_t)。
* **保持技术准确性**：
  1. 定义map时需指定键和值的类型：`map<string, size_t>`。
  2. 使用 `map[key]` 可以访问或插入元素。如果`key`不存在，会创建一个键为`key`、值初始化为0的新元素。
  3. 对map迭代时，每个元素是一个 **`pair`类型**的对象，其`.first`成员是键，`.second`成员是值。

**教材示例代码**
```cpp
// count the number of times each word occurs in the input
map<string, size_t> word_count; // empty map from string to size_t
string word;
while (cin >> word)
    ++word_count[word]; // fetch and increment the counter for word
for (const auto &w : word_count) // for each element in the map
    // print the results
    cout << w.first << " occurs " << w.second
         << ((w.second > 1) ? " times" : " time") << endl;
```
*此程序读取输入，并报告每个单词出现的频率。*

**注意点**
* ⚠️ **警告注意**：`word_count[word]` 这个下标操作有一个关键行为：如果 `word` 不在map中，它会**自动插入**一个以 `word` 为键的新元素，并将其值进行**值初始化**（对于`size_t`是0）。然后返回这个值的引用。
* 🔄 **知识关联**：`pair`类型将在后面详细说明（§11.2.3）。

---

<a id="id7"></a>
## ✅ 知识点7: 使用set的示例 - 改进的单词计数程序

**理论**
* **核心要点通俗化解释**：在单词计数基础上，我们想忽略常见词（如“the”，“and”）。我们可以用一个`set`来保存这些需要排除的单词，只统计不在这个集合中的词。
* **保持技术准确性**：
  1. `set` 也是模板，需要指定元素类型：`set<string>`。
  2. 关联容器支持列表初始化。
  3. `set`的 `.find(key)` 成员函数返回一个迭代器。如果找到键，迭代器指向该元素；如果未找到，则返回 `.end()`。通过比较 `find` 的结果是否等于 `.end()`，可以判断键是否存在。

**教材示例代码**
```cpp
// count the number of times each word occurs in the input
map<string, size_t> word_count; // empty map from string to size_t
set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                       "the", "but", "and", "or", "an", "a"};
string word;
while (cin >> word)
    // count only words that are not in exclude
    if (exclude.find(word) == exclude.end())
        ++word_count[word]; // fetch and increment the counter for word
```

**注意点**
* 💡 **理解技巧**：`if (exclude.find(word) == exclude.end())` 这行代码是使用`set`进行成员判定的标准模式。意思是“如果没在`exclude`集合中找到`word`”。
* 📋 **术语提醒**：`.find()` 和 `.end()` 都是容器的成员函数。

---

## 🔑 核心要点总结
1.  **根本区别**：顺序容器按位置访问，关联容器按键(**key**)高效访问。
2.  **两大主角**：`map`存储键值对，像字典；`set`只存储键，像集合/名单，用于快速存在性检查。
3.  **八大类型**：由“set/map”、“键是否唯一(multi)”、“是否有序(unordered)”三个维度组合出8种容器。
4.  **map使用核心**：`map[key]`操作既可访问也可插入元素；迭代map得到的是`pair`，用`.first`和`.second`访问键和值。
5.  **set使用核心**：用 `.find(key) == .end()` 来判断一个键是否不在集合中。

## 📌 考试速记版
* **关键区别**：顺序容器靠位置，关联容器靠键(key)。
* **map vs set**：map存`pair<key,value>`；set只存`key`。
* **下标操作`[]`**：仅适用于`map`和`unordered_map`（非`const`），若key不存在则**插入**一个值初始化的新元素。
* **查找操作`.find()`**：适用于所有关联容器，返回迭代器，未找到时返回`.end()`。
* **头文件**：有序容器在`<map>`/`<set>`；无序容器在`<unordered_map>`/`<unordered_set>`。

**记忆口诀**：`map`一对，`set`一个；`multi`可重，`unordered`不排；访问靠键，查找飞快。