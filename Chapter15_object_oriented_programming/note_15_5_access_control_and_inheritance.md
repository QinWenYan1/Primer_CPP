# 📘 15.5 访问控制与继承 (Access Control and Inheritance)

> 来源说明：C++ Primer 第15章第5节 | 本节涵盖：protected成员、继承访问说明符、派生类到基类转换、友元与继承、using声明改变访问级别

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 类对派生类的访问控制*](#id1)
* [*知识点2: protected成员的基本特性*](#id2)
* [*知识点3: protected成员的关键限制*](#id3)
* [*知识点4: 继承访问说明符*](#id4)
* [*知识点5: 派生访问说明符对成员访问的影响*](#id5)
* [*知识点6: 多级继承中的访问控制*](#id6)
* [*知识点7: 派生类到基类转换的可访问性*](#id7)
* [*知识点8: 关键概念：类设计与protected成员*](#id8)
* [*知识点9: 友元与继承*](#id9)
* [*知识点10: 使用using声明豁免个别成员*](#id10)
* [*知识点11: 默认继承保护级别*](#id11)
* [*知识点12: 最佳实践：显式指定私有继承*](#id12)

---

<a id="id1"></a>
## ✅ 知识点1: 类对派生类的访问控制

**理论**
* 正如每个类控制自己的成员初始化一样，**每个类也控制其成员是否对派生类可访问**
* 基类通过访问说明符(access specifiers)决定哪些成员可以被派生类使用
* 这种控制机制是类的封装(encapsulation)机制在继承体系中的延伸

---

<a id="id2"></a>
## ✅ 知识点2: `protected`成员的基本特性

**理论**
* <b>`protected`</b>访问说明符是<b>`private`</b>和<b>`public`</b>的混合体：
  * **像`private`一样**：`protected`成员对类的普通用户**不可访问**
  * <b>像`public`一样</b>：`protected`成员对派生类的成员和友元<b>可访问</b>
* **`protected`成员的设计目的**：允许基类将某些实现细节分享给派生类使用，但阻止外部普通代码访问

**教材示例代码**
```cpp
class Base {
protected:
    int prot_mem;        // protected member
};

class Sneaky : public Base {
    friend void clobber(Sneaky&);  // can access Sneaky::prot_mem
    friend void clobber(Base&);    // can't access Base::prot_mem
    int j;                         // j is private by default
};
```

---

<a id="id3"></a>
## ✅ 知识点3: `protected`成员的关键限制

**理论**
* `protected`成员有一个**重要且容易误解**的属性：
  * **派生类成员或友元只能通过派生类对象访问基类的`protected`成员**
  * 派生类对基类对象的`protected`成员**没有特殊访问权限**
* 换句话说，
 ✅ 通过派生类对象访问继承的`protected`成员合法
 ❌ 直接访问基类对象的`protected`成员非法

**注意点**
* ⚠️ **设计意图**：`protected`检查的是<b>"访问路径"</b>——只有通过"派生类对象"这条路径才能访问，"基类对象"路径被阻断，保护封装性

**教材示例代码**
```cpp
// ok: clobber can access the private and protected members in Sneaky objects
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }

// error: clobber can't access the protected members in Base
void clobber(Base &b) { b.prot_mem = 0; }
```


---

<a id="id4"></a>
## ✅ 知识点4: 继承访问说明符

**理论**
* 对继承成员的访问由两个因素共同控制：
  1. 基类中该成员的**访问说明符**
  2. 派生类**派生列表**中的**派生访问说明符**
* 三种派生访问说明符：**`public`**（公有继承）、**`private`**（私有继承）、**`protected`**（保护继承）

**教材示例代码**
```cpp
class Base {
public:
    void pub_mem();      // public member
protected:
    int prot_mem;        // protected member
private:
    char priv_mem;       // private member
};

struct Pub_Derv : public Base {
    // ok: derived classes can access protected members
    int f() { return prot_mem; }
    // error: private members are inaccessible to derived classes
    char g() { return priv_mem; }
};

struct Priv_Derv : private Base {
    // private derivation doesn't affect access in the derived class
    int f1() const { return prot_mem; }
};
```

---

<a id="id5"></a>
## ✅ 知识点5: 派生访问说明符对成员访问的影响

**理论**
* **派生访问说明符不影响派生类对其直接基类成员的访问能力**
  * 无论使用public、private还是protected继承，Pub_Derv和Priv_Derv都可以访问prot_mem
  * 两者都**不能**访问priv_mem
* **派生访问说明符的目的是控制派生类用户（包括从派生类进一步派生的类）对继承成员的访问**
  * public继承：成员保持原有的访问级别
  * private继承：基类所有成员在派生类中变为private
  * protected继承：基类的public成员在派生类中变为protected，protected成员保持protected

**教材示例代码**
```cpp
Pub_Derv d1;     // members inherited from Base are public
Priv_Derv d2;    // members inherited from Base are private

d1.pub_mem();    // ok: pub_mem is public in the derived class
d2.pub_mem();    // error: pub_mem is private in the derived class
```

**注意点**
* ⚠️ **重要区别**：继承访问说明符改变的是**继承后的可见性**，而不是**继承时的访问能力**
* 📋 **术语**：**derivation access specifier**（派生访问说明符）与**access specifier**（成员访问说明符）是两个不同层面的概念

---

<a id="id6"></a>
## ✅ 知识点6: 多级继承中的访问控制

**理论**
* 派生类使用的派生访问说明符还控制着**从该派生类继续派生**的类的访问权限
* **public继承**：基类成员在派生类中保持原有访问级别，后续派生类可以继续访问protected成员
* **private继承**：基类成员在派生类中变为private，**后续派生类无法访问**这些继承成员

**教材示例代码**
```cpp
struct Derived_from_Public : public Pub_Derv {
    // ok: Base::prot_mem remains protected in Pub_Derv
    int use_base() { return prot_mem; }
};

struct Derived_from_Private : public Priv_Derv {
    // error: Base::prot_mem is private in Priv_Derv
    int use_base() { return prot_mem; }
};
```

**注意点**
* ⚠️ **连锁效应**：Priv_Derv的派生类（Derived_from_Private）无法访问prot_mem，因为Priv_Derv使用private继承使所有Base成员变为了private
* 💡 **设计考虑**：如果你希望阻止后续派生类访问基类的protected成员，使用private继承

---

<a id="id7"></a>
## ✅ 知识点7: 派生类到基类转换的可访问性

**理论**
* **派生类到基类转换(derived-to-base conversion)**是否可访问取决于：
  1. 哪段代码尝试使用该转换
  2. 派生类使用的派生访问说明符
* **转换规则**：
  * **用户代码(user code)**：只有当D**public继承**自B时，才能使用D到B的转换；protected或private继承时不能使用
  * **派生类D的成员和友元**：无论D如何继承自B，都可以使用转换；转换对直接基类总是可访问的
  * **派生类D的派生类的成员和友元**：只有当D**public或protected继承**自B时才能使用；private继承时不能使用

**注意点**
* 📋 **关键记忆点**：对于代码中任何给定的点，如果基类的public成员可访问，则派生类到基类的转换也可访问；否则不可访问
* 🔄 **与成员访问的关联**：转换的可访问性与继承后基类public成员的可访问性一致

---

<a id="id8"></a>
## ✅ 知识点8: 关键概念：类设计与protected成员

**理论**
* **三种用户视角**：
  1. **普通用户(ordinary users)**：编写使用类对象的代码，只能访问public成员（接口）
  2. **实现者(implementors)**：类的成员和友元，可以访问public和private成员（实现细节）
  3. **派生类(derived classes)**：继承体系中的第三类用户
* **protected的设计哲学**：
  * 基类将愿意让派生类使用的实现部分声明为protected
  * protected成员对普通用户代码不可访问，但对派生类及其友元可访问
  * private成员对派生类保持不可访问
* **设计准则**：
  * 实现成员应设为**protected**（如果派生类需要在其自身实现中使用该操作或数据）
  * 否则，实现成员应设为**private**

---

<a id="id9"></a>
## ✅ 知识点9: 友元与继承

**理论**
* **友元关系不具有传递性(not transitive)**，也**不能被继承(not inherited)**
* **规则**：
  * 基类的友元**没有特殊权限**访问派生类成员
  * 派生类的友元**没有特殊权限**访问基类成员
* **例外情况**：基类友元可以访问**嵌入在派生类对象中的基类子对象**(base-class objects that are embedded in an object of a type derived from Base)
* **friendship声明范围**：当一个类声明另一个类为友元时，**仅该类本身**获得访问权限；基类和派生类都不自动获得对 befriending class 的特殊访问权

**教材示例代码**
```cpp
// Pal has no access to classes derived from Base
class Pal {
public:
    int f(Base b) { return b.prot_mem; }     // ok: Pal is a friend of Base
    int f2(Sneaky s) { return s.j; }         // error: Pal not friend of Sneaky
    // access to a base class is controlled by the base class, even inside a derived object
    int f3(Sneaky s) { return s.prot_mem; }  // ok: Pal is a friend of Base
};

// D2 has no access to protected or private members in Base
class D2 : public Pal {
public:
    int mem(Base b) { return b.prot_mem; }   // error: friendship doesn't inherit
};
```

**注意点**
* ⚠️ **常见陷阱**：f3合法但f2非法——因为Pal是Base的友元（可以访问prot_mem），但不是Sneaky的友元（不能访问j）
* 📋 **重要结论**：友元关系不继承；每个类控制自己的成员访问权限

---

<a id="id10"></a>
## ✅ 知识点10: 使用using声明豁免个别成员

**理论**
* **using声明(using declaration)**可以改变派生类继承而来的名字的访问级别
* **机制**：使用using声明可以将基类成员"提升"或"调整"到派生类中的指定访问区域
* **访问级别决定**：using声明所在的位置前的访问说明符决定了该名字的访问级别
  * private部分：仅对成员和友元可访问
  * public部分：对所有用户可访问
  * protected部分：对成员、友元和派生类可访问
* **限制**：派生类只能对**允许访问**（即非private）的名字提供using声明

**教材示例代码**
```cpp
class Base {
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};

class Derived : private Base {     // note: private inheritance
public:
    // maintain access levels for members related to the size of the object
    using Base::size;
protected:
    using Base::n;
};
```

**注意点**
* 💡 **使用场景**：当使用private继承（默认）但希望某些继承成员保持public或protected访问级别时特别有用
* 🔄 **效果**：Users of Derived可以访问size成员，从Derived继续派生的类可以访问n成员
* ⚠️ **using与继承**：using声明可以命名任何可访问的直接或间接基类成员

---

<a id="id11"></a>
## ✅ 知识点11: 默认继承保护级别

**理论**
* **默认派生访问说明符**取决于定义派生类使用的关键字：
  * 使用**class**关键字：默认是**private inheritance**（私有继承）
  * 使用**struct**关键字：默认是**public inheritance**（公有继承）
* **常见误解澄清**：struct和class定义类**没有本质区别**，仅有的两个区别是：
  1. 默认成员访问说明符（struct默认public，class默认private）
  2. 默认派生访问说明符（struct默认public，class默认private）

**教材示例代码**
```cpp
class Base { /* ... */ };

struct D1 : Base { /* ... */ };  // public inheritance by default
class D2 : Base { /* ... */ };   // private inheritance by default
```

**注意点**
* 📋 **一致性**：默认行为与成员访问一致——struct偏向"开放"(public)，class偏向"封闭"(private)
* ⚠️ **潜在陷阱**：混用struct和class时容易混淆默认继承方式，建议始终显式指定

---

<a id="id12"></a>
## ✅ 知识点12: 最佳实践：显式指定私有继承

**理论**
* **最佳实践(Best Practices)**：使用私有继承的类应**显式指定private**，而非依赖默认行为
* **理由**：显式声明使代码意图清晰，表明private继承是**有意为之(intended)**，而非**疏忽 oversight**

**注意点**
* 💡 **代码可读性**：显式访问说明符让其他程序员无需记住默认规则就能理解代码
* 🔄 **维护性**：即使后续将struct改为class（或反之），显式指定的继承方式也不会意外改变

---

## 🔑 核心要点总结

1. **protected成员的本质**：是private和public的混合体，关键限制是只能通过派生类对象访问，不能直接访问基类对象的protected成员
2. **继承访问说明符的双重作用**：不影响派生类对直接基类成员的访问能力，但控制这些成员对派生类用户及后续派生类的可见性
3. **转换可访问性规则**：只有public继承时，用户代码才能使用派生类到基类的转换；protected/private继承会阻断用户层面的类型转换
4. **友元不继承**：基类友元不能访问派生类成员，派生类友元也不能访问基类成员（除非通过派生类对象中的基类子对象）
5. **using声明调整访问**：可以在private继承中 selectively 提升特定基类成员的访问级别，且using声明的位置决定最终的访问权限

## 📌 考试速记版

**关键访问规则表**

| 场景 | public继承 | protected继承 | private继承 |
|------|-----------|--------------|-------------|
| 派生类对基类成员访问 | 正常访问 | 正常访问 | 正常访问 |
| 用户代码对继承成员 | 保持原级别 | public变protected | 全变private |
| 后续派生类访问 | 正常 | protected成员可访问 | 无法访问 |
| 用户代码使用D→B转换 | ✅允许 | ❌禁止 | ❌禁止 |

**易混淆概念对比**
* **protected vs private**：protected允许派生类访问，private不允许
* **成员访问 vs 继承访问**：成员访问说明符控制"能不能访问"，继承访问说明符控制"访问后对外可见性"
* **友元范围**：友元只声明它的类有效，不波及派生类也不回溯基类

**常见错误和陷阱**
1. ❌ 以为protected成员可以直接通过基类对象访问（必须通过派生类对象）
2. ❌ 混淆继承访问说明符对"类内部访问"和"类外部可见性"的不同影响
3. ❌ 忘记struct和class的默认继承方式相反（struct默认public，class默认private）
4. ❌ 以为友元关系可以继承（基类友元≠派生类友元）

**记忆口诀**
* **"保护成员有路径，派生对象才互通"**（protected只能通过派生类对象访问）
* **"继承控制看外面，内部访问不影响"**（继承访问说明符不影响类内部对基类成员的访问）
* **"公有转换才允许，保护私有都挡住"**（只有public继承时用户才能使用派生到基类转换）
* **"友元不遗传，各管各的门"**（友元关系不继承）