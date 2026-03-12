## 📘 第15章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 15.9 | ⭐⭐⭐ (3/5) | 核心概念理解正确，但缺少精确定义，例子重复且表述不够清晰 |

---

## 🎯 逐题详细评价

### Exercise 15.9: 表达式的静态类型何时可能与动态类型不同？给出三个例子。

**原题：** When is it possible for an expression's static type to differ from its dynamic type? Give three examples in which the static and dynamic type differ.

**你的答案：**
> 1. 比如基类中有virtual的重载操作符，但是派生类重写了这个virtual操作符号后， 一个变量使用的是基类引用， 一个使用的是基类对象类型然而两个之前都是绑定的派生类对象的话就会出现动态类型和静态类型表现不匹配的情况
> 
> 2. 或者是对基类引用参数传入派生类对象，并调用了内部的virtual函数
> 
> 3. 或者是对基类指针参数传入了派生类对象，并调用了内部的virtual函数

**批改结果：** ⭐⭐⭐ (3/5)

**详细分析：**
- ✅ **核心机制识别**：正确识别出通过基类指针/引用操作派生类对象时会出现静态类型与动态类型的差异
- ✅ **动态绑定理解**：知道这种情况与虚函数调用相关
- ⚠️ **缺少概念定义**：未先定义什么是静态类型（static type）和动态类型（dynamic type），这是回答的前提
- ⚠️ **例子重复**：例子2和例子3本质上是同一种情况（都是通过基类接口操作派生类对象），只是换了指针和引用，不符合题目要求"三个不同例子"
- ⚠️ **表述混乱**：第一个例子表述不清，特别是"一个变量使用的是基类引用，一个使用的是基类对象类型然而两个之前都是绑定的派生类对象"语义模糊，且静态类型与动态类型的差异和"操作符重载"无必然联系
- ⚠️ **条件缺失**：未强调**只有当变量是指针或引用时**才会出现这种差异（对象变量永远不会）

**正确答案：**

```cpp
// 关键概念：
// 静态类型 (Static type)：编译时已知的类型，变量声明时的类型
// 动态类型 (Dynamic type)：运行时确定的类型，对象在内存中的实际类型

// 出现条件：只有通过基类的指针或引用操作派生类对象时，
//          静态类型才可能与动态类型不同

class Base { 
public:
    virtual void func() {} 
};
class Derived : public Base { 
public:
    void func() override {} 
};

// 例子1：基类引用绑定派生类对象
Derived d;
Base& br = d;  // 静态类型: Base&, 动态类型: Derived

// 例子2：基类指针指向派生类对象  
Base* bp = new Derived();  // 静态类型: Base*, 动态类型: Derived*

// 例子3：函数参数传递（基类引用形参接收派生类实参）
void process(Base& obj) {   // obj的静态类型是Base&
    obj.func();             // 但动态类型可能是Derived或其他派生类
}
process(d);  // 传入Derived对象
```






---
Exercise 15.10: Recalling the discussion from §8.1 (p. 311), explain how the program on page 317 that passed an ifstream to the Sales_data read function works.

Answer:
跳过





