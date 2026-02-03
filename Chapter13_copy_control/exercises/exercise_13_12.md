# 📘 C++ Primer 第13章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 13.12 | ⭐⭐⭐ 3/5 | 识别了部分析构函数调用，但计数错误且混淆了概念 |

## 🎯 逐题详细评价

### Exercise 13.12 析构函数调用次数分析
**原题：** How many destructor calls occur in the following code fragment?

```cpp
bool fcn(const Sales_data *trans, Sales_data accum){
    Sales_data item1(*trans), item2(accum);
    return item1.isbn() != item2.isbn();
}
```

**你的答案：**
```
总共有4次如果不算对象内部的， trans, accum两个local variable变量
然后还有iterm1, iterm2这两个
```

**批改结果：** ⭐⭐⭐ 3/5
- **概念理解：** ⚠️ 知道函数局部对象会被销毁，但对参数和对象销毁时机理解不准确
- **代码质量：** ⚠️ 无代码，但分析逻辑有误
- **逻辑完整：** ⚠️ 分析不完整，忽略了重要细节
- **表达清晰：** ⚠️ 表达不够清晰，有错别字（"iterm"应为"item"）

**详细分析：**
- ⚠️ **错误计数**：你说有4次，这是不正确的。实际应该有3次析构函数调用。
- ❌ **概念混淆**：你说"trans, accum两个local variable" - trans是指针参数，不是Sales_data对象，不会调用Sales_data的析构函数。
- ✅ **正确识别**：你知道item1和item2作为局部对象会被销毁。
- ⚠️ **分析不完整**：没有分析参数传递方式和对象生命周期。

**正确答案：**
```
在这个代码片段中，会有3次析构函数调用：

详细分析：
1. 参数accum是按值传递的，所以在函数调用时会创建accum的副本（调用拷贝构造函数）
2. 在函数内部，创建了两个局部对象：item1和item2
3. 函数结束时，这三个对象（accum、item1、item2）都会离开作用域，因此：
   - item2被销毁（第一次析构调用）
   - item1被销毁（第二次析构调用）
   - accum被销毁（第三次析构调用）

注意：trans是指针，指针本身是内置类型，没有析构函数。指向的Sales_data对象不会被这个函数销毁。
```

**完整的对象生命周期分析：**
```cpp
bool fcn(const Sales_data *trans, Sales_data accum){ 
    // 1. accum参数：按值传递，调用拷贝构造函数创建形参accum
    
    Sales_data item1(*trans), item2(accum);
    // 2. item1：调用拷贝构造函数（从*trans拷贝）
    // 3. item2：调用拷贝构造函数（从accum拷贝）
    
    return item1.isbn() != item2.isbn();
    // 4. 函数返回，局部对象销毁顺序（与创建顺序相反）：
    //    a) item2被销毁 → 调用析构函数
    //    b) item1被销毁 → 调用析构函数
    //    c) accum被销毁 → 调用析构函数
}
```

---