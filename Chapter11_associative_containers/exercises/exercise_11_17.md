## 📊 练习批改与分析

### Exercise 11.17 迭代器适配器合法性分析

**原题：** 
Assuming c is a multiset of strings and v is a vector of strings, explain the following calls. Indicate whether each call is legal:

```
copy(v.begin(), v.end(), inserter(c, c.end()));
copy(v.begin(), v.end(), back_inserter(c));
copy(c.begin(), c.end(), inserter(v, v.end()));
copy(c.begin(), c.end(), back_inserter(v));
```

**你的答案：**
```
1. 第一个使用inserter正确， 实现效果就是依次在c的尾后追加
2. 正确， 效果同样类似于在c的尾后追加
3. 正确，c可以通过key的字母升序来遍历
4. 正确，c可以通过key的字母升序来遍历
```

**批改：** ⭐⭐⭐ 3/5 基本思路正确，但对迭代器适配器的适用性理解不足

**详细分析：**
- ✅ **第1题判断正确**：正确识别了`inserter`对multiset的适用性
- ❌ **第2题判断错误**：`back_inserter`不能用于multiset，因为它需要容器有`push_back`方法
- ✅ **第3、4题判断基本正确**：但解释不完整，需要更详细说明

**正确答案分析：**

1. **`copy(v.begin(), v.end(), inserter(c, c.end()));`**
   - ✅ **合法**：`inserter`使用容器的`insert`方法，multiset有`insert`方法
   - 效果：将vector中的所有元素插入到multiset中（按排序顺序存储）

2. **`copy(v.begin(), v.end(), back_inserter(c));`**
   - ❌ **不合法**：`back_inserter`需要容器有`push_back`方法
   - multiset是关联容器，没有`push_back`方法

3. **`copy(c.begin(), c.end(), inserter(v, v.end()));`**
   - ✅ **合法**：`inserter`使用容器的`insert`方法，vector有`insert`方法
   - 效果：将multiset中排序好的元素插入到vector末尾

4. **`copy(c.begin(), c.end(), back_inserter(v));`**
   - ✅ **合法**：`back_inserter`需要容器有`push_back`方法，vector有`push_back`方法
   - 效果：将multiset中排序好的元素追加到vector末尾


---
