# 📘 第13章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 13.1 | ⭐⭐⭐⭐ | 定义基本正确，但使用时机的描述不完整 |
| 13.2 | ⭐⭐⭐⭐ | 核心点正确，但解释可以更详细 |
| 13.3 | ⭐⭐⭐⭐⭐ | 完全正确，理解深入且表达清晰 |
| 13.4 | ⭐⭐⭐ | 识别出大部分情况，但遗漏了一些拷贝构造函数的使用场景 |

## 🎯 逐题详细评价

### Exercise 13.1: 什么是拷贝构造函数？什么时候使用？
**原题：** What is a copy constructor? When is it used?

**你的答案：**
```
复制构造函数就是， 第一个参数是引用类型， 并且要么没有其他参数， 要没其他参数有默认值的一个构造函数
当我们在复制初始化的时候被调用
```

**批改结果：** ⭐⭐⭐⭐ (4/5)
- **概念理解：** 基本正确，抓住了拷贝构造函数的关键特征
- **代码质量：** 描述性语言，无代码
- **逻辑完整：** 定义了拷贝构造函数，但使用场景描述不够全面
- **表达清晰：** 表达基本清晰，有少量语法错误

**正确答案：**
一个<b>拷贝构造函数(copy constructor)</b>是满足以下条件的构造函数：
1. 第一个参数是**类类型的引用**（通常是`const`引用）
2. 任何额外参数都有默认值
---

### Exercise 13.2: 解释为什么以下声明是非法的
**原题：** Explain why the following declaration is illegal:
```cpp
Sales_data::Sales_data(Sales_data rhs);
```

**你的答案：**
```
第一个参数的类型不是引用不构成复制构造函数
```

**批改结果：** ⭐⭐⭐⭐ (4/5)
- **概念理解：** 核心点正确：参数必须为引用类型
- **代码质量：** 无代码，描述正确
- **逻辑完整：** 答案过于简短，缺少详细解释
- **表达清晰：** 表达清晰但不够详细

**正确答案：**
这个声明非法，因为**拷贝构造函数的参数必须是引用类型**。

具体原因：
1. 当调用拷贝构造函数时，需要将实参传递给形参
2. 如果形参是**非引用类型**，则需要**拷贝构造**这个形参
3. 拷贝形参又需要调用拷贝构造函数，这会导致**无限递归**
4. 因此，C++要求拷贝构造函数的第一个参数必须是**类类型的引用**

**正确声明应为：**
```cpp
Sales_data::Sales_data(const Sales_data &rhs);
```


---

### Exercise 13.3: 拷贝`StrBlob`时会发生什么？拷贝`StrBlobPtrs`时呢？
**原题：** What happens when we copy a `StrBlob`? What about `StrBlobPtrs`?

**你的答案：**
```
StrBlob 中有一个shared_ptr。同时StrBlobPtrs还有一个指向这个shared_ptr的week_ptr。  
如果我们复制StrBlob的时候这个shared_ptr也会被执行复制， 两个StrBlob共享同一块内存， 并且这个shared_ptr的counter会增加为2
同理StrBlobPtrs，也是这样的值不过其中多了一道程序就是week_ptr在复制过去前会去检查这个shared_ptr的指针是否有效，是否这块内存已经被释放， 如果有效就返回这个shared_ptr并把这个counter加1， 无效就返回空指针
```

**批改结果：** ⭐⭐⭐⭐⭐ (5/5)
- **概念理解：** 非常准确，深入理解了智能指针的拷贝语义
- **代码质量：** 描述清晰准确
- **逻辑完整：** 完整描述了拷贝过程中发生的一切
- **表达清晰：** 表达清晰，逻辑连贯

**正确答案：**
你的答案完全正确！补充一些技术细节：

**拷贝`StrBlob`时：**
1. `StrBlob`包含一个`shared_ptr`指向`vector<string>`
2. 拷贝`StrBlob`会调用`shared_ptr`的拷贝构造函数
3. 两个`StrBlob`对象共享同一个`vector<string>`
4. `shared_ptr`的引用计数从1增加到2

**拷贝`StrBlobPtr`时：**
1. `StrBlobPtr`包含一个`weak_ptr`指向`StrBlob`的`shared_ptr`
2. 拷贝`StrBlobPtr`会调用`weak_ptr`的拷贝构造函数
3. 两个`StrBlobPtr`对象共享对同一个`vector<string>`的弱引用
4. `weak_ptr`的拷贝**不会增加**`shared_ptr`的引用计数
5. `weak_ptr`的`lock()`方法用于获取对应的`shared_ptr`，这可能会返回空指针如果底层对象已被销毁



---

### Exercise 13.4: 识别拷贝构造函数的所有使用
**原题：** Assuming Point is a class type with a public copy constructor, identify each use of the copy constructor in this program fragment:
```cpp
Point global;
Point foo_bar(Point arg)
{
    Point local = arg, *heap = new Point(global);
    *heap = local;
    Point pa[4] = { local, *heap };
    return *heap;
}
```

**你的答案：**
```
在调用这个函数foo_bar传入参数的时候使用到了
在初始化local时使用到了
在初始化pa的时候使用到了
在返回*heap的时候使用到了
```

**批改结果：** ⭐⭐⭐ (3/5)
- **概念理解：** 基本正确，但遗漏了一个重要场景
- **代码质量：** 识别出了大部分使用场景
- **逻辑完整：** 遗漏了数组初始化中的一次拷贝构造
- **表达清晰：** 表达清晰，但不够完整

**正确答案：**
在这个代码片段中，**拷贝构造函数被使用了6次**：

1. **函数参数传递**：`Point arg` 在`foo_bar`被调用时，使用拷贝构造函数从实参初始化
2. **局部变量初始化**：`Point local = arg` 使用拷贝构造函数从`arg`初始化`local`
3. **动态对象初始化**：`new Point(global)` 使用拷贝构造函数从`global`初始化堆上的对象
4. **数组元素初始化**：`Point pa[4] = { local, *heap }` 有两个初始化：
   - `pa[0]` 使用拷贝构造函数从`local`初始化
   - `pa[1]` 使用拷贝构造函数从`*heap`初始化
5. **函数返回值**：`return *heap` 使用拷贝构造函数创建返回值

**注意：**
- `*heap = local` 是**赋值操作**，调用的是**拷贝赋值运算符**，不是拷贝构造函数
- 数组`pa`的后两个元素(`pa[2]`和`pa[3]`)使用**默认构造函数**初始化（如果存在的话）

---