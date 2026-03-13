# 📘 15.4 抽象基类 (Abstract Base Classes)

> 来源说明：《C++ Primer》第15章 | 本节涵盖：通过纯虚函数和抽象基类实现接口继承，防止实例化不完整的折扣策略类，以及类层次结构的重构技术

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 书店折扣策略扩展场景*](#id1)
* [*知识点2: Disc_quote类的设计困境*](#id2)
* [*知识点3: 继承net_price带来的问题*](#id3)
* [*知识点4: 纯虚函数(Pure Virtual Functions)*](#id4)
* [*知识点5: Disc_quote类代码实现*](#id5)
* [*知识点6: 构造函数的成员初始化*](#id6)
* [*知识点7: 纯虚函数的外部定义*](#id7)
* [*知识点8: 含纯虚函数的类是抽象基类*](#id8)
* [*知识点9: 抽象基类的对象创建限制*](#id9)
* [*知识点10: 派生类构造函数只初始化直接基类*](#id10)
* [*知识点11: Bulk_quote类的重构实现*](#id11)
* [*知识点12: 子对象结构与构造函数调用链*](#id12)
* [*知识点13: 重构(Refactoring)的概念*](#id13)

---

<a id="id1"></a>
## ✅ 知识点1: 书店折扣策略扩展场景

**理论**
* **核心主旨总结**：
    * 为了扩展现有的书店类以支持多种折扣策略，除了**批量折扣**外，还可能需要支持其他策略：如购买数量达到一定值之前享受折扣、超过限额才享受折扣等。
    * 虽然这些策略不同，但它们都需要记录**数量**和**折扣金额**。
* **继承体系设计**：
    * 可以通过定义一个名为 `Disc_quote` 的新类来存储数量和折扣金额。
    * 像 `Bulk_item` 这样表示特定折扣策略的类将继承自 `Disc_quote`。
    * 每个派生类通过定义自己的 `net_price` 版本来实现其折扣策略。


**注意点**
* 💡 **设计意图**：`Disc_quote` 作为通用折扣概念的基类，为具体策略提供统一的数据成员接口
* 🔄 **知识关联**：这延续了面向对象设计中的继承体系构建思想，将共同数据抽象到中间层

---

<a id="id2"></a>
## ✅ 知识点2: `Disc_quote`类的设计困境

**理论**
* **核心主旨总结**：
    * 在定义 `Disc_quote` 类之前，必须决定如何处理 `net_price` 函数。
    * `Disc_quote` 类本身不对应任何特定的折扣策略，因此为这个类指定 `net_price` 的含义是没有意义的。
* **关键决策点**：该类代表的是折扣图书的通用概念，而非具体的折扣策略。


**注意点**
* ⚠️ **语义缺失**：基类本身无法确定具体的价格计算逻辑，因为不同的折扣策略有不同的计算方式


---

<a id="id3"></a>
## ✅ 知识点3: 继承`net_price`带来的问题

**理论**
* **核心主旨总结**：
    * 虽然可以定义一个不包含自己版本 `net_price` 的 `Disc_quote` 类（这样 `Disc_quote` 会继承 `Quote` 的 `net_price`），但这种设计会让用户能够编写无意义的代码。
* **具体问题**：
    * 用户可以创建一个 `Disc_quote` 类型的对象，提供数量和折扣率，然后将该对象传递给 `print_total` 等函数。
    * 这时会使用 `Quote` 版本的 `net_price`，计算出的价格不会包含创建对象时提供的折扣，这种状态是没有意义的。


**注意点**
* ⚠️ **严重缺陷**：允许实例化 `Disc_quote` 会导致折扣参数被忽略，产生逻辑错误
* 💡 **设计原则**：应该防止用户创建这种"不完整"的对象，强制使用具体的策略类

---

<a id="id4"></a>
## ✅ 知识点4: 纯虚函数

**理论**
* **核心主旨总结**：
    * 深入思考这个问题会发现，我们不仅不知道如何定义 `net_price`，更重要的是要阻止用户创建 `Disc_quote` 对象。
    * 这个类代表的是折扣图书的抽象概念，而非具体的折扣策略。
* **纯虚函数定义**：
    * 可以通过将 `net_price` 定义为<b>纯虚函数(pure virtual)</b>来强制执行这一设计意图。
    * 与普通的虚函数不同，纯虚函数不应该在基类中定义。
* **语法规范**：通过在函数声明的分号之前写入 `= 0` 来指定虚函数为纯虚函数（即代替函数体）。**` = 0` 只能出现在类体内的虚函数声明中**。

**注意点**
* ⚠️ **语法限制**：`= 0` 只能出现在类体内的虚函数声明末尾，不能用于类外定义
* 🔧 **核心作用**：强制派生类必须覆盖(override)该函数，否则派生类也会成为抽象类

**教材示例代码**
```cpp
// class to hold the discount rate and quantity
// derived classes will implement pricing strategies using these data
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
        Quote(book, price),
        quantity(qty), discount(disc) { }
    double net_price(std::size_t) const = 0;
protected:
    std::size_t quantity = 0;  // purchase size for the discount to apply
    double discount = 0.0;     // fractional discount to apply
};
```


---

<a id="id5"></a>
## ✅ 知识点5: `Disc_quote`类代码实现

**理论**
* **核心主旨总结**：
    * 与之前的 `Bulk_item` 类类似，`Disc_quote` 定义了默认构造函数和一个接受四个参数的构造函数。
    * 虽然我们不能直接定义 `Disc_quote` 类型的对象，但从 `Disc_quote` 派生的类的构造函数会使用 `Disc_quote` 的构造函数来构造其对象的 `Disc_quote` 部分。
* **构造函数行为**：
    1. 接受四个参数的构造函数将前两个参数传递给 `Quote` 构造函数，直接初始化自己的成员 `discount` 和 `quantity`。
    2. 默认构造函数默认初始化这些成员。

**注意点**
* 🔄 **构造链**：派生类构造函数通过基类构造函数间接构造间接基类 `Quote`

**教材示例代码**
```cpp
// class to hold the discount rate and quantity
// derived classes will implement pricing strategies using these data
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
        Quote(book, price),
        quantity(qty), discount(disc) { }
    double net_price(std::size_t) const = 0;
protected:
    std::size_t quantity = 0;  // purchase size for the discount to apply
    double discount = 0.0;     // fractional discount to apply
};
```




---

<a id="id6"></a>
## ✅ 知识点6: 构造函数的成员初始化

**理论**
* **核心主旨总结**：
    * `Disc_quote` 的构造函数将前两个参数（书名和价格）传递给 `Quote` 的构造函数，直接使用初始化列表初始化自己的数据成员 `quantity` 和 `discount`。
    * 默认构造函数则对这些成员进行默认初始化（使用类内初始值 `= 0` 和 `= 0.0`）。



**注意点**
* 🔧 **初始化顺序**：先执行基类构造函数 `Quote(book, price)`，然后按声明顺序初始化本类成员 `quantity` 和 `discount`
* 💡 **默认初始化**：`quantity = 0` 和 `discount = 0.0` 是类内默认成员初始化器，在默认构造函数中使用

---

<a id="id7"></a>
## ✅ 知识点7: 纯虚函数的外部定义

**理论**
* **核心主旨总结**：
    * 值得注意的是，**我们可以为纯虚函数提供定义**，但是**函数体必须在类外定义**。
    * 也就是说，我们不能在类体内为标记为 `= 0` 的函数提供函数体。



**注意点**
* ⚠️ **重要区别**：`= 0` 只影响函数的"抽象性"（是否需要派生类覆盖），不禁止基类提供默认实现
* 📋 **使用场景**：基类可以提供纯虚函数的默认实现，但派生类仍必须显式覆盖，且可以在覆盖函数中调用基类的默认实现


---

<a id="id8"></a>
## ✅ 知识点8: 含纯虚函数的类是抽象基类

**理论**
* **核心主旨总结**：
    * 包含（或继承但未覆盖）纯虚函数的类称为**抽象基类(abstract base class)**。
    * 抽象基类定义了一个接口，供后续派生类覆盖。
    * 我们**不能直接创建抽象基类类型的对象**。


**教材示例代码**
```cpp
// Disc_quote declares pure virtual functions, which Bulk_quote will override
Disc_quote discounted;  // error: can't define a Disc_quote object
Bulk_quote bulk;        // ok: Bulk_quote has no pure virtual functions
```



---

<a id="id9"></a>
## ✅ 知识点9: 抽象基类的对象创建限制

**理论**
* **核心主旨总结**：**我们不能创建抽象基类类型的对象**。
* 这是抽象基类的根本特征，强制派生类必须实现所有纯虚函数才能被实例化。

**注意点**
* ⚠️ **编译时检查**：编译器会在编译时阻止抽象基类的实例化
* 💡 **设计价值**：这一限制确保了所有被使用的对象都具有完整的实现，避免"半实现"对象被误用

* ⚠️ **编译错误**：尝试实例化抽象基类会导致编译错误（如 `Disc_quote discounted;`）
* ✅ **合法实例化**：只有当派生类覆盖了所有纯虚函数后，才能实例化该派生类（如 `Bulk_quote`）

**教材示例代码**
```cpp
Disc_quote discounted;  // error: can't define a Disc_quote object
```


---

<a id="id10"></a>
## ✅ 知识点10: 派生类构造函数只初始化直接基类

**理论**
* **核心主旨总结**：
    * 现在可以重新实现 `Bulk_quote` 类，让它继承自 `Disc_quote` 而不是直接继承 `Quote`。
    * `Bulk_quote` 的类定义与之前的版本类似，只需要修改其构造函数。


**注意点**
* 🔧 **构造函数变化**：新构造函数接受四个参数，但只将它们传递给 `Disc_quote` 的构造函数，不再直接调用 `Quote` 的构造函数
* 📋 **初始化责任**：**派生类构造函数只负责初始化其直接基类**。`Bulk_quote` 的直接基类是 `Disc_quote`，`Disc_quote` 再负责初始化 `Quote`
* 🔄 **构造链**：`Bulk_quote` → `Disc_quote` → `Quote` 的构造函数链

**教材示例代码**
```cpp
// the discount kicks in when a specified number of copies of the same book are sold
// the discount is expressed as a fraction to use to reduce the normal price
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price,
               std::size_t qty, double disc):
        Disc_quote(book, price, qty, disc) { }
    // overrides the base version to implement the bulk purchase discount policy
    double net_price(std::size_t) const override;
};
```


---

<a id="id11"></a>
## ✅ 知识点11: `Bulk_quote`类的重构实现

**理论**
* **核心主旨总结**：
    * 这个版本的 `Bulk_quote` 有一个直接基类 `Disc_quote` 和一个间接基类 `Quote`。
    * 每个 `Bulk_quote` 对象包含三个子对象：一个（空的）`Bulk_quote` 部分、一个 `Disc_quote` 子对象（包含 `quantity` 和 `discount`），以及一个 `Quote` 子对象（包含 `bookNo` 和 `price`）。
* **`net_price`覆盖**：`Bulk_quote` 必须覆盖 `net_price` 以提供具体的批量折扣策略实现。

**注意点**
* 📋 **对象内存布局**：`Bulk_quote` 对象内存中包含 `Quote` 基类子对象、`Disc_quote` 基类子对象（含保护成员）、以及 `Bulk_quote` 自己的成员（本例中无额外成员）
* ⚠️ **覆盖要求**：必须提供 `net_price` 的具体实现，否则 `Bulk_quote` 也会成为抽象基类

**教材示例代码**
```cpp
// overrides the base version to implement the bulk purchase discount policy
double net_price(std::size_t) const override;
```



---

<a id="id12"></a>
## ✅ 知识点12: 子对象结构与构造函数调用链

**理论**
* **核心主旨总结**：
    * 正如我们所见，每个类控制其类型对象的初始化。
    * 因此，即使 `Bulk_quote` 没有自己的数据成员，它也提供了与原始类相同的四参数构造函数。
    * 新构造函数将其参数传递给 `Disc_quote` 构造函数。
* **构造函数执行流程**：
  1. 该构造函数运行 `Disc_quote` 构造函数
  2. `Disc_quote` 构造函数又运行 `Quote` 构造函数
  3. `Quote` 构造函数初始化 `bookNo` 和 `price` 成员
  4. `Quote` 构造函数完成后，`Disc_quote` 构造函数运行并初始化 `quantity` 和 `discount` 成员
  5. 此时，`Bulk_quote` 构造函数继续执行。该构造函数没有其他初始化工作或任务要做



**注意点**
* 🔧 **构造顺序**：基类构造严格按照继承层次从上到下
* 💡 **构造函数体**：`Bulk_quote` 的构造函数体为空，因为所有初始化工作都通过初始化列表和基类构造函数完成
* 📋 **成员初始化时机**：基类子对象的构造在派生类构造函数体执行之前完成

---

<a id="id13"></a>
## ✅ 知识点13: 重构(Refactoring)的概念

**理论**
* **核心主旨总结**：
    * 将 `Disc_quote` 添加到 `Quote` 层次结构中是<b>重构(refactoring)</b>的一个例子。
    * 重构涉及重新设计类层次结构，将操作和/或数据从一个类移动到另一个类。
    * 重构在面向对象应用程序中很常见，随着需求变化不断优化类结构
* **代码兼容性**：
    * 值得注意的是，即使我们改变了继承层次结构，使用 `Bulk_quote` 或 `Quote` 的代码也不需要更改。
    * 但是，当类被重构（或以其他方式更改）时，我们必须重新编译使用这些类的代码。


**注意点**
* 📋 **重构介绍**：Refactoring（重构）= 重新设计类层次结构，移动操作和数据以优化设计，同时保持外部接口不变
* 💡 **面向对象优势**：良好的继承设计允许内部结构调整（重构）而不影响客户端代码
* ⚠️ **编译依赖**：虽然源代码兼容，但修改类定义后必须重新编译所有依赖代码


---

## 🔑 核心要点总结

1. **纯虚函数与抽象基类**：通过在虚函数声明后添加 `= 0` 定义纯虚函数，包含纯虚函数的类成为抽象基类，不能实例化对象，强制派生类必须覆盖该函数

2. **构造函数职责**：派生类构造函数只直接初始化其直接基类，通过基类构造函数链间接初始化间接基类，构造顺序从最远基类开始逐级向下

3. **接口继承与实现分离**：抽象基类（如 `Disc_quote`）定义通用接口和共享数据，但不提供具体策略实现，由具体派生类（如 `Bulk_quote`）实现虚函数

4. **重构与设计演进**：通过引入中间抽象层（`Disc_quote`）重构继承体系，可以优化代码结构而不影响现有客户端代码，但需重新编译

5. **纯虚函数的特例**：纯虚函数可以拥有类外定义（默认实现），但这不会使类变为非抽象，派生类仍必须覆盖该函数

## 📌 考试速记版

* **纯虚函数语法**：`virtual 返回类型 函数名(参数) const = 0;`
* **抽象基类特征**：含纯虚函数 → 不能实例化 → 派生类必须覆盖所有纯虚函数才能实例化
* **构造函数链**：`Bulk_quote` → 初始化 `Disc_quote` → 初始化 `Quote`（先远后近）
* **关键区别**：普通虚函数"可以"覆盖，纯虚函数"必须"覆盖
* **重构定义**：重新设计类层次结构，移动数据/操作，保持接口不变

**记忆口诀**：
> 纯虚函数零标记，抽象基类禁实例；  
> 派生必须全覆盖，构造链式逐级来；  
> 重构结构优设计，接口不动源码在。