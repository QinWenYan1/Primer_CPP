# 📘 11.4 The Unordered Containers (无序容器)

> 来源说明：C++ Primer 11.4 | 本节涵盖：C++标准库中的四种无序关联容器的定义、特点、使用方法、底层实现（桶和哈希）以及如何为自定义类型定义哈希函数。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 无序容器的定义与特点*](#id1)
* [*知识点2: 使用无序容器*](#id2)
* [*知识点3: 管理桶 (Bucket Management)*](#id3)
* [*知识点4: 无序容器的管理操作接口*](#id4)
* [*知识点5: 无序容器对键类型的要求*](#id5)
* [*知识点6: 为自定义类型定义哈希与比较*](#id6)

---

<a id="id1"></a>
## ✅ 知识点1: 无序容器的定义与特点

**理论**
* **核心主旨总结**：
    * C++11标准定义了四种**无序关联容器(unordered associative containers)**。
    * 与有序容器使用比较操作来组织元素不同，无序容器使用一个**哈希函数(hash function)** 和键类型的 **`==`运算符**来管理元素。
    * 当键类型元素之间**没有明显的顺序关系**，或者维护有序元素的**成本过高时**，无序容器非常有用。
* **性能权衡**：理论上，哈希能提供更好的平均性能，但在实践中要获得好效果通常需要进行大量的性能测试和调整。因此，使用有序容器通常更简单（并且常常能获得更好的性能）。
* **关键建议**：**如果键类型本身是无序的，或者性能测试表明哈希可能解决问题，则使用无序容器。**

**注意点**
* ⚠️ **警告注意**：哈希在<b>平均情况(average case)</b>下性能更好，但实现良好的效果需要调优。
* ⚠️ 无序容器与有序容器（如 `map`, `set`）在接口上相似，但底层实现（哈希 vs. 红黑树）和元素顺序（无序 vs. 有序）不同。

---

<a id="id2"></a>
## ✅ 知识点2: 使用无序容器

**理论**
* **核心主旨总结**：
    * 除了管理哈希的操作外，无序容器提供了与有序容器相同的操作（如 `find`, `insert`）。
    * 这意味着用于 `map` 和 `set` 的操作也适用于 `unordered_map` 和 `unordered_set`。多键版本（如 `unordered_multimap`）也是如此。

* **互换性**：通常可以用无序容器替换对应的有序容器，反之亦然。**但由于元素无序存储，使用无序容器的程序输出通常会与使用有序容器的程序不同。**


**教材示例代码**
```cpp
// count occurrences, but the words won‘t be in alphabetical order
unordered_map<string, size_t> word_count;
string word;
while (cin >> word)
    ++word_count[word]; // fetch and increment the counter for word
for (const auto &w : word_count) // for each element in the map
    // print the results
    cout << w.first << " occurs " << w.second
    << ((w.second > 1) ? " times" : " time") << endl;
```
**代码解析**：
* 将之前的单词计数程序重写为使用 `unordered_map`，唯一的不同是容器的类型。
* 输出结果（单词的出现次数）相同，**但单词的输出顺序不再是字母序**。

**注意点**

* ⚠️ **输出差异**：使用无序容器时，迭代输出的顺序是未定义的（通常与插入顺序和哈希结果有关），而不是排序的。

---

<a id="id3"></a>
## ✅ 知识点3: 管理桶 (Bucket Management)

**理论**
* **核心主旨总结**：无序容器在内部组织为一组**桶(buckets)**，每个桶保存零个或多个元素。容器使用哈希函数将元素映射到桶。
* **访问过程**：访问元素时，容器首先计算元素的**哈希码(hash code)**，以确定搜索哪个桶。具有相同哈希值的元素会被放在同一个桶中。允许重复键的容器会将所有具有相同键的元素放在同一个桶里。
* **性能依赖**：无序容器的性能取决于其**哈希函数的质量(quality of its hash function)** 以及其**桶的数量和大小(number and size of its buckets)**。
* **哈希函数要求**：哈希函数对相同的参数必须始终产生相同的结果。理想情况下，哈希函数将每个特定的值映射到唯一的桶，但允许将不同键的元素映射到同一个桶（哈希冲突）。
* **冲突解决**：当一个桶包含多个元素时，会**顺序搜索(searched sequentially)** 这些元素以找到目标。计算哈希码和查找桶是快速操作，但如果桶内元素过多，则需要多次比较。

**注意点**
* ⚠️ **警告注意**：哈希冲突会导致桶内元素增多，从而降低查找效率（从O(1)退化为O(n)）。


---

<a id="id4"></a>
## ✅ 知识点4: 无序容器的管理操作接口

**理论**
* **核心主旨总结**：无序容器提供了一组函数（见表11.8）来管理桶。这些成员允许我们查询容器的状态，并强制容器在需要时进行重组。

**无序容器管理操作列表**
```

# Bucket Interface
c.bucket_count()    Number of buckets in use.
c.max_bucket_count()  Largest number of buckets this container can hold.
c.bucket_size(n)    Number of elements in the nth bucket.
c.bucket(k)    Bucket in which elements with key k would be found.

# Bucket Iteration
local_iterator    Iterator type that can access elements in a bucket.
const_local_iterator const version of the bucket iterator.
c.begin(n), c.end(n)    Iterator to the first, one past the last element in bucket n.
c.cbegin(n), c.cend(n)    Returns const_local_iterator.

# Hash Policy
c.load_factor()    Average number of elements per bucket. Returns float.
c.max_load_factor()    Average bucket size that c tries to maintain. Adds buckets to keep load_factor <= max_load_factor. Returns float.
c.rehash(n)    Reorganize storage so that bucket_count >= n and bucket_count > size/max_load_factor.
c.reserve(n)    Reorganize so that c can hold n elements without a rehash.
```

**注意点**
* 📋 **术语提醒**：**负载因子(load_factor)** = 元素总数 / 桶数量，是衡量哈希表拥挤程度的指标。
* 💡 **理解技巧**：`rehash`和`reserve`可以用来优化性能，在已知要插入大量元素前预分配足够的桶，避免插入过程中多次重组。

---

<a id="id5"></a>
## ✅ 知识点5: 无序容器对键类型的要求

**理论**
* **核心主旨总结**：默认情况下，无序容器使用键类型的 `==` 运算符比较元素，并使用一个 `hash<key_type>` 类型的对象为每个元素生成哈希码。
* **内置类型的支持**：标准库为内置类型（包括指针）以及一些库类型（如 `string` 和智能指针）提供了 `hash` 模板特化版本。因此，可以直接定义键为这些类型的无序容器。
* **自定义类型的限制**：**不能直接使用自定义类类型作为无序容器的键**。与有序容器不同，不能直接使用 `hash` 模板。必须提供我们自己版本的 `hash` 模板（§16.5），或者提供哈希函数和相等性判断函数。

**注意点**
* ⚠️ **警告注意**：为自定义类型定义无序容器时，必须提供**哈希函数(hash function)** 和**相等性比较(equality comparison)**（除非重载了 `==` 运算符）。


---

<a id="id6"></a>
## ✅ 知识点6: 为自定义类型定义哈希与比较

**理论**
* **核心主旨总结**：可以通过提供函数来替换默认的 `==` 运算符和哈希计算逻辑，从而使用自定义类型（如 `Sales_data`）作为无序容器的键。
* **示例步骤**：
    1. 定义哈希函数 `hasher`：接受自定义类型的常量引用，返回 `size_t`。通常利用已有类型的 `hash` 对象（如 `hash<string>`）来计算成员（如 `isbn`）的哈希值。
    2. 定义相等性比较函数 `eqOp`：接受两个自定义类型的常量引用，返回 `bool`。比较关键成员（如 `isbn`）是否相等。
    3. 定义容器类型：使用 `unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>`。需要指定哈希函数和相等比较函数的指针类型。
    4. 构造容器：创建容器对象时，传入桶大小的初始值以及指向上述两个函数的指针。

**教材示例代码**
```cpp
// 定义哈希函数和相等性比较函数
size_t hasher(const Sales_data &sd)
{
    return hash<string>()(sd.isbn());
}
bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

// 使用类型别名简化声明
using SD_multiset = unordered_multiset<Sales_data,
                    decltype(hasher)*, decltype(eqOp)*>;
// 构造容器，参数为：初始桶数、哈希函数指针、相等比较函数指针
SD_multiset bookstore(42, hasher, eqOp);
```

**注意点**
* 💡 **理解技巧**：`decltype(hasher)*` 获取函数 `hasher` 的指针类型。`hasher` 和 `eqOp` 是函数名，在作为参数传递时会自动转换为函数指针。
* ⚠️ **简化情况**：
    * 如果自定义类已经定义了 `==` 运算符，则只需要提供哈希函数。
    * 使用`using`来使容器类型化繁为简


**教材示例代码 (简化情况)**
```cpp
// use FooHash to generate the hash code; Foo must have an == operator
unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);
```

---

## 🔑 核心要点总结
1.  **无序 vs. 有序**：无序容器（`unordered_*`）使用哈希表和 `==` 运算符组织元素，不保证顺序；有序容器（`map/set`）使用红黑树和 `<` 运算符，保持元素有序。
2.  **接口兼容**：无序容器与对应有序容器的基本操作（如 `find`, `insert`）接口相同，通常可以直接替换，但输出顺序会不同。
3.  **底层实现**：无序容器的性能核心是**哈希函数**和**桶管理**。哈希函数的质量决定了元素分布的均匀性，影响查找效率。
4.  **自定义键类型**：要将自定义类型用作无序容器的键，必须提供**哈希函数**和**相等性比较**（除非已重载 `==`），并在构造容器时传入。
5.  **管理操作**：无序容器提供 `bucket_count()`, `load_factor()`, `rehash(n)` 等接口用于查询和优化内部存储结构。

## 📌 考试速记版
*   **定义**：无序容器 = 哈希函数 + `==` 运算符。无序、平均O(1)查找。
*   **使用**：`unordered_map<string, int>`; 接口同 `map`，但输出无序。
*   **性能关键**：好的哈希函数 → 元素均匀分布 → 桶内元素少 → 查找快。
*   **自定义键**：必须提供**两个函数**（哈希+比较）并传入容器构造函数。
*   **管理函数**：`c.bucket_count()`, `c.load_factor()`, `c.rehash(n)`。
*   **常见错误**：试图将没有定义 `hash` 和 `==` 的自定义类直接用作 `unordered_set` 的键。

**记忆口诀**：无序哈希快，顺序它不爱；自定义类型想进来，哈希等于两手带。