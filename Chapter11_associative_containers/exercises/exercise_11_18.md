## 📊 练习批改与分析

### Exercise 11.18 显式写出迭代器类型

**原题：** Write the type of map_it from the loop on page 430 without using auto or decltype.

```
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

**你的答案：**
```
map<int, int>::iterator map_it = word_count.cbegin();
```

**批改：** ⭐⭐ 2/5 答案存在多个概念性错误

**详细分析：**
- ❌ **容器类型错误**：题目中的`word_count`是`map<string, size_t>`，不是`map<int, int>`
- ❌ **迭代器类型错误**：`cbegin()`返回const_iterator，不能赋值给iterator
- ✅ **部分结构正确**：理解了需要写出完整的迭代器类型

**正确答案：**
```cpp
std::map<std::string, std::size_t>::const_iterator map_it = word_count.cbegin();
```
---