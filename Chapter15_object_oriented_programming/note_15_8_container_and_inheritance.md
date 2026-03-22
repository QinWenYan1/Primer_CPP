# 📘 15.8 容器与继承 (Containers and Inheritance)

> 来源说明：C++ Primer 第15.8节 | 本节涵盖：在容器中存储继承层次对象的正确方法、对象切片问题、智能指针的使用、Basket类设计模式

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 容器存储继承对象的基本限制*](#id1)
    * [*知识点2: 对象切片问题与代码示例*](#id2)
* [*知识点3: 在容器中使用智能指针而非对象*](#id3)
* [*知识点4: 智能指针的派生类到基类转换*](#id4)
    * [*知识点5: 编写Basket类-类定义与multiset使用*](#id5)
* [*知识点6: Basket类中的比较函数设计*](#id6)
    * [*知识点7: 定义Basket的成员-add_item与total_receipt*](#id7)
    * [*知识点8: total_receipt函数实现与批量处理*](#id8)
    * [*知识点9: upper_bound与循环增量控制*](#id9)
    * [*知识点10: print_total函数与虚调用*](#id10)
* [*知识点11: 隐藏指针-简化用户接口*](#id11)
* [*知识点12: 模拟虚拷贝-virtual clone机制*](#id12)
    * [*知识点13: 基于clone的add_item实现*](#id13)

---

<a id="id1"></a>
## ✅ 知识点1: 容器存储继承对象的基本限制

**理论**
* **核心主旨总结**：当我们使用容器(container)存储来自继承层次(inheritance hierarchy)的对象时，**通常必须间接存储这些对象**。我们无法将与继承相关的不同类型的对象直接放入容器，因为没有办法定义一个能保存不同类型元素的容器。
* **具体限制分析**：
  * 不能定义一个存储 `Bulk_quote` 对象的vector来同时保存客户想要购买的多本书籍，因为我们无法将 `Quote` 对象转换为 `Bulk_quote` 对象（向上转型不允许）
  * 同样，我们也不能使用存储 `Quote` 类型对象的vector。虽然在这种情况下我们可以将 `Bulk_quote` 对象放入容器，但这些对象**将不再保持为 `Bulk_quote` 对象**——派生部分会被切掉(sliced down)

**注意点**
* ⚠️ **关键限制**：容器和继承关系混合使用时，直接存储对象会导致派生类对象被"切片"(sliced down)，丢失派生类特有的数据和行为
* 📋 **术语提醒**：**继承层次(inheritance hierarchy)**、**间接存储(store indirectly)**、**对象切片(object slicing)**

---

<a id="id2"></a>
## ✅ 知识点2: 对象切片问题与代码示例

**教材示例代码**
```cpp
vector<Quote> basket;
basket.push_back(Quote("0-201-82470-1", 50));
// ok, but copies only the Quote part of the object into basket
basket.push_back(Bulk_quote("0-201-54848-8", 50, 10, .25));
// calls version defined by Quote, prints 750, i.e., 15 * $50
cout << basket.back().net_price(15) << endl;
```

**理论**
* **代码行为分析**：`basket` 中的元素都是 `Quote` 对象。当我们向vector添加 `Bulk_quote` 对象时，其**派生部分被忽略**(derived part is ignored)，只复制了基类 `Quote` 部分
* **结果验证**：调用 `net_price(15)` 时，打印的是750（即15 * $50），而不是经过折扣计算后的价格，因为对象已经被切片为基类类型

**⚠️ Warning（警告框）**
> Because derived objects are "sliced down" when assigned to a base-type object, **containers and types related by inheritance do not mix well**.
> 
> （因为派生对象在赋值给基类类型对象时会被"切片"，**容器和与继承相关的类型不能很好地混合**）

**注意点**
* ⚠️ **严重警告**：对象切片是C++中一个隐蔽但危险的错误，会导致多态行为失效，程序产生错误结果而不会报错
* 💡 **理解技巧**：想象把派生类对象"塞进"基类大小的盒子里，多余的部分（派生类特有的成员）被硬生生切掉了

---

<a id="id3"></a>
## ✅ 知识点3: 在容器中使用智能指针而非对象

**理论**
* **核心主旨总结**：当我们需要一个容器来保存与继承相关的对象时，通常将容器定义为保存**指针(pointers)**（最好是**智能指针(smart pointers)**，如 `§12.1, p. 450` 所述）指向基类。这些指针所指向的对象的动态类型(dynamic type)可以是基类类型，也可以是从该基类派生的类型。
* **解决方案优势**：通过存储指向基类的指针（特别是 `shared_ptr`），容器可以间接保存不同类型的对象，同时保持多态性

**教材示例代码**
```cpp
vector<shared_ptr<Quote>> basket;
basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
basket.push_back(
    make_shared<Bulk_quote>("0-201-54848-8", 50, 10, .25));
// calls the version defined by Quote; prints 562.5, i.e., 15 * $50 less the discount
cout << basket.back()->net_price(15) << endl;
```

**注意点**
* 💡 **关键区别**：使用 `basket.back()` 返回的是 `shared_ptr`，我们必须使用 `->` 运算符来调用 `net_price`，以便在指针指向的对象上运行该函数
* 🔄 **知识关联**：`net_price` 的调用版本取决于指针所指向对象的动态类型(dynamic type)，实现了运行时多态
* 📋 **术语提醒**：**智能指针(smart pointers)**、**动态类型(dynamic type)**、**间接存储(indirect storage)**

---

<a id="id4"></a>
## ✅ 知识点4: 智能指针的派生类到基类转换

**理论**
* **核心主旨总结**：尽管我们将 `basket` 定义为 `shared_ptr<Quote>`，但在第二个 `push_back` 中我们传递了指向 `Bulk_quote` 对象的 `shared_ptr`。就像我们可以将派生类型的普通指针转换为基类类型的指针一样（`§15.2.2, p. 597`），我们也可以将派生类型的智能指针转换为基类类型的智能指针。
* **转换机制**：`make_shared<Bulk_quote>` 返回 `shared_ptr<Bulk_quote>` 对象，在调用 `push_back` 时转换为 `shared_ptr<Quote>`。因此，尽管表面上看起来不同，`basket` 的所有元素都具有相同的类型。

**注意点**
* 📋 **技术细节**：`shared_ptr` 支持**派生类到基类的转换(derived-to-base conversion)**，这是容器能够存储多种相关类型的关键
* 💡 **理解技巧**：`shared_ptr` 的类型转换与普通指针类似，但自动管理内存，避免内存泄漏

---

<a id="id5"></a>
## ✅ 知识点5: 编写Basket类-类定义与multiset使用

**理论**
* **核心主旨总结**：C++中面向对象编程(object-oriented programming)的一个悖论是我们不能直接使用对象来支持它。相反，我们必须使用指针和引用。由于指针给我们的程序增加了复杂性，我们经常定义辅助类(auxiliary classes)来帮助管理这种复杂性。本节通过定义一个表示购物篮的 `Basket` 类来展示这种设计模式。

**教材示例代码**
```cpp
class Basket {
public:
    // Basket uses synthesized default constructor and copy-control members
    void add_item(const std::shared_ptr<Quote> &sale)
        { items.insert(sale); }
    // prints the total price for each book and the overall total for all items in the basket
    double total_receipt(std::ostream&) const;
private:
    // function to compare shared_ptrs needed by the multiset member
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
        { return lhs->isbn() < rhs->isbn(); }
    // multiset to hold multiple quotes, ordered by the compare member
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
        items{compare};
};
```

**注意点**
* 📋 **类设计**：`Basket` 类使用编译器合成的默认构造函数和拷贝控制成员
* 🔄 **容器选择**：使用 `multiset`（`§11.2.1, p. 423`）保存交易，这样可以存储同一本书的多个交易，并使给定书籍的所有交易保持在一起（`§11.2.2, p. 424`）
* 📋 **术语提醒**：**辅助类(auxiliary classes)**、**multiset**、**合成默认构造函数(synthesized default constructor)**

---

<a id="id6"></a>
## ✅ 知识点6: Basket类中的比较函数设计

**理论**
* **核心主旨总结**：`multiset` 中的元素是 `shared_ptr`，而 `shared_ptr` 没有定义小于运算符(`<`)。因此，我们必须提供自己的比较操作来对元素进行排序（`§11.2.2, p. 425`）。
* **实现细节**：定义了一个名为 `compare` 的**私有静态成员(private static member)**，比较 `shared_ptr` 指向的对象的ISBN。通过类内初始化器(in-class initializer)（`§7.3.1, p. 274`）初始化 `multiset` 以使用此比较函数。

**教材示例代码**
```cpp
// multiset to hold multiple quotes, ordered by the compare member
std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
    items{compare};
```

**注意点**
* 🔧 **声明解析**：从左到右阅读，`items` 是一个 `multiset`，元素类型为 `shared_ptr<Quote>`，使用与 `compare` 成员类型相同的函数进行排序，名为 `items`，使用 `compare` 函数初始化
* 📋 **静态成员**：`compare` 声明为 `static` 因为它不依赖于类的特定对象实例
* 💡 **类型推导**：使用 `decltype(compare)*` 获取函数指针类型

---

<a id="id7"></a>
## ✅ 知识点7: 定义Basket的成员-add_item与total_receipt

**理论**
* **核心主旨总结**：`Basket` 类只定义了两个操作。`add_item` 成员在类内定义，接受一个指向动态分配 `Quote` 的 `shared_ptr` 并将其插入 `multiset`。第二个成员 `total_receipt` 打印购物篮内容的明细账单并返回所有物品的总价。

**注意点**
* 📋 **接口设计**：`add_item` 直接暴露 `shared_ptr` 接口，用户需要处理动态内存分配（如使用 `make_shared`）
* 🔄 **后续改进**：后面会讨论如何隐藏指针，让用户直接使用对象而不必处理内存管理

---

<a id="id8"></a>
## ✅ 知识点8: total_receipt函数实现与批量处理

**教材示例代码**
```cpp
double Basket::total_receipt(ostream &os) const
{
    double sum = 0.0;    // holds the running total
    // iter refers to the first element in a batch of elements with the same ISBN
    // upper_bound returns an iterator to the element just past the end of that batch
    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter)) {
        // we know there's at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << endl; // print the final overall total
    return sum;
}
```

**理论**
* **核心逻辑**：`total_receipt` 通过迭代 `multiset` 来累积总价。对于每个不同的ISBN，它调用 `print_total` 打印该书籍的明细，并将该书籍的总价加到 `sum` 中。

**注意点**
* 📋 **迭代器使用**：`iter` 初始化为 `items.cbegin()`，条件检查是否等于 `items.cend()`
* 🔧 **解引用操作**：`**iter` 是 `Quote` 对象（或派生自 `Quote` 的类型）。第一次解引用得到 `shared_ptr`，第二次解引用得到实际对象
* 📋 **计数函数**：使用 `multiset` 的 `count` 成员（`§11.3.5, p. 436`）确定具有相同键（即相同ISBN）的元素数量

---

<a id="id9"></a>
## ✅ 知识点9: upper_bound与循环增量控制

**理论**
* **核心主旨总结**：`for` 循环的"增量"表达式很有意思。与通常读取每个元素的循环不同，这里通过调用 `upper_bound`（`§11.3.5, p. 438`）将 `iter` 推进到下一个键。`upper_bound` 调用返回指向最后一个具有与 `iter` 相同键的元素之后那个元素的迭代器，即跳过所有与当前键匹配的元素，直接指向下一个不同的书籍或集合末尾。

**注意点**
* 💡 **算法技巧**：这种循环结构允许我们**批量处理**具有相同键的元素（同一本书的多个副本），而不是逐个处理每个元素
* 🔄 **知识关联**：`upper_bound` 是关联容器的重要操作，用于查找键的范围

---

<a id="id10"></a>
## ✅ 知识点10: print_total函数与虚调用

**教材示例代码**
```cpp
sum += print_total(os, **iter, items.count(*iter));
```

**理论**
* **函数参数**：`print_total` 的参数包括：写入的 `ostream`、要处理的 `Quote` 对象、以及计数。
* **虚调用机制**：`print_total` 对 `net_price` 进行**虚调用(virtual call)**，因此生成的价格取决于 `**iter` 的动态类型。`print_total` 函数打印给定书籍的总价并返回计算出的总价，该结果被加到 `sum` 中，在 `for` 循环完成后打印总和。

**注意点**
* 📋 **多态实现**：尽管通过 `shared_ptr` 间接存储，通过适当的解引用（`**iter`）仍然实现了运行时多态
* 💡 **设计模式**：辅助函数 `print_total` 封装了打印和计算逻辑，保持 `total_receipt` 的简洁

---

<a id="id11"></a>
## ✅ 知识点11: 隐藏指针-简化用户接口

**理论**
* **核心主旨总结**：`Basket` 的用户仍然需要处理动态内存，因为 `add_item` 接受 `shared_ptr` 参数。因此，用户必须编写类似 `make_shared<Quote>(...)` 的代码。下一步是重新定义 `add_item`，使其接受 `Quote` 对象而非 `shared_ptr`，由新版本处理内存分配，用户不再需要这样做。
* **重载设计**：定义两个版本，一个复制给定对象，另一个从给定对象移动（`§13.6.3, p. 544`）：

**教材示例代码**
```cpp
void add_item(const Quote& sale);   // copy the given object
void add_item(Quote&& sale);        // move the given object
```

**注意点**
* ⚠️ **潜在问题**：`add_item` 不知道要分配什么类型。当它进行内存分配时，会复制（或移动）其 `sale` 参数。如果使用 `new Quote(sale)`，这会分配一个 `Quote` 类型的对象并复制 `sale` 的 `Quote` 部分。然而，`sale` 可能引用 `Bulk_quote` 对象，在这种情况下，对象会被**切片**。

---

<a id="id12"></a>
## ✅ 知识点12: 模拟虚拷贝-virtual clone机制

**理论**
* **核心主旨总结**：通过给 `Quote` 类添加一个**虚成员(virtual member)** 来解决分配正确类型的问题，该成员分配自身的副本。这称为**模拟虚拷贝(simulating virtual copy)**。
* **clone设计**：定义 `clone` 函数的两个版本（左值和右值版本，基于引用限定符，`§13.6.3, p. 546`），每个 `clone` 函数分配其自身类型的新对象：
  * `const` 左值引用版本将自身复制到新分配的对象
  * 右值引用版本移动其自身数据

**教材示例代码**
```cpp
class Quote {
public:
    // virtual function to return a dynamically allocated copy of itself
    // these members use reference qualifiers; see §13.6.3 (p. 546)
    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
    // other members as before
};

class Bulk_quote : public Quote {
    Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    Bulk_quote* clone() && 
        {return new Bulk_quote(std::move(*this));}
    // other members as before
};
```

**注意点**
* 📋 **返回类型**：派生类的 `clone` 返回 `Bulk_quote*`，基类返回 `Quote*`，这是**协变返回类型(covariant return type)**的合法使用
* 🔧 **引用限定符**：`const &` 版本处理左值，`&&` 版本处理右值，分别执行拷贝和移动
* 💡 **设计模式**：这是**原型模式(Prototype Pattern)**的一种实现，允许通过基类接口复制派生类对象

---

<a id="id13"></a>
## ✅ 知识点13: 基于clone的add_item实现

**教材示例代码**
```cpp
class Basket {
public:
    void add_item(const Quote& sale) // copy the given object
        { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote&& sale)      // move the given object
        { items.insert(
            std::shared_ptr<Quote>(std::move(sale).clone())); }
    // other members as before
};
```

**理论**
* **重载解析**：像 `add_item` 本身一样，`clone` 根据调用它是左值还是右值进行重载。第一个 `add_item` 版本在 `sale` 上调用 `const` 左值版本的 `clone`，第二个版本调用右值引用版本。
* **右值处理细节**：在右值版本中，虽然 `sale` 的类型是右值引用，但 `sale` 本身（像任何其他变量一样）是左值（`§13.6.1, p. 533`）。因此需要调用 `std::move` 将右值引用绑定到 `sale`。
* **虚函数机制**：`clone` 是虚函数，运行 `Quote` 还是 `Bulk_quote` 的版本取决于 `sale` 的动态类型。无论复制还是移动数据，`clone` 都返回指向新分配对象的指针，该对象是其自身的类型。我们将 `shared_ptr` 绑定到该对象并调用 `insert` 添加到 `items`。

**注意点**
* ⚠️ **关键技巧**：注意第二个版本中的 `std::move(sale).clone()`——必须先转换为右值才能调用右值版本的 `clone`
* 🔄 **类型转换**：因为 `shared_ptr` 支持派生类到基类的转换（`§15.2.2, p. 597`），我们可以将 `shared_ptr<Quote>` 绑定到 `Bulk_quote*`
* 📋 **内存管理**：`shared_ptr` 接管 `clone` 分配的原始指针，确保自动内存管理，防止内存泄漏

---

## 🔑 核心要点总结

1. **绝不能直接在容器中存储继承层次的对象**，否则会发生**对象切片(object slicing)**，导致派生类部分被切掉，多态行为失效。

2. **使用智能指针（特别是 `shared_ptr`）间接存储**继承层次中的对象，这样既保持多态性，又自动管理内存。`shared_ptr` 支持派生类到基类的隐式类型转换。

3. **`multiset` 配合自定义比较函数**可以高效管理有序的多重集合，当元素类型（如 `shared_ptr`）没有默认比较操作时，需提供静态比较函数并通过类内初始化器初始化容器。

4. **`upper_bound` 是批量处理关联容器的利器**，可用于跳过具有相同键的所有元素，直接定位到下一个不同的键，实现高效的批量统计（如计算同一本书的总价）。

5. **通过虚拷贝(virtual clone)模拟多态复制**，解决"不知道具体类型时如何正确复制对象"的问题。结合引用限定符实现拷贝和移动两个版本，配合 `shared_ptr` 实现完整的对象生命周期管理。

## 📌 考试速记版

* **对象切片公式**：`vector<Base> v; v.push_back(Derived());` → Derived部分被切掉，只留Base子对象
* **智能指针转换**：`shared_ptr<Derived>` 可隐式转为 `shared_ptr<Base>`，保持多态且自动管理内存
* **multiset比较器**：元素无 `<` 运算符时，定义 `static bool cmp(const T&, const T&)`，容器声明为 `multiset<T, decltype(cmp)*> items{cmp}`
* **批量处理技巧**：`for(auto it = c.begin(); it != c.end(); it = c.upper_bound(*it))` 跳过重复键
* **clone模式**：基类定义 `virtual Base* clone() const & { return new Base(*this); }`，派生类重写返回 `Derived*`，实现虚拷贝

**记忆口诀**：
> 容器存继承，指针别存对象；
> 切片藏隐患，智能指针来护航；
> multiset缺比较，静态函数来帮忙；
> upper_bound跳重复，批量处理效率高；
> 不知类型怎么拷？virtual clone来报道！