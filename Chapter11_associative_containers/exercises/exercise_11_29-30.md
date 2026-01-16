## 📊 练习批改与分析


---

### Exercise 11.29 边界查找函数的返回值

**原题：** What do upper_bound, lower_bound, and equal_range return when you pass them a key that is not in the container?

**你的答案：**
```
如果键值不存在于容器中的话，那么upper_bound和lower_bound实际上是指向同一个位置，这个位置就是这个新键值应该插入的地方并能保持顺序
同理
equal_range实际上就返回一个pair，first就是upper_bound而second就是lower_bound
```

**批改：** ⭐⭐⭐ 3/5 答案基本正确，但有一些混淆和表述不准确

**详细分析：**
- ✅ **核心概念正确**：理解到当键不存在时，`lower_bound`和`upper_bound`返回相同的位置
- ❌ **表述有混淆**：将`upper_bound`和`lower_bound`的顺序说反了
- ❌ **equal_range描述不准确**：`first`是`lower_bound`，`second`是`upper_bound`

**正确答案：**

对于有序关联容器（`set`、`map`、`multiset`、`multimap`），当传递一个不存在的键时：

1. **lower_bound(key)**：返回第一个**不小于**key的元素迭代器。如果key不存在，则返回第一个大于key的元素迭代器，即key应该插入的位置以保持有序。

2. **upper_bound(key)**：返回第一个**大于**key的元素迭代器。如果key不存在，则同样返回第一个大于key的元素迭代器，即key应该插入的位置以保持有序。

3. **equal_range(key)**：返回一个`pair`，其中`first`是`lower_bound(key)`，`second`是`upper_bound(key)`。

因此，当key不存在时：
- `lower_bound`和`upper_bound`返回相同的迭代器，都指向第一个大于key的元素。
- `equal_range`返回的`pair`中的两个迭代器相等，都指向key应该插入的位置。

---

### Exercise 11.30 equal_range输出表达式的含义

**原题：** Explain the meaning of the operand pos.first->second used in the output expression of the final program in this section.

```cpp
    // definitions of authors and search_item as above
    // pos holds iterators that denote the range of elements for this key
    for (auto pos = authors.equal_range(search_item);
    pos.first != pos.second; ++pos.first)
        cout << pos.first->second << endl; // print each title
```

**你的答案：**
```
pos.first指的就是lower_bound的迭代器，也就是第一个指向键值为它的元素，然后pos.first->second就是将其指向的的元素的mapped_value打印出来一个一个，直到将所有目标键值的元素全部打印出来
```

**批改：** ⭐⭐⭐⭐ 4/5 优秀答案，但可以更精确

**详细分析：**
- ✅ **理解正确**：准确理解了`pos.first`是`equal_range`返回的`pair`的第一个迭代器，即`lower_bound`
- ✅ **功能描述正确**：知道这是在遍历所有匹配键的元素并打印它们的值
- ⚠️ **可以更精确**：需要明确说明这是在`multimap`或`multiset`中，因为键可能重复

**正确答案：**

在给定的代码中：
- `authors` 可能是一个 `multimap<string, string>`，键是作者，值是书名。
- `pos` 是通过 `authors.equal_range(search_item)` 得到的迭代器范围，是一个 `pair<iterator, iterator>`。
  - `pos.first` 指向第一个键等于 `search_item` 的元素（即 `lower_bound` 的返回值）。
  - `pos.second` 指向第一个键大于 `search_item` 的元素（即 `upper_bound` 的返回值）。
- 循环条件 `pos.first != pos.second` 确保只遍历键等于 `search_item` 的元素。
- `pos.first->second` 解引用迭代器，访问当前元素的 `second` 成员，即书名（在 `multimap` 中，每个元素是一个 `pair<const key_type, mapped_type>`）。
- 循环通过 `++pos.first` 移动到下一个元素，直到遍历完所有匹配的元素。

因此，这段代码的作用是打印出所有与 `search_item` 键相关联的书名。

**补充说明：**
如果 `authors` 是 `multimap`，那么同一个作者可能有多本书，`equal_range` 返回的范围包含所有该作者的作品。如果是普通 `map`，则范围最多包含一个元素。

---