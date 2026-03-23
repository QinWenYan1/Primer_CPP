# 📘 15.9 Text Queries Revisited (文本查询再探)

> 来源说明：《C++ Primer》第15章第9节 | 本节涵盖：通过面向对象设计扩展文本查询系统，支持复合查询操作

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 文本查询系统扩展概述*](#id1)
* [*知识点2: 支持的查询类型与示例*](#id2)
* [*知识点3: 复合查询与运算符优先级*](#id3)
* [*知识点4: 面向对象解决方案设计考量*](#id4)
* [*知识点5: 抽象基类 Query_base 的设计*](#id5)
* [*知识点6: 查询类层次结构设计*](#id6)
* [*知识点7: 关键概念 - 继承与组合*](#id7)
* [*知识点8: 在接口类中隐藏层次结构*](#id8)
* [*知识点9: 查询表达式创建的对象树*](#id9)
* [*知识点10: 表15.1 查询程序设计回顾*](#id10)
* [*知识点11: Query_base 和 Query 类定义*](#id11)
* [*知识点12: Query 输出运算符*](#id12)
* [*知识点13: 派生类概述*](#id13)
* [*知识点14: WordQuery 类*](#id14)
* [*知识点15: Query 构造函数（字符串版本）*](#id15)
* [*知识点16: NotQuery 类与 ~ 运算符*](#id16)
* [*知识点17: BinaryQuery 类*](#id17)
* [*知识点18: AndQuery 与 OrQuery 类及相关运算符*](#id18)
* [*知识点19: eval 函数概述*](#id19)
* [*知识点20: OrQuery::eval 实现*](#id20)
* [*知识点21: AndQuery::eval 实现*](#id21)
* [*知识点22: NotQuery::eval 实现*](#id22)

---

<a id="id1"></a>
## ✅ 知识点1: 文本查询系统扩展概述

**理论**
* 本节作为继承的最终示例，扩展了`§12.3`中的文本查询应用程序
* 原始类只能查找给定单词在文件中的出现位置
* 目标是扩展系统以支持更复杂的查询

**注意点**
* 💡 **学习重点**：这是综合运用面向对象设计原则（继承、多态、抽象基类）的完整案例


---

<a id="id2"></a>
## ✅ 知识点2: 支持的查询类型与示例

**理论**
* 示例使用一个简单的故事文本进行查询演示
* 系统支持以下四种查询类型：

**1. 单词查询**
* 查找匹配给定`string`的所有行
* 示例：查询 `Daddy`
* 输出显示：`Daddy`出现3次，并列出包含该词的行（第2、7、10行）

**2. 非查询**
* 使用 `~` 运算符，返回不匹配查询的行
* 示例：`~(Alice)`
* 输出显示：`~(Alice)`出现9次，列出不包含`Alice`的行（第2、3、4行等）

**3. 或查询**
* 使用 `|` 运算符，返回匹配两个查询中任意一个的行
* 示例：`(hair | Alice)`
* 输出显示：`(hair | Alice)`出现2次，列出包含`hair`或`Alice`的行（第1、3行）

**4. 与查询**
* 使用 `&` 运算符，返回同时匹配两个查询的行
* 示例：`(hair & Alice)`
* 输出显示：`(hair & Alice)`出现1次，列出同时包含`hair`和`Alice`的行（第1行）


---

<a id="id3"></a>
## ✅ 知识点3: 复合查询与运算符优先级

**理论**
* 支持组合这些操作，例如：`fiery & bird | wind`
* **使用正常的C++优先级规则**（§4.1.2）来评估复合表达式
* 因此，查询 `fiery & bird | wind` 匹配以下两种情况的行：
  * 同时包含 `fiery` 和 `bird` 的行
  * 或者包含 `wind` 的行

**复合查询示例**
* 查询：`((fiery & bird) | wind)`
* 结果出现3次：
  * (line 2) Her Daddy says when the wind blows
  * (line 4) like a fiery bird in flight
  * (line 5) A beautiful fiery bird, he tells her

**注意点**
* ⚠️ **优先级重要**：C++正常的运算符优先级会影响查询解释，建议使用括号明确优先级


---

<a id="id4"></a>
## ✅ 知识点4: 面向对象解决方案设计考量

**理论**
* **初步想法**：使用 `§12.3.2`的 `TextQuery` 类表示单词查询，并从该类派生其他查询
* **设计缺陷**：这种设计是有缺陷的
* **原因分析**：
  * 考虑非查询：单词查询查找特定单词，但非查询需要能够识别被否定的单词
  * 一般情况下，不存在这样的单词。相反，非查询包含一个查询（单词查询或其他任何类型的查询），并对其结果取反
  * 类似地，与查询和或查询包含两个查询，并组合它们的结果

**核心观察**
* 这一观察表明，应将不同类型的查询建模为**独立的类**，它们共享一个**共同的基类**

**各类查询表示**
```cpp
WordQuery    // Daddy
NotQuery     // ~Alice
OrQuery      // hair | Alice
AndQuery     // hair & Alice
```

**注意点**
* 💡 **设计原则**：当"Is A"关系不成立时，不应使用继承。Not query不是某种Word query，而是包含一个Word query


---

<a id="id5"></a>
## ✅ 知识点5: 抽象基类 `Query_base`的设计

**理论**
* 这些类将只有两个操作：
  1. `eval`：接受`TextQuery`对象并返回`QueryResult`。该函数使用给定的`TextQuery`对象查找查询匹配的行
  2. `rep`：返回底层查询的 `string`表示。该函数被`eval`用于创建表示匹配的 `QueryResult`，也被输出运算符用于打印查询表达式

**抽象基类定义**
* 四个查询类型不是通过继承相关的，它们是概念上的兄弟
* 每个类共享相同的接口，这表明需要定义一个**抽象基类**（§15.4）来表示该接口
* 抽象基类命名为 `Query_base`，表明其作用是作为查询层次结构的根

**纯虚函数**
* `Query_base` 类将`eval`和 `rep`定义为**纯虚函数**（§15.4）
* 每个表示特定查询类型的类都必须**覆盖**这些函数
* `WordQuery`和`NotQuery`直接从 `Query_base`派生

**注意点**
* ⚠️ **重要限制**：含有纯虚函数的类是抽象类，不能创建该类型的对象

---

<a id="id6"></a>
## ✅ 知识点6: 查询类层次结构设计

**理论**
* `AndQuery`和`OrQuery`类共享一个其他类不具备的属性：每个都有**两个操作数**
* 为建模这一属性，定义另一个抽象基类 `BinaryQuery`，表示具有两个操作数的查询
* `AndQuery`和`OrQuery`类将从 `BinaryQuery`继承，而 `BinaryQuery`又从`Query_base`继承
* 这些决策产生的类设计如下所示

**类层次结构(Class Hierarchy)**
```
Query_base (抽象基类)
    ├── WordQuery
    ├── NotQuery
    └── BinaryQuery (抽象基类)
            ├── AndQuery
            └── OrQuery
```

**注意点**
* 💡 **设计技巧**：识别共同特征（两个操作数）并提取中间抽象层 `BinaryQuery`，避免代码重复

---

<a id="id7"></a>
## ✅ 知识点7: 关键概念 - 继承与组合

**理论**
* 继承层次结构的设计本身是一个复杂的主题，超出了本书范围。但有一个重要的设计准则非常基础，每个程序员都应该熟悉：
* **"Is A"关系**：
    * 当定义一个类公开继承自另一个类时，派生类应该反映与基类的"Is A"关系。
    * 在设计良好的类层次结构中，公开派生类的对象可以在需要基类对象的任何地方使用。
* **"Has A"关系**：
    * 类型之间的另一种常见关系是"Has A"关系。
    * 通过"Has A"关系相关的类型意味着成员资格。
* 在书店示例中:
    * 基类代表以规定价格出售的书籍报价概念。
    * `Bulk_quote`"是一种(Is A)"报价，但具有不同的定价策略。
    * 书店类"有一个(Has A)"价格和一个ISBN。

**注意点**
* 💡 **核心设计原则**：继承表示"Is A"（是一种），组合/成员表示"Has A"（有一个）
* ⚠️ **常见错误**：滥用继承（如让`Not query`继承`Word query`）会破坏"Is A"语义

---

<a id="id8"></a>
## ✅ 知识点8: 在接口类中隐藏层次结构

**理论**
* 程序将处理评估查询，而不是构建查询(building them)。然而，为了能够运行程序，需要能够创建查询
* 最简单的方法是编写C++表达式来创建查询。例如，希望通过编写如下代码生成前面描述的复合查询：
```cpp
Query q = Query("fiery") & Query("bird") | Query("wind");
```

**接口类设计**
* 问题描述隐含表明用户级代码不会直接使用继承的类
* 相反，定义一个名为 **Query** 的**接口类(interface class)**来隐藏层次结构
* **Query** 类将存储指向 **Query_base** 的指针(pointer)
* 该指针将绑定到从 **Query_base** 派生的类型的对象
* **Query** 类将提供与 **Query_base** 类相同的操作：**eval** 用于评估关联查询，**rep** 用于生成查询的字符串版本
* 它还将定义一个**重载的输出运算符(overloaded output operator)**来显示关联查询

**运算符重载(Operator Overloading)设计**
* 用户将通过 **Query** 对象上的操作间接创建和操作 **Query_base** 对象
* 在 **Query** 对象上定义三个重载运算符：
  * **& 运算符**：生成绑定到新 **AndQuery** 的 **Query**
  * **| 运算符**：生成绑定到新 **OrQuery** 的 **Query**
  * **~ 运算符**：生成绑定到新 **NotQuery** 的 **Query**
* 接受 **string** 的 **Query** 构造函数将生成新的 **WordQuery**

**注意点**
* 📋 **设计模式**：接口类(Query) + 实现继承层次(Query_base)，这是一种常见的设计模式，封装了实现细节
* 💡 **动态分配**：这些运算符函数将动态分配(dynamic allocate)从 **Query_base** 派生的类型的新对象

---

<a id="id9"></a>
## ✅ 知识点9: 查询表达式创建的对象树

**理论**
* 重要的是要意识到应用程序中的大部分工作在于构建对象来表示用户的查询
* 例如，上述表达式生成的相关对象集合如图15.3所示
* 一旦对象树(object tree)建立，评估（或生成查询的表示）基本上是一个由编译器管理的过程，遵循这些链接，要求每个对象评估（或显示）自身
* 例如，如果在 **q** 上调用 **eval**（即在树的根上），该调用要求 **OrQuery**（**q** 指向的对象）评估自身
* 评估此 **OrQuery** 会对其两个操作数调用 **eval** —— 对 **AndQuery** 和查找单词 **wind** 的 **WordQuery**
* 评估 **AndQuery** 会评估其两个 **WordQuery**，分别为单词 **fiery** 和 **bird** 生成结果

**注意点**
* 💡 **递归评估**：查询评估是递归过程，从根节点向下遍历树结构
* 🔄 **知识关联**：这是**组合模式(Composite Pattern)**的典型应用，统一处理单个对象和组合对象

---

<a id="id10"></a>
## ✅ 知识点10: 表15.1 查询程序设计回顾

**理论**
* 表15.1总结了本示例中使用的类，包括接口类和实现类

**查询程序接口类和操作(Query Program Interface Classes and Operations)**

| 类/操作 | 描述 |
|---------|------|
| **TextQuery** | 读取给定文件并构建查找映射的类。该类具有一个查询操作，接受 **string** 参数并返回 **QueryResult**，表示该 **string** 出现的行（§12.3.2，第487页） |
| **QueryResult** | 保存查询操作结果的类（§12.3.2，第489页） |
| **Query** | 指向从 **Query_base** 派生的类型对象的接口类 |
| **Query q(s)** | 将 **Query q** 绑定到持有 **string s** 的新 **WordQuery** |
| **q1 & q2** | 返回绑定到持有 **q1** 和 **q2** 的新 **AndQuery** 对象的 **Query** |
| **q1 \| q2** | 返回绑定到持有 **q1** 和 **q2** 的新 **OrQuery** 对象的 **Query** |
| **~q** | 返回绑定到持有 **q** 的新 **NotQuery** 对象的 **Query** |

**查询程序实现类(Query Program Implementation Classes)**

| 类 | 描述 |
|-----|------|
| **Query_base** | 查询类的抽象基类 |
| **WordQuery** | 从 **Query_base** 派生的类，查找给定单词 |
| **NotQuery** | 从 **Query_base** 派生的类，返回其 **Query** 操作数不出现的行集合 |
| **BinaryQuery** | 从 **Query_base** 派生的抽象基类，表示具有两个 **Query** 操作数的查询 |
| **OrQuery** | 从 **BinaryQuery** 派生的类，返回其两个操作数出现的行号的并集(union) |
| **AndQuery** | 从 **BinaryQuery** 派生的类，返回其两个操作数出现的行号的交集(intersection) |

**注意点**
* 📋 **表格重要性**：此表完整列出了整个查询系统的架构，是理解设计的关键参考
* ⚠️ **区分接口与实现**：Query是用户接口，Query_base及派生类是实现细节

---

<a id="id11"></a>
## ✅ 知识点11: Query_base 和 Query 类定义

**理论**
* 从定义 **Query_base** 类开始实现

**Query_base 类定义**
```cpp
// 抽象类作为具体查询类型的基类；所有成员都是私有的
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;  // 用于eval函数
    virtual ~Query_base() = default;
private:
    // eval返回匹配此查询的QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep是查询的字符串表示
    virtual std::string rep() const = 0;
};
```

* **eval** 和 **rep** 都是**纯虚函数**，这使得 **Query_base** 成为抽象基类（§15.4，第610页）
* 因为不打算让用户或派生类直接使用 **Query_base**，所以 **Query_base** 没有 **public** 成员
* **Query_base** 的所有使用都将通过 **Query** 对象进行
* 授予 **Query** 类友元(friendship)权限，因为 **Query** 的成员将调用 **Query_base** 中的虚函数
* **protected** 成员 **line_no** 将在 **eval** 函数内部使用
* 类似地，**析构函数(destructor)**是 **protected** 的，因为它被派生类的析构函数（隐式）使用

**Query 类定义**
* **Query** 类提供（并隐藏）**Query_base** 继承层次结构的接口
* 每个 **Query** 对象将持有一个 **shared_ptr** 指向相应的 **Query_base** 对象
* 因为 **Query** 是 **Query_base** 类的唯一接口，所以 **Query** 必须定义自己的 **eval** 和 **rep** 版本

```cpp
// 管理Query_base继承层次结构的接口类
class Query {
    // 这些运算符需要访问shared_ptr构造函数
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);  // 构建新的WordQuery
    // 接口函数：调用相应的Query_base操作
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query): q(query) { }
    std::shared_ptr<Query_base> q;
};
```

* 接受 **string** 的 **Query** 构造函数将创建新的 **WordQuery** 并将其 **shared_ptr** 成员绑定到新创建的对象
* **&**、**|** 和 **~** 运算符将分别创建 **AndQuery**、**OrQuery** 和 **NotQuery** 对象
* 这些运算符将返回绑定到其新生成对象的 **Query** 对象
* 为了支持这些运算符，**Query** 需要一个接受 **shared_ptr** 指向 **Query_base** 的构造函数并存储给定指针
* 将此构造函数设为 **private**，因为不打算让一般用户代码定义 **Query_base** 对象
* 因为此构造函数是私有的，所以需要将这些运算符设为**友元(friends)**

**注意点**
* ⚠️ **访问控制**：Query_base全是private，通过友元授予Query访问权限；Query的构造函数是private，通过友元授予运算符访问权限
* 💡 **智能指针使用**：使用shared_ptr管理Query_base对象的生命周期，自动处理内存管理
* 📋 **术语**：shared_ptr（共享指针），friend（友元），protected（受保护的）

---

<a id="id12"></a>
## ✅ 知识点12: Query 输出运算符

**理论**
* 输出运算符是整体查询系统工作原理的一个好例子

**输出运算符实现**
```cpp
std::ostream &
operator<<(std::ostream &os, const Query &query)
{
    // Query::rep通过其Query_base指针进行虚调用到rep()
    return os << query.rep();
}
```

**工作原理**
* 当打印 **Query** 时，输出运算符调用 **Query** 类的 **rep** 成员
* 该函数通过其指针成员对 **Query** 指向的对象的 **rep** 成员进行**虚调用(virtual call)**
* 即，当写入以下代码时：
```cpp
Query andq = Query(sought1) & Query(sought2);
cout << andq << endl;
```
* 输出运算符在 **andq** 上调用 **Query::rep**
* **Query::rep** 通过其 **Query_base** 指针进行虚调用到 **Query_base** 版本的 **rep**
* 因为 **andq** 指向 **AndQuery** 对象，该调用将运行 **AndQuery::rep**

**注意点**
* 💡 **虚调用链**：operator<< → Query::rep → Query_base::rep（虚调用）→ AndQuery::rep（动态绑定）
* 🔄 **多态性体现**：同样的代码可以根据实际对象类型调用不同的rep实现

---

<a id="id13"></a>
## ✅ 知识点13: 派生类概述

**理论**
* 从 **Query_base** 派生的类最有趣的部分是它们如何被表示
* **WordQuery** 类最简单直接，其工作是保存搜索词(search word)
* 其他类操作一个或两个操作数：
  * **NotQuery** 有一个操作数(operand)
  * **AndQuery** 和 **OrQuery** 有两个操作数
* 在这些类的每一个中，操作数可以是任何从 **Query_base** 派生的具体类的对象：
  * **NotQuery** 可以应用于 **WordQuery**、**AndQuery**、**OrQuery** 或另一个 **NotQuery**
* 为了允许这种灵活性，操作数必须存储为 **Query_base** 指针。这样可以将指针绑定到我们需要的任何具体类

**使用 Query 对象简化**
* 然而，不是存储 **Query_base** 指针，我们的类将使用 **Query** 对象
* 就像使用接口类简化了用户代码一样，我们可以通过使用相同的类来简化自己的类代码

**注意点**
* 💡 **设计一致性**：实现类内部也使用Query接口类，而不是直接使用Query_base指针，保持一致性并简化代码
* 📋 **灵活性**：NotQuery可以嵌套，支持复杂查询表达式

---

<a id="id14"></a>
## ✅ 知识点14: WordQuery 类

**理论**
* **WordQuery** 查找给定的 **string**
* 这是唯一实际在给定 **TextQuery** 对象上执行查询的操作

**WordQuery 类定义**
```cpp
class WordQuery: public Query_base {
    friend class Query; // Query使用WordQuery构造函数
    WordQuery(const std::string &s): query_word(s) { }
    // 具体类：WordQuery定义所有继承的纯虚函数
    QueryResult eval(const TextQuery &t) const
        { return t.query(query_word); }
    std::string rep() const { return query_word; }
    std::string query_word;   // 要搜索的单词
};
```

* 像 **Query_base** 一样，**WordQuery** 没有 **public** 成员
* **WordQuery** 必须将 **Query** 设为友元以允许 **Query** 访问 **WordQuery** 构造函数
* 每个具体查询类都必须定义继承的纯虚函数 **eval** 和 **rep**
* 我们在 **WordQuery** 类体内定义了两个操作：
  * **eval** 调用其给定 **TextQuery** 参数的 **query** 成员，该成员在文件中执行实际搜索
  * **rep** 返回此 **WordQuery** 表示的 **string**（即 **query_word**）

**注意点**
* 📋 **具体类(Concrete Class)**：WordQuery是具体类，实现了所有纯虚函数，可以创建对象
* 💡 **唯一执行者**：WordQuery是唯一真正访问TextQuery数据的类，其他查询类都是在此基础上组合

---

<a id="id15"></a>
## ✅ 知识点15: Query 构造函数（字符串版本）

**理论**
* 定义了 **WordQuery** 类后，现在可以定义接受 **string** 的 **Query** 构造函数

**构造函数实现**
```cpp
inline
Query::Query(const std::string &s): q(new WordQuery(s)) { }
```

* 此构造函数分配 **WordQuery** 并将其指针成员初始化为指向新分配的对象

**注意点**
* 💡 **隐式转换**：接受string的Query构造函数允许从string隐式转换为Query对象
* ⚠️ **动态分配**：使用new动态分配WordQuery对象，由shared_ptr管理

---

<a id="id16"></a>
## ✅ 知识点16: NotQuery 类与 ~ 运算符

**理论**
* **~ 运算符**生成 **NotQuery**，它持有并对其取反的 **Query**

**NotQuery 类定义**
```cpp
class NotQuery: public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }
    // 具体类：NotQuery定义所有继承的纯虚函数
    std::string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}
```

**实现细节**
* 因为 **NotQuery** 的成员都是 **private**，首先将 **~ 运算符**设为友元
* 为了表示 **NotQuery**，将 **~** 符号与底层 **Query** 的表示连接起来
* 对输出加括号以确保优先级(precedence)对读者清晰
* 值得注意的是，**NotQuery** 自己的 **rep** 成员中对 **rep** 的调用最终进行虚调用：
  * **query.rep()** 是对 **Query** 类 **rep** 成员的非虚调用
  * **Query::rep** 调用 **q->rep()**，这是通过其 **Query_base** 指针的虚调用
* **~ 运算符**动态分配新的 **NotQuery** 对象
* 返回（隐式）使用接受 **shared_ptr<Query_base>** 的 **Query** 构造函数
* 即，**return** 语句等价于：
```cpp
// 分配新的NotQuery对象
// 将生成的NotQuery指针绑定到shared_ptr<Query_base>
shared_ptr<Query_base> tmp(new NotQuery(expr));
return Query(tmp); // 使用接受shared_ptr的Query构造函数
```

**注意点**
* ⚠️ **运算符友元**：需要将operator~设为友元以访问private构造函数
* 💡 **字符串构建**：rep()构建带括号的字符串表示，如"~(Alice)"
* 🔄 **递归表示**：query.rep()会调用实际Query对象的rep，形成递归构建

---

<a id="id17"></a>
## ✅ 知识点17: BinaryQuery 类

**理论**
* **BinaryQuery** 类是一个**抽象基类(abstract base class)**，保存需要两个操作数的查询类型所需的数据

**BinaryQuery 类定义**
```cpp
class BinaryQuery: public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) { }
    // 抽象类：BinaryQuery不定义eval
    std::string rep() const { return "(" + lhs.rep() + " " 
                                    + opSym + " " 
                                    + rhs.rep() + ")"; }
    Query lhs, rhs;    // 右侧和左侧操作数
    std::string opSym; // 运算符名称
};
```

* **BinaryQuery** 中的数据是两个 **Query** 操作数和相应的运算符符号(operator symbol)
* 构造函数接受两个操作数和运算符符号，每个都存储在相应的数据成员中
* 为了表示 **BinaryOperator**，生成由左操作数的表示、后跟运算符、后跟右操作数的表示组成的带括号表达式(parenthesized expression)
* 与显示 **NotQuery** 时一样，对 **rep** 的调用最终对 **lhs** 和 **rhs** 指向的 **Query_base** 对象的 **rep** 函数进行虚调用

**注意**
* **BinaryQuery** 类没有定义 **eval** 函数，因此继承了一个纯虚函数
* 因此，**BinaryQuery** 也是一个抽象基类，**不能创建 BinaryQuery 类型的对象**

**注意点**
* ⚠️ **抽象类**：BinaryQuery不实现eval，保持抽象，强制派生类必须实现eval
* 📋 **数据成员**：lhs（左操作数），rhs（右操作数），opSym（运算符符号）
* 💡 **rep实现**：BinaryQuery实现了rep，派生类继承此实现即可

---

<a id="id18"></a>
## ✅ 知识点18: AndQuery 与 OrQuery 类及相关运算符

**理论**
* **AndQuery** 和 **OrQuery** 类（及其相应的运算符）彼此非常相似

**AndQuery 类定义**
```cpp
class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "&") { }
    // 具体类：AndQuery继承rep并定义剩余的纯虚函数
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
```

**OrQuery 类定义**
```cpp
class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "|") { }
    QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
```

**实现细节**
* 这些类使相应的运算符成为友元，并定义构造函数以使用适当的运算符创建其 **BinaryQuery** 基部分
* 它们继承 **BinaryQuery** 的 **rep** 定义，但每个都**覆盖(overrides)** **eval** 函数
* 像 **~ 运算符**一样，**&** 和 **|** 运算符返回绑定到新分配对象的 **shared_ptr**
* 该 **shared_ptr** 在每个这些运算符的 **return** 语句中作为 **Query** 的一部分被转换

**注意点**
* 📋 **覆盖(override)**：AndQuery和OrQuery继承rep但覆盖eval，实现不同的查询逻辑
* 💡 **友元运算符**：运算符需要是友元以访问private构造函数
* ⚠️ **返回值转换**：shared_ptr<Query_base>自动转换为Query对象（通过Query的private构造函数，需要友元）

---

<a id="id19"></a>
## ✅ 知识点19: eval 函数概述

**理论**
* **eval 函数**是查询系统的核心
* 这些函数中的每一个都对其操作数调用 **eval**，然后应用自己的逻辑：
  * **OrQuery** 的 **eval** 操作返回其两个操作数结果的**并集(union)**
  * **AndQuery** 返回**交集(intersection)**
  * **NotQuery** 更复杂：它必须返回**不在其操作数集合中的行号**

**QueryResult 支持**
* 为了支持 **eval** 函数中的处理，需要使用 **QueryResult** 的版本，该版本定义了在 **§12.3.2**（第490页）的练习中添加的成员
* 假设 **QueryResult** 具有 **begin** 和 **end** 成员，允许遍历 **QueryResult** 保存的行号集合
* 还假设 **QueryResult** 有一个名为 **get_file** 的成员，返回指向执行查询的底层文件的 **shared_ptr**

**警告**
* ⚠️ **前置条件**：Query 类使用在 **§12.3.2**（第490页）的练习中为 **QueryResult** 定义的成员

---

<a id="id20"></a>
## ✅ 知识点20: OrQuery::eval 实现

**理论**
* **OrQuery** 表示其两个操作数结果的并集(union)，通过对每个操作数调用 **eval** 获得
* 因为这些操作数是 **Query** 对象，调用 **eval** 是对 **Query::eval** 的调用，后者又进行虚调用到基础 **Query_base** 对象的 **eval**
* 这些调用中的每一个都产生一个 **QueryResult**，表示其操作数出现的行号
* 将这些行号组合成一个新集合

**OrQuery::eval 代码逻辑**
```cpp
// 返回其操作数结果集的并集
QueryResult
OrQuery::eval(const TextQuery& text) const
{
    // 通过Query成员进行虚调用，lhs和rhs
    // 对eval的调用返回每个操作数的QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    // 将左侧操作数的行号复制到结果集
    auto ret_lines = 
        make_shared<set<line_no>>(left.begin(), left.end());
    // 插入右侧操作数的行
    ret_lines->insert(right.begin(), right.end());
    // 返回表示lhs和rhs并集的新QueryResult
    return QueryResult(rep(), ret_lines, left.get_file());
}
```

**实现细节**
* 使用接受一对迭代器的 **set** 构造函数初始化 **ret_lines**
* **QueryResult** 的 **begin** 和 **end** 成员返回指向该对象行号集合的迭代器
* 因此，**ret_lines** 是通过复制 **left** 集合的元素创建的
* 接下来在 **ret_lines** 上调用 **insert** 以插入来自 **right** 的元素
* 在此调用之后，**ret_lines** 包含出现在 **left** 或 **right** 中的行号
* **eval** 函数通过构建并返回表示组合匹配的 **QueryResult** 结束
* **QueryResult** 构造函数（§12.3.2，第489页）接受三个参数：
  1. 表示查询的 **string**
  2. 指向匹配行号集合的 **shared_ptr**
  3. 指向表示输入文件的 **vector** 的 **shared_ptr**
* 调用 **rep** 生成 **string**，调用 **get_file** 获取指向文件的 **shared_ptr**
* 因为 **left** 和 **right** 引用相同的文件，使用哪个调用 **get_file** 并不重要

**注意点**
* 💡 **算法步骤**：1)评估左右操作数 2)创建结果集（复制左侧）3)插入右侧 4)返回QueryResult
* 📋 **STL使用**：使用set的构造函数和insert方法，自动处理重复行号（集合特性）
* 🔄 **文件处理**：通过get_file()获取原始文件指针，用于显示查询结果上下文

---

<a id="id21"></a>
## ✅ 知识点21: AndQuery::eval 实现

**理论**
* **AndQuery** 版本的 **eval** 类似于 **OrQuery** 版本，不同之处在于它调用库算法来查找两个查询共有的行

**AndQuery::eval 代码逻辑**
```cpp
// 返回其操作数结果集的交集
QueryResult
AndQuery::eval(const TextQuery& text) const
{
    // 通过Query操作数进行虚调用以获取操作数的结果集
    auto left = lhs.eval(text), right = rhs.eval(text);
    // 保存left和right交集的set
    auto ret_lines = make_shared<set<line_no>>();
    // 将两个范围的交集写入目标迭代器
    // 此调用中的目标迭代器向ret添加元素
    set_intersection(left.begin(), left.end(),
                    right.begin(), right.end(),
                    inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
```

**算法解释**
* 这里使用库 **set_intersection** 算法，描述见**附录A.2.8**（第880页），合并这两个集合
* **set_intersection** 算法接受**五个迭代器**。它使用前四个表示两个输入序列（§10.5.2，第413页）
* 最后一个参数表示目标位置(destination)。算法将出现在两个输入序列中的元素写入目标
* 在此调用中，传递**插入迭代器(insert iterator)**（§10.4.1，第401页）作为目标
* 当 **set_intersection** 写入此迭代器时，效果将是向 **ret_lines** 插入新元素
* 像 **OrQuery** 的 **eval** 函数一样，这个函数通过构建并返回表示组合匹配的 **QueryResult** 结束

**注意点**
* 📋 **STL算法**：set_intersection需要五个参数（四个输入迭代器+一个输出迭代器）
* 💡 **插入迭代器**：使用inserter适配器将算法输出转换为set的插入操作
* ⚠️ **前提条件**：left和right的结果集必须是有序的（set自动保证），set_intersection才能正确工作

---

<a id="id22"></a>
## ✅ 知识点22: NotQuery::eval 实现

**理论**
* **NotQuery** 查找操作数未找到的文本的每一行

**NotQuery::eval 代码逻辑**
```cpp
// 返回不在其操作数结果集中的行
QueryResult
NotQuery::eval(const TextQuery& text) const
{
    // 通过Query操作数进行虚调用eval
    auto result = query.eval(text);
    // 从空结果集开始
    auto ret_lines = make_shared<set<line_no>>();
    // 我们必须遍历操作数出现的行
    auto beg = result.begin(), end = result.end();
    // 对于输入文件中的每一行，如果该行不在result中，
    // 将该行号添加到ret_lines
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        // 如果我们还没有处理result中的所有行
        // 检查此行是否存在
        if (beg == end || *beg != n)
            ret_lines->insert(n);  // 如果不在result中，添加此行
        else if (beg != end)
            ++beg; // 否则获取result中的下一个行号（如果有的话）
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
```

**算法解释**
* 像其他 **eval** 函数一样，首先对此对象的**操作数(operand)**调用 **eval**
* 该调用返回 **QueryResult**，包含操作数出现的行号
* 但我们想要的是操作数**不出现**的行号。即，我们想要文件中不在 **result** 中的每一行
* 通过遍历直到输入文件大小的顺序整数来生成该集合
* 将每个不在 **result** 中的数字放入 **ret_lines**
* 定位 **beg** 和 **end** 以表示 **result** 中第一个和最后一个元素之后的位置
* 该对象是 **set**，因此当遍历它时，我们将按**升序(ascending order)**获得行号
* 循环体检查当前数字是否在 **result** 中。如果不在，将该数字添加到 **ret_lines**
* 如果数字在 **result** 中，递增 **beg**（它是进入 **result** 的迭代器）
* 一旦处理了所有行号，返回包含 **ret_lines** 的 **QueryResult**，以及运行 **rep** 和 **get_file** 的结果，如之前的 **eval** 函数中所述

**注意点**
* 💡 **逻辑取反**：NotQuery是"补集"操作，需要遍历文件所有行（0到size），排除result中的行
* ⚠️ **迭代器管理**：使用beg和end遍历result集合，与文件行号n同步前进，算法复杂度为O(N)其中N是文件行数
* 🔄 **有序性利用**：利用set和行号都是升序的特性，使用双指针技术（文件行号n和result迭代器beg）高效遍历

---

## 🔑 核心要点总结

1. **"Is A" vs "Has A"**：继承表示"Is A"关系（如AndQuery是一种BinaryQuery），成员表示"Has A"关系（如NotQuery有一个Query操作数）。错误地使用继承（如让NotQuery继承WordQuery）会破坏设计。

2. **抽象基类与虚函数**：Query_base定义纯虚函数eval和rep，建立接口契约；具体派生类（WordQuery, NotQuery, AndQuery, OrQuery）必须实现这些函数。

3. **接口类封装**：Query类作为接口类隐藏了复杂的继承层次，对外提供统一接口，内部使用shared_ptr<Query_base>管理多态对象，简化了用户代码。

4. **运算符重载与对象树**：通过重载&、|、~运算符动态创建查询对象，构建表达式树（如fiery & bird | wind）；eval操作通过递归遍历树（虚调用）实现查询求值。

5. **复合查询算法**：OrQuery使用集合并集（set_union逻辑，实际使用insert），AndQuery使用set_intersection，NotQuery通过遍历文件所有行并排除操作数结果集实现取反。

---

## 📌 考试速记版

* **类层次结构**：Query_base（抽象）→ WordQuery, NotQuery, BinaryQuery（抽象）→ AndQuery, OrQuery

* **关键运算符**：&（AndQuery）、|（OrQuery）、~（NotQuery）、接受string的Query构造函数（WordQuery）

* **eval逻辑**：
  * **OrQuery**：并集，左侧结果集insert右侧所有元素
  * **AndQuery**：交集，使用set_intersection算法
  * **NotQuery**：补集，遍历0~file_size，排除operand结果集中的行

* **rep构建规则**：
  * WordQuery：直接返回query_word
  * NotQuery："~(" + operand.rep() + ")"
  * BinaryQuery："(" + left.rep() + " " + opSym + " " + right.rep() + ")"

* **访问控制要点**：
  * Query_base全private，grant friendship给Query
  * 派生类构造函数private，grant friendship给相应运算符
  * Query接受shared_ptr的构造函数private，grant friendship给运算符

**记忆口诀**："字非并或四查询，基类抽象定接口；运算符重载建对象，递归虚调eval走；与交或并非取反，结果构造返文件。"