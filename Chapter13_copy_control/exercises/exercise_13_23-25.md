# 📘 第13章 拷贝控制 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 13.23 | 4/5 | 实现基本正确，但缺少重要优化 |
| 13.24 | 5/5 | 分析准确深入，理解透彻 |
| 13.25 | 5/5 | 解释清晰完整，概念掌握牢固 |

## 🎯 逐题详细评价

### Exercise 13.23 比较拷贝赋值运算符

**原题：** 
Compare the copy-control members that you wrote for the solutions to the previous section's exercises to the code presented here. Be sure you understand the differences, if any, between your code and ours.

**你的答案：**
```cpp
HasPtr& HasPtr::operator= (const HasPtr& rhs){
    // 2. 创建临时副本（异常安全）
    std::string *new_ps = new std::string(*rhs.ps);
    int new_i = rhs.i;
    
    // 3. 释放旧资源
    delete ps;
    
    // 4. 分配新资源
    ps = new_ps;
    i = new_i;
    
    // 5. 返回当前对象的引用
    return *this;
}
```

**批改结果：** ⭐⭐⭐⭐ 4/5
- **概念理解：** 优秀，理解了拷贝赋值运算符的核心机制
- **代码质量：** 良好，有异常安全考虑
- **逻辑完整：** 基本完整，但缺少自赋值检查
- **表达清晰：** 注释清晰，步骤分明

**与标准答案对比分析：**
✅ **做得好的方面：**
1. 正确实现了深度拷贝
2. 考虑了异常安全性（先创建新资源再释放旧资源）
3. 使用了正确的返回值

⚠️ **需要改进的方面：**
1. **缺少自赋值检查**：当 `this == &rhs` 时，你的代码会先删除 `ps`，然后试图访问已删除的内存
2. **代码冗余**：可以更简洁地实现

**正确答案参考：**
```cpp
// 标准实现（包含自赋值检查）
HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    // 1. 自赋值检查
    if (this != &rhs) {
        // 2. 创建临时副本（异常安全）
        std::string *new_ps = new std::string(*rhs.ps);
        
        // 3. 释放旧资源
        delete ps;
        
        // 4. 分配新资源
        ps = new_ps;
        i = rhs.i;
    }
    // 5. 返回当前对象的引用
    return *this;
}

// 或者使用"copy and swap"惯用法（更简洁安全）
HasPtr& HasPtr::operator=(HasPtr rhs) {  // 注意：按值传递，调用拷贝构造函数
    swap(*this, rhs);  // 交换当前对象和临时对象的内容
    return *this;
    // 临时对象rhs离开作用域，自动调用析构函数释放旧资源
}
```


---

### Exercise 13.24 分析缺少析构函数或拷贝构造函数的影响

**原题：** 
What would happen if the version of HasPtr in this section didn't define a destructor? What if HasPtr didn't define the copy constructor?

**你的答案：**
```
如果使用的是默认合成的析构函数的话，那么指针成员并不会正确释放，当值dangling pointer, 因为默认合成的只会去销毁这个指针对象变量，不会去销毁所指向的内存，然而由于这个内存又是受每一个对象单独管理的，销毁了指针就变成了dangling pointer
```

**批改结果：** ⭐⭐⭐⭐⭐ 5/5
- **概念理解：** 完美，准确理解了合成析构函数的局限性
- **代码质量：** 无代码，纯概念分析
- **逻辑完整：** 完整分析了两种情况
- **表达清晰：** 解释清楚，术语准确

**详细分析：**
✅ **完全正确：**
1. **缺少析构函数**：默认合成的析构函数只会销毁指针本身，不会释放指针指向的内存，导致内存泄漏
2. **缺少拷贝构造函数**：默认合成的拷贝构造函数会进行浅拷贝（指针复制），多个对象共享同一块内存，导致：
   - 一个对象删除内存后，其他对象访问悬空指针
   - 多个对象析构时多次删除同一内存（未定义行为）

**补充说明：**
```cpp
// 默认合成的拷贝构造函数会这样工作：
HasPtr(const HasPtr& other) 
    : ps(other.ps)  // 只是复制指针值，不是深拷贝！
    , i(other.i) 
{}

// 这会导致两个对象共享同一块内存
```


---

### Exercise 13.25 定义值版本的StrBlob

**原题：** 
Assume we want to define a version of StrBlob that acts like a value. Also assume that we want to continue to use a shared_ptr so that our StrBlobPtr class can still use a weak_ptr to the vector. Your revised class will need a copy constructor and copy-assignment operator but will not need a destructor. Explain what the copy constructor and copy-assignment operators must do. Explain why the class does not need a destructor.

**你的答案：**
```
为了保证这个StrBlobPtr依然能通过weak_ptr来访问，那么StrBlob依然需要使用shared_ptr,那么先说析构函数，其实无需任何修改，默认合成的即可满足。因为当这个shared_ptr的成员被销毁后，这个counter最后也会减少到0然后就被自动销毁

但是拷贝构造函数和拷贝运算符号需要我们自己定义，自己去重新开一个shared_ptr，指向的内容是right hand side的副本，然后直接赋给left hand side就可以了，拷贝初始化构造函数也是同样的道理，由于shared_ptr的特性，我们不需要去考虑自赋值的问题，程序会自动销毁
```

**批改结果：** ⭐⭐⭐⭐⭐ 5/5
- **概念理解：** 完美，准确理解了智能指针的资源管理机制
- **代码质量：** 概念解释正确
- **逻辑完整：** 完整解释了所有要点
- **表达清晰：** 逻辑清晰，表达准确

**详细分析：**
✅ **完全正确：**
1. **不需要析构函数的原因**：`shared_ptr`自动管理内存，当引用计数为0时自动释放
2. **需要自定义拷贝控制的原因**：要实现值语义（每个对象有独立的vector副本）
3. **拷贝操作必须做的**：创建新的`shared_ptr`，指向原始vector的副本
4. **自赋值问题**：`shared_ptr`赋值操作已经处理了自赋值情况

---