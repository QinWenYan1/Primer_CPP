## 📊 练习批改与分析

### Exercise 15.23 虚函数覆盖与调用解析

**原题：** Assuming class D1 on page 620 had intended to override its inherited fcn function, how would you fix that class? Assuming you fixed the class so that fcn matched the definition in Base, how would the calls in that section be resolved?

**你的答案：**
> 如果D1也像override这个基类的fcn()虚函数的话， 需要自己的fcn()函数有着相同的返回类型和参数， 同时最好要有override来让编译器帮助检查， 对于调用决议来说如果使用的基类指针还是派生类指针，最后都会去调用被override的fcn()函数在派生类中， 在基类指针中无非就是先去基类中找到这个虚函数fcn()然后再深入到派生类调用这个fcn()

**批改：** ⭐⭐⭐⭐ (4/5)

---

### 详细分析

#### ✅ 做得好的方面
1. **概念理解正确**：准确指出了override需要相同的返回类型和参数列表，这是虚函数覆盖的核心要求
2. **现代C++意识**：提到使用`override`关键字让编译器帮助检查，体现了对C++11新特性的了解
3. **动态绑定理解**：基本理解了通过基类指针调用虚函数时的动态绑定机制

#### ⚠️ 需要改进的方面
1. **缺少具体修复代码**：仅描述修改思路，未展示修复后的D1类代码
2. **"隐藏" vs "覆盖"概念**：没有明确指出原代码中D1的行为是"隐藏"(hide)而非"覆盖"(override)
3. **调用决议表述不够精确**："无非就是先去基类中找到..."这种描述不够专业，应使用虚函数表(vtable)机制解释
4. **缺少具体调用示例分析**：没有分析当D1修复后，书中那段代码的具体调用结果

---

### 正确答案

**修复后的D1类：**
```cpp
class D1 : public Base {
public:
    int fcn() override;  // 正确覆盖Base::fcn()
    int fcn(int);          // 仍然是隐藏，不是覆盖
    virtual void f2();     // 新的虚函数
};
```

**关键区别说明：**
- 原代码中`int fcn(int)`是**隐藏**(hide)了Base::fcn，而非覆盖
- 修复后`int fcn()`通过`override`明确声明覆盖意图，编译器会验证签名匹配

**调用解析（假设书中调用代码如下）：**
```cpp
Base bobj;  D1 d1obj;  D2 d2obj;
Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
bp1->fcn();  // 调用Base::fcn()
bp2->fcn();  // 调用D1::fcn()（动态绑定）
bp3->fcn();  // 调用D2::fcn()（动态绑定）

D1 *d1p = &d1obj;
D2 *d2p = &d2obj;
d1p->f2();   // 调用D1::f2()
d2p->f2();   // 调用D2::f2()（覆盖）

bp2->f2();   // 错误！Base没有f2成员
d1p->fcn(42); // 调用D1::fcn(int)
d2p->fcn(42); // 调用D2::fcn(int)，隐藏了D1::fcn(int)
```

---
