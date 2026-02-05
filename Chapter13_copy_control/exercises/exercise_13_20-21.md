# 📘 C++ 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 13.20 | ⭐⭐⭐⭐⭐ | 分析准确，理解深入 |
| Exercise 13.21 | ⭐⭐⭐⭐ | 分析基本正确，但有改进空间 |

## 🎯 逐题详细评价

### Exercise 13.20 解释TextQuery和QueryResult的拷贝、赋值和销毁行为

**原题：**
Explain what happens when we copy, assign, or destroy objects of our TextQuery and QueryResult classes from § 12.3 (p. 484).

**你的答案：**
```
先说TextQuery, 当我们赋值的时候成员file指针同样也会被复制到目标， 并且shared_ptr的计数counter会increment by one
另一个成员wm会被原封不动地复制过去
当销毁的时候， 会调用wm和shared_ptr的析构函数， wm直接销毁， 儿shared_ptr 类的成员指针会被销毁， counter减一， 如果发现counter为0了就会讲指向的内存销毁并释放

然后对于QueryResult， 同理， shared_ptr 和TextQuery是同一个道理， 另外一个成员sought也是直接复制过来， 销毁也是调用其析构函数将其销毁
```

**批改结果：** ⭐⭐⭐⭐⭐

- **概念理解：** ✅ 准确理解了智能指针的引用计数机制和默认拷贝控制成员的行为
- **代码质量：** ✅ 分析完整，考虑了所有成员
- **逻辑完整：** ✅ 涵盖了拷贝、赋值和销毁三种情况
- **表达清晰：** ✅ 解释清楚，逻辑清晰

**详细分析：**

**TextQuery类分析：**
```
class TextQuery {
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
```

1. **拷贝构造：**
   - `file`：复制shared_ptr，引用计数+1
   - `wm`：复制map，其中每个shared_ptr都复制，各自的引用计数+1
   - 结果是两个TextQuery对象共享相同的文件内容和单词映射

2. **拷贝赋值：**
   - 左操作数的`file`引用计数-1（如果减为0则释放资源）
   - 左操作数的`wm`被销毁，其中每个shared_ptr引用计数-1
   - 右操作数的`file`复制到左操作数，引用计数+1
   - 右操作数的`wm`复制到左操作数，每个shared_ptr引用计数+1

3. **销毁：**
   - `file`的析构函数被调用，引用计数-1，如果为0则释放内存
   - `wm`的析构函数被调用，每个元素的shared_ptr引用计数-1，如果为0则释放对应内存

**QueryResult类分析：**
```
class QueryResult {
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};
```

1. **拷贝构造：**
   - `sought`：复制字符串内容
   - `lines`和`file`：复制shared_ptr，引用计数+1

2. **拷贝赋值：**
   - `sought`：赋值运算符复制字符串
   - `lines`和`file`：左操作数的shared_ptr引用计数-1，右操作数的shared_ptr复制过来，引用计数+1

3. **销毁：**
   - `sought`：调用string析构函数释放内存
   - `lines`和`file`：调用shared_ptr析构函数，引用计数-1，如果为0则释放内存

---

### Exercise 13.21 是否需要定义拷贝控制成员

**原题：**
Do you think the TextQuery and QueryResult classes need to define their own versions of the copy-control members? If so, why? If not, why not? Implement whichever copy-control operations you think these classes require.

**你的答案：**
```
我认为不用，因为默认合成的完全够用而且符合逻辑了
```

**批改结果：** ⭐⭐⭐⭐

- **概念理解：** ✅ 基本正确，但可以更深入
- **代码质量：** N/A（未提供实现）
- **逻辑完整：** ⚠️ 可以更详细解释理由
- **表达清晰：** ✅ 观点明确

**详细分析：**

**正确答案：**
两个类都不需要定义自己的拷贝控制成员，原因如下：

1. **TextQuery类：**
   - 成员都是标准库类型或智能指针
   - `std::shared_ptr`管理自己的内存，引用计数机制确保资源安全
   - `std::map`和`std::string`都有正确的拷贝语义
   - 默认合成的拷贝控制成员完全够用

2. **QueryResult类：**
   - 同样，所有成员都有正确的拷贝语义
   - `std::string`和`std::shared_ptr`都能正确处理拷贝和销毁
   - 默认合成的版本完全符合需求
