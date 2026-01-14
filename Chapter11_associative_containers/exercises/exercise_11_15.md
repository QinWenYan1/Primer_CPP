## 📊 练习批改与分析

### Exercise 11.15 映射类型定义

**原题：** What are the mapped_type, key_type, and value_type of a map from int to vector<int>?

**你的答案：**
```
mapped_type在本例子种指的是就是pair<const int, vector<int>>
key_type显而易见的就是const int, value_type就是vector<int>
```

**批改：** ⭐ 1/5 答案存在概念性错误，需要重新学习map的类型定义

**详细分析：**
- ❌ **概念理解错误**：对`mapped_type`、`key_type`和`value_type`的定义理解有误
- ❌ **术语混淆**：混淆了map容器中不同类型别名的含义
- ✅ **部分正确**：意识到`const`和`pair`的存在，但分配位置错误

**正确答案：**
对于`std::map<int, std::vector<int>>`：
- `key_type`: `int` (键的类型)
- `mapped_type`: `std::vector<int>` (值的类型)
- `value_type`: `std::pair<const int, std::vector<int>>` (存储的元素类型)

---