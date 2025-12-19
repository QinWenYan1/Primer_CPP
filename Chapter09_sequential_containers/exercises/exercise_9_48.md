# 📘 C++ Primer 练习题评价

## 📊 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 9.48 | 4/5 | 理解正确，细节有小瑕疵 |

---

## 🎯 逐题详细评价

### Exercise 9.48 `string::find()` 返回值问题

**原题：** Given the definitions of name and numbers on page 365, what does `numbers.find(name)` return?

```cpp
string numbers("0123456789"), name("r2d2");
numbers.find(name); 
```

**你的答案：**
> 由于在整个numbers里面没有找到，或者没有出现"r2dr"， 所以会返回 string::npos

**批改结果：** ⭐⭐⭐⭐ 4/5
- **概念理解：** ✅ 正确理解`find()`找不到子串时返回`npos`
- **代码质量：** ✅ 不涉及代码实现
- **逻辑完整：** ⚠️ 打字错误将`r2d2`写成`r2dr`，但核心逻辑正确
- **表达清晰：** ✅ 能清楚说明原因和结果

---

**正确答案：**
```cpp
// numbers.find(name) 返回 string::npos
// 因为name字符串"r2d2"作为一个完整子串，在numbers"0123456789"中不存在
```

