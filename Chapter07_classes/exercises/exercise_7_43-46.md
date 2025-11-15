# 📘 C++构造函数练习题详解

## Exercise 7.43
**原题：** Assume we have a class named NoDefault that has a constructor that takes an int, but has no default constructor. Define a class C that has a member of type NoDefault. Define the default constructor for C.

**你的答案：**
```cpp
class C{
private:
    NoDefault v; 
public:
    C():v(0){}
}
```

**批改：** ⭐⭐⭐⭐⭐ 完全正确！
- ✅ 正确理解了`NoDefault`没有默认构造函数的问题
- ✅ 在初始化列表中正确初始化了成员`v`
- ✅ 语法正确

**改进建议：** 补充缺少的分号
```cpp
class C {
private:
    NoDefault v; 
public:
    C() : v(0) {}  // 正确！
};
```

---

## Exercise 7.44
**原题：** Is the following declaration legal? If not, why not?
```cpp
vector<NoDefault> vec(10);
```

**你的答案：** 会有问题，因为vector会对对象进行值初始化，然而值初始化需要调用类类型的默认构造器，但是NoDefault没有，会报错

**批改：** ⭐⭐⭐⭐⭐ 完全正确！
- ✅ 准确理解了vector的初始化机制
- ✅ 知道值初始化需要默认构造函数
- ✅ 正确识别了问题根源

**详细解释：**
```cpp
vector<NoDefault> vec(10);  // 错误！
```
这个声明尝试创建包含10个`NoDefault`对象的vector，每个元素都需要被**值初始化**。但是：
- `NoDefault`没有默认构造函数
- 编译器无法创建`NoDefault`的默认实例
- 导致编译错误

---

## Exercise 7.45
**原题：** What if we defined the vector in the previous exercise to hold objects of type C?

**你的答案：** 不行，在vector中每个元素都为C的话，因为C类的成员并不知道如何去默认初始化，会报错

**批改：** ⭐⭐ 理解错误

**正确答案：** 这个声明是**合法的**！

**分析：**
```cpp
vector<C> vec(10);  // 合法！
```
原因：
- 在Exercise 7.43中，你**已经为类C定义了默认构造函数** `C():v(0){}`
- 这个默认构造函数正确地初始化了`NoDefault`成员`v`
- 因此，`C`类有可用的默认构造函数
- vector可以成功创建10个`C`对象

**关键点：** 你忘记了在7.43中已经解决了这个问题！

---

## Exercise 7.46
**原题：** Which, if any, of the following statements are untrue? Why?
(a) A class must provide at least one constructor.
(b) A default constructor is a constructor with an empty parameter list.
(c) If there are no meaningful default values for a class, the class should not provide a default constructor.
(d) If a class does not define a default constructor, the compiler generates one that initializes each data member to the default value of its associated type.

**你的答案：**
(a). true，不管提供的是不是默认初始化器，都需要知道如何去初始化这个类才行  
(b). untrue, 还需要告诉这个类是default才行  
(c). true  
(d). untrue, 如果你提供了其他constructor而没有提供default constructor的话，compiler不会自动生成一个默认给你

**批改：** ⚠️ 部分正确

**正确答案分析：**

**(a) "A class must provide at least one constructor."**
你的回答：true ❌  
**正确答案：** false  
- 如果类没有定义任何构造函数，编译器会**自动合成**一个默认构造函数
- 类可以不提供任何构造函数

**(b) "A default constructor is a constructor with an empty parameter list."**
你的回答：untrue ⭐⭐⭐⭐  
**正确答案：** false  
- 带默认参数的构造函数也是默认构造函数，如：`Sales_data(string s = "")`
- 你的理解方向正确，但表述可以更准确

**(c) "If there are no meaningful default values for a class, the class should not provide a default constructor."**
你的回答：true ❌  
**正确答案：** false  
- 实践中，即使没有有意义的默认值，也应该提供默认构造函数
- 很多场景（如容器）需要默认构造函数

**(d) "If a class does not define a default constructor, the compiler generates one that initializes each data member to the default value of its associated type."**
你的回答：untrue ⭐⭐⭐⭐⭐  
**正确答案：** false  
- 只有在类**没有定义任何构造函数**时，编译器才会合成默认构造函数
- 如果定义了其他构造函数但没有默认构造函数，编译器不会自动生成

---

## 🎯 Exercise 7.46 完整正确答案

(a) **False** - 类可以不提供任何构造函数，编译器会自动合成默认构造函数

(b) **False** - 带所有参数都有默认值的构造函数也是默认构造函数

(c) **False** - 即使没有有意义的默认值，也应该提供默认构造函数，因为很多库和容器需要它

(d) **False** - 只有在类没有定义任何构造函数时，编译器才会合成默认构造函数

---

## 📊 总体评价

| 题目 | 得分 | 评价 |
|------|------|------|
| 7.43 | 5/5 | 完美！ |
| 7.44 | 5/5 | 完美！ |
| 7.45 | 2/5 | 忽略了上下文关联 |
| 7.46 | 3/5 | 对编译器行为理解需要加强 |

