# C++ 关联容器章节核心知识表

根据《C++ Primer》关联容器章节内容，按照指南要求整理的核心知识表如下：

| 类别 | 概念 | 定义 | 关键点 |
|------|------|------|--------|
| **📌 基础概念** | **关联容器 (Associative Container)** | 支持通过键（key）高效查找和检索元素的容器类型。 | • 与顺序容器的核心区别：按键访问 vs. 按位置访问<br>• 核心优势：高效的键值查找 |
|  | **关联数组 (Associative Array)** | 通过键（而非位置）来索引其元素的数组。 | • 本质是键到值的映射<br>• `map` 和 `unordered_map` 是典型实现 |
|  | **严格弱序 (Strict Weak Ordering)** | 关联容器中键的比较关系。允许比较任意两个值以确定其序。 | • 是定义在键上的比较规则<br>• 若 `a` 不小于 `b` 且 `b` 不小于 `a`，则认为两者相等<br>• 有序容器默认使用 `<` 运算符 |
| **🔧 容器分类与特性** | **有序容器 (Ordered Containers)** | 使用比较函数（默认 `<`）按键排序的关联容器。 | • 元素按键的顺序存储和访问<br>• 包括：`map`, `set`, `multimap`, `multiset` |
|  | **无序容器 (Unordered Containers)** | 使用哈希函数和键的 `==` 运算符来组织元素的关联容器。 | • 元素不按特定顺序存储<br>• 性能依赖于哈希函数的质量<br>• 包括：`unordered_map`, `unordered_set`, `unordered_multimap`, `unordered_multiset` |
|  | **唯一键容器 (Unique-key Containers)** | 要求容器内每个键只能出现一次的容器。 | • 容器名中**不含** `multi`<br>• 包括：`map`, `set`, `unordered_map`, `unordered_set` |
|  | **非唯一键容器 (Nonunique-key Containers)** | 允许容器内同一键出现多次的容器。 | • 容器名中**包含** `multi`<br>• 包括：`multimap`, `multiset`, `unordered_multimap`, `unordered_multiset` |
| **🗺️ 映射类容器 (Map)** | **映射 (Map)** | 存储键-值对（key-value pairs）的关联容器，键唯一。 | • 定义关联数组<br>• 键 (`key_type`) 唯一<br>• 解引用迭代器得到 `pair<const key_type, mapped_type>`<br>• 支持下标运算符 `[]` |
|  | **多重映射 (Multimap)** | 允许键重复出现的映射容器。 | • 与 `map` 类似，但键可重复<br>• **不支持**下标运算符 `[]` |
|  | **无序映射 (Unordered_Map)** | 使用哈希表实现、键唯一的映射容器。 | • 无序存储<br>• 键唯一<br>• 支持下标运算符 `[]` |
|  | **无序多重映射 (Unordered_Multimap)** | 使用哈希表实现、允许键重复的映射容器。 | • 无序存储<br>• 键可重复<br>• **不支持**下标运算符 `[]` |
| **🔑 集合类容器 (Set)** | **集合 (Set)** | 仅存储键（key）的有序关联容器，键唯一。 | • `key_type` 与 `value_type` 相同<br>• 键唯一<br>• 通常用于检查成员是否存在 |
|  | **多重集合 (Multiset)** | 允许键重复出现的集合容器。 | • 键可重复<br>• `key_type` 与 `value_type` 相同 |
|  | **无序集合 (Unordered_Set)** | 使用哈希表实现、键唯一的集合容器。 | • 无序存储<br>• 键唯一 |
|  | **无序多重集合 (Unordered_Multiset)** | 使用哈希表实现、允许键重复的集合容器。 | • 无序存储<br>• 键可重复 |
| **📊 关键类型别名** | **键类型 (key_type)** | 容器用于存储和检索值的键的类型。 | • 对于 `map`：是索引类型<br>• 对于 `set`：与 `value_type` 相同 |
|  | **映射类型 (mapped_type)** | 在 `map` 类容器中，与键关联的值的类型。 | • 仅适用于 `map` 和 `multimap`（及其无序版本） |
|  | **值类型 (value_type)** | 容器中存储的元素的类型。 | • 对于 `set`/`multiset`：与 `key_type` 相同<br>• 对于 `map`/`multimap`：是 `pair<const key_type, mapped_type>` |
| **⚙️ 核心机制** | **哈希 (Hash)** | 无序容器使用的库模板，用于管理元素的位置。 | • 基于 `hash<key_type>` 类型的对象 |
|  | **哈希函数 (Hash Function)** | 将给定类型的值映射到整型（`size_t`）的函数。 | • 相等键必须映射到相等整数<br>• 理想情况下，不等键应映射到不等整数 |
| **🔗 对类型 (Pair)** | **对 (Pair)** | 一种模板类型，持有两个名为 `first` 和 `second` 的公有数据成员。 | • `map` 迭代器解引用得到 `pair`<br>• `first` 是 `const key_type`，`second` 是 `mapped_type` |
| <b>⚡ 操作符特性</b> | <b> 解引用运算符</b> | 应用于关联容器迭代器时，返回 `value_type`。 | • 对于 `map`/`multimap`，返回 `pair` |
|  | **[] 下标运算符** | 仅针对 `map` 和 `unordered_map` 的非常量对象定义。 | • 参数是 `key_type`（或可转换类型）<br>• 返回 `mapped_type` 的引用<br>• **不适用于** `multimap` 和所有 `set` 类容器 |

---
