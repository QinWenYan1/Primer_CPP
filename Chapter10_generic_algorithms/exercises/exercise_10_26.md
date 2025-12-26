# 📊 练习批改与分析

### Exercise 10.26 解释三种插入迭代器的区别

**原题：** Explain the differences among the three kinds of insert iterators.

**你的答案：**
```
三者调用的容器操作不一样一个是push_back, 一个是push_front, 还有一个是insert
同时， inserter还有一点特殊的是，插入元素后， 插入器会自动更新指向到原来的元素上， 相对位置不变。 但是其它两个不会这样， 相对位置会改变
```

**批改：** ⭐⭐⭐⭐ 4/5 答案基本正确，抓住了核心区别，但表述可以更精确完整

**详细分析：**
- ✅ **核心概念正确**：准确地指出了三种插入迭代器调用不同的容器操作
- ✅ **关键差异识别**：正确地指出了`inserter`的特殊行为（保持迭代器指向原位置）
- ⚠️ **术语准确性**：使用了中文描述，但专业术语使用可以更规范
- ⚠️ **完整性**：缺少对三种插入迭代器适用容器类型的说明

**正确答案（详细解释）：**

三种插入迭代器的区别如下：

1. **back_insert_iterator (back_inserter)**
   - 调用容器的`push_back`操作
   - 只能在支持`push_back`的容器上使用（如`vector`、`deque`、`list`、`string`）
   - 总是在容器末尾插入元素
   - 插入后迭代器指向新插入的元素之后

2. **front_insert_iterator (front_inserter)**
   - 调用容器的`push_front`操作
   - 只能在支持`push_front`的容器上使用（如`deque`、`list`、`forward_list`）
   - 总是在容器开头插入元素
   - 插入后迭代器指向新插入的元素之后

3. **insert_iterator (inserter)**
   - 调用容器的`insert`操作
   - 可以在任何支持`insert`的容器上使用
   - 在指定位置插入元素
   - **关键特性**：插入后迭代器仍指向原来的位置，这使得可以在同一位置连续插入多个元素

