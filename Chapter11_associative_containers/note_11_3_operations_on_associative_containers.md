# 📘 11.3 Operations on Associative Containers (关联容器上的操作)

> 来源说明：C++ Primer 第11.3节 | 本节涵盖：关联容器特有的类型别名、迭代器、增删改查操作，以及一个综合应用示例。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 关联容器额外的类型别名*](#id1)
* [*知识点2: 关联容器迭代器*](#id2)
* [*知识点3: 迭代器遍历关联容器*](#id3)
* [*知识点4: 关联容器与算法*](#id4)
* [*知识点5: 添加元素 (insert)*](#id5)
* [*知识点6: 向 map 添加元素*](#id6)
* [*知识点7: 测试 insert 的返回值*](#id7)
* [*知识点8: 解读返回值语法*](#id8)
* [*知识点9: 向 multiset 或 multimap 添加元素*](#id9)
* [*知识点10: 删除元素 (erase)*](#id10)
* [*知识点11: 对 map 进行下标操作*](#id11)
* [*知识点12: 使用下标操作返回的值*](#id12)
* [*知识点13: 访问元素 (find, count, etc.)*](#id13)
* [*知识点14: 在 multimap 或 multiset 中查找元素*](#id14)
* [*知识点15: 使用 lower_bound 和 upper_bound 的解决方案*](#id15)
* [*知识点16: 使用 equal_range 函数*](#id16)
* [*知识点17: 单词转换程序概述*](#id17)
* [*知识点18: 构建转换映射*](#id18)
* [*知识点19: 生成转换结果*](#id19)

---

<a id="id1"></a>
## ✅ 知识点1: 关联容器额外的类型别名

**理论**
* **核心主旨总结**：关联容器定义了几个额外的类型别名 (Type Aliases)，用以表示其键(key)和值(value)的类型。
    * `key_type` 总是容器的键类型。
    * 对于 `map` 系列，`value_type` 是一个 `pair`，其 `first` 成员是 `const key_type`。
* **具体类型说明**：
    * `key_type`：此容器类型的键的类型。
    * `mapped_type`：每个键关联的值的类型；仅 `map` 类型有此定义。
    * `value_type`：
        * 对于 `set`，与 `key_type` 相同。
        * 对于 `map`，是 `pair<const key_type, mapped_type>`。

**教材示例代码**
```cpp
set<string>::value_type v1;    // v1 is a string
set<string>::key_type v2;    // v2 is a string
map<string, int>::value_type v3;    // v3 is a pair<const string, int>
map<string, int>::key_type v4;    // v4 is a string
map<string, int>::mapped_type v5;    // v5 is an int
```

**注意点**
* ⚠️ **`value_type` 对于 `map` 是一个 `pair`**，并且我们**不能改变元素的关键字(key)**，因此该 `pair` 的 `first` 成员是 `const`。

---

<a id="id2"></a>
## ✅ 知识点2: 关联容器迭代器

**理论**
* **核心主旨总结**：**解引用**一个关联容器迭代器，会得到一个指向容器 `value_type` 的**引用**。
    * 对于 `map`，这意味着得到的是一个 `pair` 的引用，其 `first` 成员是 `const` 的键。
* **访问限制**：可以通过迭代器修改 `map` 元素的值 (`second`)，但不能修改键 (`first`)。

**教材示例代码**
```cpp
// get an iterator to an element in word_count
auto map_it = word_count.begin();
// *map_it is a reference to a pair<const string, size_t> object
cout << map_it->first;    // prints the key for this element
cout << " " << map_it->second;    // prints the value of the element
map_it->first = "new key";    // error: key is const
++map_it->second;    // ok: we can change the value through an iterator
```

**注意点**
* ⚠️ **关键警告**：**必须记住 `map` 的 `value_type` 是一个 `pair`，我们可以改变该 `pair` 的 `value` 成员，但不能改变其 `key` 成员。**

---

<a id="id3"></a>
## ✅ 知识点3: 迭代器遍历关联容器

**理论**
* **核心主旨总结**：`map` 和 `set` 类型提供 `begin` 和 `end` 操作，可以像遍历顺序容器一样使用迭代器遍历它们。
* **遍历顺序**：当使用迭代器遍历一个 `map`、`multimap`、`set` 或 `multiset` 时，迭代器会**按关键字升序**返回元素。

**教材示例代码**
```cpp
// get an iterator positioned on the first element
auto map_it = word_count.cbegin();
// compare the current iterator to the off-the-end iterator
while (map_it != word_count.cend()) {
    // dereference the iterator to print the element key--value pairs
    cout << map_it->first << " occurs "
    << map_it->second << " times" << endl;
    ++map_it; // increment the iterator to denote the next element
}
```

**注意点**
* ⚠️ **`set` 的迭代器是 const 的**：对于 `set` 类型，无论是 `iterator` 还是 `const_iterator`，都只提供对元素的**只读**访问。不能通过 `set` 的迭代器写入元素。
    ```cpp
    set<int> iset = {0,1,2,3,4,5,6,7,8,9};
    set<int>::iterator set_it = iset.begin();
    if (set_it != iset.end()) {
        *set_it = 42; // error: keys in a set are read-only
        cout << *set_it << endl; // ok: can read the key
    }
    ```

---

<a id="id4"></a>
## ✅ 知识点4: 关联容器与算法

**理论**
* **核心主旨总结**：通常**不将通用算法用于关联容器**。
* **原因**：
    1. **键是 const**：关联容器的迭代器（对于 `map` 是 `pair` 的 `first` 为 const，对于 `set` 元素是 const）不能传递给会写入或重排容器元素的算法。
    2. **搜索效率低**：关联容器能通过键快速查找，而像 `find` 这样的通用算法执行的是顺序搜索。使用容器定义的 `find` 成员比调用通用版本要快得多。
* **使用场景**：如果要用，通常将关联容器用作算法的**源序列**或**目的位置**（例如，使用 `copy` 拷贝元素，或使用 `inserter` 绑定一个插入迭代器）。

---

<a id="id5"></a>
## ✅ 知识点5: 添加元素 (insert)

**理论**
* **核心主旨总结**：`insert` 成员用于向关联容器添加**一个**或**一个范围**的元素。
* **对键唯一容器的效果**：对于 `map` 和 `set`，插入一个已存在的元素**没有效果**。
* **`insert` 操作概览**：
    * `c.insert(v)` 或 `c.emplace(args)`：插入 `value_type` 对象。
        * 对于 `map/set`：
            * 仅当键不存在时才插入。
            * 返回一个 `pair`，包含一个指向具有**给定键的元素的迭代器**，以及一个指示插入是否发生的 `bool`。
        * 对于 `multimap/multiset`：总是插入。返回指向新元素的迭代器。
    * `c.insert(b, e)`, `c.insert(il)`：
        * 插入**迭代器范围**或**一个初始化列表值`il`**, 返回 `void`
        * **只插入键第一次出现的元素**。
    * `c.insert(p, v)` 或 `c.emplace(p, args)`：
        * `p` 是一个迭代器，作为搜索新元素存储位置的提示。
        * 返回指向具有给定键的元素的迭代器。

**教材示例代码**
```cpp
vector<int> ivec = {2,4,6,8,2,4,6,8};    // ivec has eight elements
set<int> set2;    // empty set
set2.insert(ivec.cbegin(), ivec.cend());    // set2 has four elements
set2.insert({1,3,5,7,1,2,5,7});    // set2 now has eight elements
```

---

<a id="id6"></a>
## ✅ 知识点6: 向`map`添加元素

**理论**
* **核心主旨总结**：向 `map` 插入元素时，元素类型是 `pair`。有几种方式可以创建这个 `pair` 对象作为 `insert` 的参数。
* **常用方法**：
    * 在新标准中(C++11)，最简单的方法是在参数列表中使用花括号初始化。
    * 也可以使用 `make_pair` 或显式构造 `pair`。

**教材示例代码**
```cpp
// four ways to add word to word_count
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(map<string, size_t>::value_type(word, 1));
```

---

<a id="id7"></a>
## ✅ 知识点7: 测试`insert`的返回值

**理论**
* **核心主旨总结**：
    * 对于键唯一的容器，插入单个元素的 `insert` 或 `emplace` 返回一个 `pair`。
    * 其 `first` 成员是指向具有给定键的元素的迭代器；`second` 成员是一个 `bool`，指示元素是**被插入**(true)还是**已存在**(false)。
* **应用**：可以利用返回值来更新元素。如果键不存在则插入，如果存在则更新其值。

**教材示例代码**
```cpp
// more verbose way to count number of times each word occurs in the input
map<string, size_t> word_count;    // empty map from string to size_t
string word;
while (cin >> word) {
    // inserts an element with key equal to word and value 1;
    // if word is already in word_count, insert does nothing
    auto ret = word_count.insert({word, 1});
    if (!ret.second)    // word was already in word_count
        ++ret.first->second;    // increment the counter
}
```

**代码解析**
* 对于每个单词，尝试用值 1 插入。如果 `word` 已在 `map` 中，`insert` 不做任何事，返回值中的 `bool` 为 `false`。
* 如果 `word` 不在 `map` 中，则插入该字符串并将其计数器值设为 1。
* 如果插入失败（`bool` 为 `false`），则通过返回的迭代器递增已存在元素的计数器。

---

<a id="id8"></a>
## ✅ 知识点8: 解读返回值语法

**理论**
* **核心主旨总结**：理解从 `insert` 返回值中递增计数器的表达式 `++ret.first->second` 需要分解步骤。
* **语法解析**：
    1. `ret` 保存 `insert` 返回的 `pair`。
    2. `ret.first` 是该 `pair` 的第一个成员，是一个指向具有给定键的元素的 `map` 迭代器。
    3. `*ret.first` 解引用该迭代器，获取 `map` 元素（也是一个 `pair`）。
    4. `ret.first->second` 是 `map` 元素 `pair` 的值部分。
    5. `++ret.first->second` 递增该值。

**教材示例代码**
```cpp
++((ret.first)->second); // equivalent expression - 加上括号的等价表达式
// 旧式编译器的声明方式
pair<map<string, size_t>::iterator, bool> ret = word_count.insert(make_pair(word, 1));
```

---

<a id="id9"></a>
## ✅ 知识点9: 向 multiset 或 multimap 添加元素

**理论**
* **核心主旨总结**：由于 `multi` 容器允许重复键，对它们进行 `insert` **总是会插入一个新元素**。
* **返回值**：对于允许多个键的容器，接受单个元素的 `insert` 操作返回**一个指向新元素的迭代器（不返回 `bool`）**。

**教材示例代码**
```cpp
multimap<string, string> authors;
// adds the first element with the key Barth, John
authors.insert({"Barth, John", "Sot-Weed Factor"});
// ok: add the second element with the key Barth, John
authors.insert({"Barth, John", "Lost in the Funhouse"});
```

---

<a id="id10"></a>
## ✅ 知识点10: 删除元素 (erase)

**理论**
* **核心主旨总结**：关联容器定义了三个版本的 `erase`。
* **操作概览**：
    * `c.erase(k)`：从 `c` 中删除每个关键字为 `k` 的元素。返回 `size_type` 类型的值，表示删除的元素数量。
    * `c.erase(p)`：删除迭代器 `p` 指定的元素。`p` 必须指向 `c` 中的一个真实元素。返回一个指向 `p` 之后元素的迭代器。
    * `c.erase(b, e)`：删除迭代器对 `b` 和 `e` 所表示的范围中的元素。返回 `e`。
* **注意**：对于键唯一的容器，`erase(k)` 的返回值总是 0 或 1。对于允许多键的容器，返回值可能大于 1。

**教材示例代码**
```cpp
// erase on a key returns the number of elements removed
if (word_count.erase("removal_word"))
    cout << "ok: " << "removal_word" << " removed\n";
else cout << "oops: " << "removal_word" << " not found\n";

auto cnt = authors.erase("Barth, John"); // 如果 authors 是 multimap，cnt 可能是 2
```

---

<a id="id11"></a>
## ✅ 知识点11: 对 map 进行下标操作

**理论**
* **核心主旨总结**：`map` 和 `unordered_map` 容器提供了下标运算符 `[]` 和对应的 `at` 函数。`set` 类型不支持下标，`multimap` 和 `unordered_multimap` 也不能下标，因为一个键可能对应多个值。
* **下标行为**：与数组或 `vector` 不同，**对一个 `map` 使用下标时，如果关键字 `k` 不在 `map` 中，会创建一个关键字为 `k` 的新元素，并对其进行值初始化**。因此，只能对非 `const` 的 `map` 使用下标操作。
* **操作步骤示例**：`word_count["Anna"] = 1;` 的执行步骤：
    1. 在 `word_count` 中搜索键为 `"Anna"` 的元素，未找到。
    2. 将一个新的键值对插入 `word_count`。键是 `const string` `"Anna"`，值是值初始化的（`size_t` 被初始化为 0）。
    3. 获取新插入的元素，并将其值赋为 1。

**注意点**
* ⚠️ **重要区别**：下标一个 `map` 返回的是 `mapped_type` 对象；而解引用一个 `map` 迭代器返回的是 `value_type` 对象（即一个 `pair`）。

---

<a id="id12"></a>
## ✅ 知识点12: 使用下标操作返回的值

**理论**
* **核心主旨总结**：`map` 的下标运算符返回一个**左值**。因此，我们可以读取或写入元素。
* **潜在问题**：由于下标操作在键不存在时会插入元素，如果只是想检查元素是否存在而不想改变 `map`，则**必须使用 `find`**，而不是下标操作符。

**教材示例代码**
```cpp
cout << word_count["Anna"]; // fetch the element indexed by Anna; prints 1
++word_count["Anna"]; // fetch the element and add 1 to it
cout << word_count["Anna"]; // fetch the element and print it; prints 2
```

---

<a id="id13"></a>
## ✅ 知识点13: 访问元素 (find, count, etc.)

**理论**
* **核心主旨总结**：关联容器提供多种查找给定元素的方法。
* **操作选择**：
    * 如果只关心元素是否存在，最好使用 `find`。
    * 对于键唯一的容器，使用 `find` 或 `count` 差别不大。
    * **对于允许多键的容器，如果不需要计数，最好使用 `find`**，因为 `count` 需要做更多工作（统计相同键的数量）。
* **操作概览 (Table 11.7)**：
    * `c.find(k)`：返回一个指向第一个关键字为 `k` 的元素的迭代器；若未找到，返回尾后迭代器。
    * `c.count(k)`：返回关键字等于 `k` 的元素的数量。
    * `c.lower_bound(k)`：返回一个迭代器，指向第一个关键字**不小于** `k` 的元素。
    * `c.upper_bound(k)`：返回一个迭代器，指向第一个关键字**大于** `k` 的元素。
    * `c.equal_range(k)`：返回一个迭代器 `pair`，表示关键字等于 `k` 的元素范围。若未找到，则两个成员都等于 `c.end()`。

**教材示例代码**
```cpp
set<int> iset = {0,1,2,3,4,5,6,7,8,9};
iset.find(1); // returns an iterator that refers to the element with key == 1
iset.find(11); // returns the iterator == iset.end()
iset.count(1); // returns 1
iset.count(11); // returns 0

// 使用 find 而不是下标来检查元素是否存在
if (word_count.find("foobar") == word_count.end())
    cout << "foobar is not in the map" << endl;
```

**注意点**
* ⚠️ **`lower_bound` 和 `upper_bound` 不适用于无序容器**。
* ⚠️ 下标和 `at` 操作仅适用于非 `const` 的 `map` 和 `unordered_map`。

---

<a id="id14"></a>
## ✅ 知识点14: 在 multimap 或 multiset 中查找元素

**理论**
* **核心主旨总结**：在允许多键的容器中查找元素更复杂，因为可能有多个元素具有相同的键。这些元素在容器中是**相邻存储**的。
* **解决方案一（使用 `count` 和 `find`）**：先调用 `count` 确定元素数量，再调用 `find` 获得指向第一个元素的迭代器，然后通过循环遍历所有具有该键的元素。

**教材示例代码**
```cpp
string search_item("Alain de Botton"); // author we'll look for
auto entries = authors.count(search_item); // number of elements
auto iter = authors.find(search_item); // first entry for this author
// loop through the number of entries there are for this author
while(entries) {
    cout << iter->second << endl; // print each title
    ++iter; // advance to the next title
    --entries; // keep track of how many we've printed
}
```

**注意点**
* 💡 **保证**：迭代遍历一个 `multimap` 或 `multiset` **可以保证按顺序返回所有具有给定键的元素**。

---

<a id="id15"></a>
## ✅ 知识点15: 使用 lower_bound 和 upper_bound 的解决方案

**理论**
* **核心主旨总结**：另一种解决方案是使用 `lower_bound` 和 `upper_bound` 来获取表示具有给定键的元素范围的迭代器对。如果键在容器中，`lower_bound` 返回指向第一个实例的迭代器，`upper_bound` 返回指向最后一个实例之后位置的迭代器。如果键不在容器中，这两个操作返回相等的迭代器（指向可插入该键以保持顺序的位置）。
* **流程**：用 `lower_bound` 初始化 `beg`，用 `upper_bound` 初始化 `end`，然后遍历 `[beg, end)` 范围。

**教材示例代码**
```cpp
// definitions of authors and search_item as above
// beg and end denote the range of elements for this author
for (auto beg = authors.lower_bound(search_item),
          end = authors.upper_bound(search_item);
     beg != end; ++beg)
    cout << beg->second << endl; // print each title
```

**注意点**
* ⚠️ **`lower_bound` 返回的迭代器可能不指向具有给定键的元素**。如果键不在容器中，则 `lower_bound` 指向第一个关键字大于该键的元素（可能是尾后迭代器）。
* ⚠️ **如果 `lower_bound` 和 `upper_bound` 返回相同的迭代器，则表示给定键不在容器中。**

---

<a id="id16"></a>
## ✅ 知识点16: 使用 equal_range 函数

**理论**
* **核心主旨总结**：最直接的解决方案是使用 `equal_range` 函数。它接受一个键，返回一个迭代器 `pair`。如果键存在，`first` 成员指向第一个实例，`second` 成员指向最后一个实例之后的位置。如果未找到，两个迭代器都指向可插入该键的位置。
* **本质**：`equal_range` 返回的 `pair` 的 `first` 成员等价于 `lower_bound` 的返回值，`second` 成员等价于 `upper_bound` 的返回值。

**教材示例代码**
```cpp
// definitions of authors and search_item as above
// pos holds iterators that denote the range of elements for this key
for (auto pos = authors.equal_range(search_item);
     pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl; // print each title
```

---

<a id="id17"></a>
## ✅ 知识点17: 单词转换程序概述

**理论**
* **核心主旨总结**：一个综合示例程序，它使用 `map` 来根据规则转换文本。输入有两部分：规则文件（单词->替换短语）和待转换的文本文件。程序输出转换后的文本。
* **函数分工**：
    * `word_transform`：管理整体处理流程。
    * `buildMap`：读取规则文件并创建转换映射 (`map`)。
    * `transform`：接受一个 `string`，如果存在转换规则则返回其转换，否则返回原字符串。

**教材示例代码 (word_transform 函数)**
```cpp
void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file); // store the transformations
    string text; // hold each line from the input
    while (getline(input, text)) { // read a line of input
        istringstream stream(text); // read each word
        string word;
        bool firstword = true; // controls whether a space is printed
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                cout << " "; // print a space between words
            // transform returns its first argument or its transformation
            cout << transform(word, trans_map); // print the output
        }
        cout << endl; // done with this line of input
    }
}
```

---

<a id="id18"></a>
## ✅ 知识点18: 构建转换映射

**理论**
* **核心主旨总结**：`buildMap` 函数读取规则文件并构建 `map<string, string>`。每条规则由待转换的单词（键）和替换短语（值）组成，可能包含多个单词。
* **实现细节**：使用 `>>` 读取键，`getline` 读取该行的剩余部分作为值。需要跳过键和值之间的空格。如果一行中键后面没有有效内容（值大小小于等于1），则抛出异常。
* **重复键处理**：程序使用下标运算符添加键值对，这意味着如果同一个单词在规则文件中出现多次，**最后出现的规则会覆盖之前的规则**。

**教材示例代码 (buildMap 函数)**
```cpp
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map; // holds the transformations
    string key; // a word to transform
    string value; // phrase to use instead
    // read the first word into key and the rest of the line into value
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1) // check that there is a transformation
            trans_map[key] = value.substr(1); // skip leading space
        else
            throw runtime_error("no rule for " + key);
    return trans_map;
}
```

---

<a id="id19"></a>
## ✅ 知识点19: 生成转换结果

**理论**
* **核心主旨总结**：`transform` 函数执行实际的转换。它在转换 `map` 中查找给定的字符串。如果找到，返回对应的值（替换短语）；否则，返回原字符串。
* **关键点**：使用 `find` 而不是下标操作来查找，因为查找时不应该添加新元素。

**教材示例代码 (transform 函数)**
```cpp
const string &
transform(const string &s, const map<string, string> &m)
{
    // the actual map work; this part is the heart of the program
    auto map_it = m.find(s);
    // if this word is in the transformation map
    if (map_it != m.cend())
        return map_it->second;  // use the replacement word
    else
        return s;    // otherwise return the original unchanged
}
```

---

## 🔑 核心要点总结
1. **类型别名**：关联容器有 `key_type`, `mapped_type` (仅 map), `value_type`。`map` 的 `value_type` 是 `pair<const key_type, mapped_type>`。
2. **迭代器特性**：`map` 迭代器指向 `pair`，可修改 `second` (值)，不可修改 `first` (键)。`set` 迭代器是只读的。
3. **插入元素**：使用 `insert` 或 `emplace`。对于键唯一的容器，返回 `pair<iterator, bool>`，指示插入是否发生。
4. **删除元素**：`erase(k)` 删除所有键为 `k` 的元素，返回删除数量。
5. **下标操作**：仅用于 `map`/`unordered_map`。**如果键不存在，会创建一个新元素**。返回 `mapped_type` 的引用。
6. **查找元素**：使用 `find`, `count`, `lower_bound/upper_bound`, `equal_range`。对于多键容器，相同键的元素相邻存储。
7. **算法使用**：通常不与通用算法一起使用，因为键是 const 且容器有自己的高效查找成员函数。

## 📌 考试速记版
* **`map` 的 `value_type` 是 `pair<const K, V>`**。
* **`set` 的迭代器是 const**，不能写。
* **`insert` 返回 `pair<iter, bool>`** (键唯一容器)，`bool` 表示是否插入成功。
* **`erase(k)` 返回删除的数量**。
* **`map` 的下标 `[]` 会在键不存在时插入元素**，因此检查存在性要用 `find`。
* **多键容器 (`multimap/set`) 中相同键的元素是相邻的**。
* 查找时，`equal_range(k)` 等价于 `{lower_bound(k), upper_bound(k)}`。
* **避免用通用 `find` 算法搜索关联容器**，用成员函数 `find`。

**记忆口诀**：`map` 迭代指向 `pair`，键 `const` 值可改；`set` 迭代只读快，下标 `[]` 慎用来（会插入），查找多用成员 `find`，多键相邻好遍历。