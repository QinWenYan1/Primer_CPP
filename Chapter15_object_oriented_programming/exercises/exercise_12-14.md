## 📘 第15章 练习题评价（15.12-15.14）

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 15.12 | ⭐⭐⭐⭐⭐ (5/5) | 完全正确，理解了override和final的组合价值 |
| 15.13 | ⭐⭐⭐⭐ (4/5) | 正确识别无限递归并提供修复，但可以更详细解释机制 |
| 15.14 | ⭐⭐ (2/5) | 对动态绑定的判断有误，忽略了非虚函数特性及递归问题 |

---

## 🎯 逐题详细评价

### Exercise 15.12: 同时声明为override和final是否有用？

**原题：** Is it ever useful to declare a member function as both `override` and `final`? Why or why not?

**你的答案：**
> 当然有意义，比如你在这个派生类里面重写了这个虚函数后，不希望后续的派生类再去定义对那个类的新表现的时候就可以使用final了

**批改结果：** ⭐⭐⭐⭐⭐ (5/5) 🎉

**详细分析：**
- ✅ **正确理解**：准确指出`final`用于阻止后续派生类进一步重写
- ✅ **场景合理**：描述了中间类固定实现的设计场景
- ✅ **逻辑完整**：解释了为什么这两个关键字可以且应该一起使用（`override`确保确实在重写基类函数，`final`阻止子孙重写）

**补充说明（锦上添花）：**
```cpp
class Base {
public:
    virtual void algorithm() { /* 默认实现 */ }
};

class MidLayer : public Base {
public:
    // 组合使用：确认这是重写，同时固定此实现
    void algorithm() override final { /* 关键优化实现 */ }
};

class Leaf : public MidLayer {
public:
    // void algorithm() override; // 错误：无法重写final函数
};
```

---

### Exercise 15.13: 解释`print`函数并修复问题

**原题：** Given the following classes, explain each print function... If there is a problem in this code, how would you fix it?

**你的答案：**
> 有问题，虽然我们在派生类中可以发现writer其实想先调用基类中的`print`然后调用派生类中的`print`，可是由于signature里面并没有写明，导致编译器会解读为无限递归了，为了解决这个问题，我们写为:
> ```cpp
> virtual void print(ostream &os) override { base::print(os); os << " " << i; }
> ```

**批改结果：** ⭐⭐⭐⭐ (4/5)


**详细机制解释：**
```cpp
class derived : public base {
public:
    // 问题：这里的print(os)调用的是derived::print自身！
    void print(ostream &os) { 
        print(os);  // 无限递归：调用自己，没有终止条件
        os << " " << i; 
    }
    /* 
     * 原因：派生类中的print隐藏了基类print（名字隐藏规则）
     * 在derived::print的作用域内，未限定的print名字查找
     * 只找到derived::print，形成无限递归
     */
    
    // 正确修复：使用作用域解析符明确调用基类版本
    void print(ostream &os) override { 
        base::print(os);  // 先调用基类输出basename
        os << " " << i;   // 再输出派生类特有成员
    }
};
```

---

### Exercise 15.14: 确定运行时调用哪个函数

**原题：** Given the classes from the previous exercise and the following objects, determine which function is called at run time...

```cpp
class base {
public:
    string name() { return basename; }
    virtual void print(ostream &os) { os << basename; }
private:
    string basename;
};

class derived : public base {
public:
    void print(ostream &os) { print(os); os << " " << i; }
private:
    int i;
}; 
```
```cpp
base bobj; base *bp1 = &bobj; base &br1 = bobj;
derived dobj; base *bp2 = &dobj; base &br2 = dobj;
```

(a) `bobj.print();` 
(b) `dobj.print();`
(c) `bp1->name();`
(d) `bp2->name();`
(e) `br1.print();`
(f) `br2.print();`

**你的答案：**
> (a). "bobj"  
> (b). "dobj" << i  
> (c). "bobj"  
> (d). "dobj"  
> (e). "bobj"  
> (f). "dobj " << i

**批改结果：** ⭐⭐ (2/5)


**关键概念纠正：**

```cpp
// 核心概念1：只有虚函数才进行动态绑定
bp2->name();  // name()不是虚函数！
// 静态类型是base*，所以调用base::name()
// 即使想调用derived::name()（如果存在），也需要虚函数机制

// 核心概念2：题目中的代码有严重bug！
dobj.print();  // 调用derived::print
// 内部执行：print(os) → 又调用derived::print → 无限递归
// 正确输出应该是先输出basename（继承成员），再输出i，但实际会崩溃
```

**正确答案：**
```cpp
(a) base::print()        // 输出: basename的值（可能是空）
(b) 栈溢出/崩溃          // 无限递归，不会正常输出
(c) base::name()         // 返回bobj的basename
(d) base::name()         // 非虚函数！返回dobj的basename（继承的成员）
(e) base::print()        // 同(a)
(f) 栈溢出/崩溃          // 同(b)，虽然静态类型是base&，但调用的是有bug的derived::print
```


---
