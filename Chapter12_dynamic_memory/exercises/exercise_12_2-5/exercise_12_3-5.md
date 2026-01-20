# 📘 第12章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 12.3 | ⭐⭐⭐⭐ (4/5) | 答案正确但解释不够详细 |
| Exercise 12.4 | ⭐⭐⭐ (3/5) | 理解有偏差，未抓住核心原因 |
| Exercise 12.5 | ⭐⭐⭐⭐ (4/5) | 优缺点分析基本正确 |

## 🎯 逐题详细评价

### Exercise 12.3 push_back和pop_back的const版本

**原题：**
Does this class need const versions of push_back and pop_back? If so, add them. If not, why aren't they needed?

**你的答案：**
当然不需要， push_back, 和pop_back都需要去修改类中的成员，如果我们真的要使用push_back和pop_back的话，一定就不需要const 版本

**批改结果：** ⭐⭐⭐⭐ (4/5)
- **概念理解：** 基本正确，理解了const成员函数的核心概念
- **代码质量：** 不涉及代码实现
- **逻辑完整：** 回答简洁但不够完整
- **表达清晰：** 表达清晰但缺乏细节

**详细分析：**
✅ **你的理解正确**：`push_back`和`pop_back`确实不需要const版本，因为它们是修改操作的函数

⚠️ **但解释可以更深入**：
1. **const成员函数的语义**：const成员函数承诺不会修改对象状态
2. **修改操作的本质**：`push_back`和`pop_back`都会修改`data`指向的`vector`的内容
3. **语言规则限制**：即使我们声明了const版本的`push_back`，在const函数中也不能修改成员


---

### Exercise 12.4 check函数中为何不检查i是否大于0

**原题：**
In our check function we didn't check whether i was greater than zero. Why is it okay to omit that check?

**你的答案：**
这里我们的check是使用的传入的参数来与现在的vector比较两者大小，这样写泛用性更高

**批改结果：** ⭐⭐⭐ (3/5)
- **概念理解：** 理解有偏差，未抓住核心原因
- **代码质量：** 不涉及代码实现
- **逻辑完整：** 回答不准确
- **表达清晰：** 表达较模糊

**正确答案分析：**
真正的原因是**`size_type`是无符号整数类型**。让我们查看代码：

```cpp
typedef std::vector<std::string>::size_type size_type;
void check(size_type i, const std::string &msg) const;
```

**关键点：**
1. `size_type`是`vector<string>::size_type`的别名，它是`size_t`类型
2. `size_t`是无符号整数类型（unsigned integer type）
3. 无符号整数永远不会小于0，所以`i >= 0`永远为真

---

### Exercise 12.5 构造函数是否应为explicit

**原题：**
We did not make the constructor that takes an initializer_list explicit (§ 7.5.4, p. 296). Discuss the pros and cons of this design choice.

**你的答案：**
优点：能接受更广泛的参数输入，使用限制更少
缺点：可能无法提醒到一些非必要的或者无意的类型转换， 导致计算错误

**批改结果：** ⭐⭐⭐⭐ (4/5)
- **概念理解：** 对explicit关键字的作用理解正确
- **代码质量：** 不涉及代码实现
- **逻辑完整：** 优缺点分析基本全面
- **表达清晰：** 表达清晰准确

**详细分析：**
✅ **优点分析正确**：非explicit构造函数允许更方便的隐式转换
✅ **缺点分析正确**：可能导致意外的类型转换

**补充说明：**

**具体优点（隐式转换的便利性）：**
```cpp
// 如果构造函数是explicit的
StrBlob sb1{"hello", "world"};  // 直接初始化，OK
StrBlob sb2 = {"hello", "world"};  // 拷贝初始化，如果explicit则错误
processStrBlob({"hello", "world"});  // 参数传递，如果explicit则错误

// 如果构造函数不是explicit的，以上所有情况都合法
```

**具体缺点（意外的转换）：**
```cpp
void processStrBlob(const StrBlob& sb) {
    // 处理StrBlob
}

// 意外的转换：传入一个初始化列表，被隐式转换为StrBlob
processStrBlob({"unexpected", "conversion"});
// 程序员可能原本想调用其他重载版本，但编译器选择了这个
```

---