## 📊 练习批改与分析

### Exercise 13.29 解释swap递归调用问题

**原题：**  
Exercise 13.29: Explain why the calls to swap inside swap(HasPtr&, HasPtr&) do not cause a recursion loop.

**你的答案：**  
因为参数不同防止了递归发生的可能，我们implement的function是两个相同类参数，然而里面调用的可不是，里面调用的一般都是这个类的成员，因此并不会造成递归

**批改：** ⭐⭐⭐ 3/5  
基本理解正确，但解释不够精确和完整，存在一些概念模糊之处。

**详细分析：**
- ✅ **基本思路正确**：你意识到了内部调用的swap与自定义的swap参数不同，这是正确的方向。
- ⚠️ **概念表达不够准确**：你说"里面调用的一般都是这个类的成员"，这并不准确。在`swap(HasPtr&, HasPtr&)`内部，我们通常调用的是`std::swap`或通过ADL找到的针对成员类型的swap，而不是类的成员函数。
- ⚠️ **缺少关键机制说明**：没有提到命名空间和参数依赖查找（ADL）这两个关键机制。
- ⚠️ **表达可以更清晰**：答案的组织和术语使用可以进一步优化。

**正确答案：**
```cpp
// 以HasPtr类为例，假设有int*指针和一个int类型成员
class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    // ...
private:
    int *ptr;
    int val;
};

// 自定义的swap函数
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;           // 关键：使std::swap可见
    swap(lhs.ptr, rhs.ptr);    // 调用std::swap<int*>
    swap(lhs.val, rhs.val);    // 调用std::swap<int>
    // 不会递归调用swap(HasPtr&, HasPtr&)
}
```

---