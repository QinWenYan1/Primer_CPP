# 📘 12.3 文本查询程序 (A Text-Query Program)

> 来源说明：C++ Primer 12.3 | 本节涵盖：设计并实现一个能够从文件中查询单词出现位置及上下文的简单程序。

---

## 🧠 核心概念总览（严格按原文顺序）

* [*知识点1: 程序目标*](#id1)
* [*知识点2: 设计需求分析*](#id2)
* [*知识点3: 库设施选择*](#id3)
* [*知识点4: 抽象数据结构设计*](#id4)
* [*知识点5: 共享数据问题与解决方案*](#id5)
* [*知识点6: TextQuery 类使用示例*](#id6)
* [*知识点7: TextQuery 类的定义*](#id7)
* [*知识点8: TextQuery 构造函数的实现*](#id8)
* [*知识点9: QueryResult 类的定义*](#id9)
* [*知识点10: query 函数的实现*](#id10)
* [*知识点11: print 函数的实现*](#id11)

---

<a id="id1"></a>
## ✅ 知识点1: 程序目标

**理论**
* **核心主旨总结**：
    * 本节将实现一个简单的文本查询程序。用户可以在给定文件中搜索单词。查询结果包括该单词出现的次数，以及出现该单词的所有行（每行只显示一次，并按行号升序排列）。
* **输出示例**：例如，搜索单词 “element”，输出格式如下：
    `element occurs 112 times`
    `(line 36) A set element contains only a key;`
    `...` （后续行）

---

<a id="id2"></a>
## ✅ 知识点2: 设计需求分析

**理论**
* **核心主旨总结**：
    * **设计程序的起点是列出其必须完成的操作**。
    * 这有助于确定所需的数据结构。
* **程序任务清单**：
    1.  **读取输入时**：必须记住每个单词出现的行号。这需要按行读取输入文件，并将每行拆分成单词。
    2.  **生成输出时**：
        * 必须能根据给定单词获取相关的行号。
        * 行号必须按升序排列且无重复。
        * 必须能打印给定行号在输入文件中对应的文本内容。

---

<a id="id3"></a>
## ✅ 知识点3: 库设施选择

**理论**
* **核心主旨总结**：可以通过组合使用标准库设施来优雅地满足上述需求。
* **数据结构选择**：
    1.  `vector<string>`：存储整个输入文件的副本。文件的每一行是`vector`中的一个元素，便于通过行号（索引）快速获取行文本。
    2.  `istringstream`：用于将每一行文本分解为单词。
    3.  `set`：存储每个单词出现的行号集合。`set`保证元素唯一且自动按升序排列。
    4.  `map`：将每个单词关联到其出现的行号`set`。通过`map`可以根据单词快速查找对应的`set`。
* **附加工具**：解决方案还将使用`shared_ptr`（原因稍后解释）。

---

<a id="id4"></a>
## ✅ 知识点4: 抽象数据结构设计

**理论**
* **核心主旨总结**：
    * 与其直接使用`vector`、`set`和`map`，不如定义一个更抽象的类结构，使查询文件更容易。
* **TextQuery 类**：
    * 负责以易于查询的方式保存输入文件。
    * 它将包含一个`vector`（存储文件文本）和一个`map`（关联每个单词到其行号集合`set`）。
    * 该类需要一个构造函数（读取输入文件）和一个执行查询的操作。
* **查询操作的返回值**：
    * 查询操作需要返回单词的出现频率、行号和对应的行文本。
    * 最简单的方案是定义第二个类。
* **QueryResult 类**：用于保存查询结果。该类将包含一个`print`函数来打印结果。

---

<a id="id5"></a>
## ✅ 知识点5: 共享数据问题与解决方案

**理论**
* **核心主旨总结**：
    * `QueryResult`需要的数据存储在`TextQuery`对象中，因此需要考虑如何访问这些数据。
* **问题分析**：
    * **复制方案开销大**：复制`set`可能代价高昂，而复制`vector`意味着复制整个文件，这对于通常只打印一小部分行的场景不划算。
    * **指针/迭代器方案有风险**：如果返回指向`TextQuery`对象内部数据的指针或迭代器，当`TextQuery`对象先于`QueryResult`被销毁时，`QueryResult`将引用已不存在的无效数据。
* **解决方案**：
    * 由于这两个类在概念上“共享”数据，因此使用<b>`shared_ptr`智能指针</b>来在数据结构中反映这种共享关系，从而自动管理数据的生命周期。

---

<a id="id6"></a>
## ✅ 知识点6: TextQuery 类使用示例

**理论**
* **核心主旨总结**：在设计类之前，**先编写使用该类的程序有助于验证类是否提供了所需的功能**。
* **`runQueries` 函数示例**：该函数展示了如何使用`TextQuery`和`QueryResult`类。它接受一个指向待处理文件的`ifstream`，与用户交互，并打印对给定单词的查询结果。

**教材示例代码**
```cpp
void runQueries(ifstream &infile)
{
    // infile 是一个 ifstream，指向我们要查询的文件
    TextQuery tq(infile);   // 存储文件并建立查询 map
    // 与用户交互：提示输入要查找的单词并打印结果
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // 如果遇到输入结束符或用户输入‘q’，则停止
        if (!(cin >> s) || s == "q") break;
        // 执行查询并打印结果
        print(cout, tq.query(s)) << endl;
    }
}
```



---

<a id="id7"></a>
## ✅ 知识点7: TextQuery 类的定义

**理论**
* **核心主旨总结**：
    * 开始定义`TextQuery`类。用户通过提供一个`istream`来创建对象。
    * 类提供`query`操作，接收一个`string`并返回代表该字符串出现行的`QueryResult`对象。
* **数据成员设计**：考虑到与`QueryResult`对象的共享需求，类包含两个数据成员：
    1.  `shared_ptr<vector<string>> file`：指向动态分配的`vector`，保存输入文件。
    2.  `map<string, shared_ptr<set<line_no>>> wm`：将每个单词映射到一个动态分配的、存储其行号（`line_no`类型）的`set`。
* **类型成员**：为了增加代码可读性，定义了一个类型别名`line_no`，表示行号，即`vector<string>`的索引类型。

**教材示例代码**
```cpp
class QueryResult; // query函数返回类型所需的声明
class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file; // 输入文件
    // 将每个单词映射到包含该单词的行号的 set
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
```

**注意点**
* ⚠️ **前向声明**：因为`query`成员函数的返回类型是`QueryResult`，所以需要在`TextQuery`类定义之前对`QueryResult`类进行前向声明。
* 📋 **类型别名**：`using line_no = ...` 是C++11引入的类型别名语法，等价于 `typedef`。


---

<a id="id8"></a>
## ✅ 知识点8: `TextQuery` 构造函数的实现

**理论**
* **核心主旨总结**：`TextQuery`构造函数接收一个`ifstream`，逐行读取输入文件，填充`file`和`wm`。
* **实现步骤**：
    1.  **初始化**：在构造函数的初始化列表中，为`file`成员分配一个新的`vector<string>`。
    2.  **逐行读取**：使用`getline`读取文件的每一行，并将其压入`file`指向的`vector`。
    3.  **逐字处理**：对于每一行，使用`istringstream`将其分解为单词。对于每个单词：
        * 通过`map`的下标操作`wm[word]`获取与该单词关联的`shared_ptr<set<line_no>>`的引用`lines`。
        * 如果`word`是第一次出现，下标操作会将其添加到`wm`，并值初始化其关联的`shared_ptr`，此时`lines`为空（null）。
        * 如果`lines`为空，则为其分配一个新的`set`，并使用`reset`方法更新`lines`所指的`shared_ptr`。
        * 无论`set`是新建还是已存在，都将当前行号插入到该`set`中。`set`的`insert`操作会自动处理重复行号。

**教材示例代码**
```cpp
TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    while (getline(is, text)) { // 对文件中的每一行
        file->push_back(text); // 保存此行文本
        int n = file->size() - 1; // 当前行号
        istringstream line(text); // 将行文本分解为单词
        string word;
        while (line >> word) { // 对该行中的每个单词
            // 如果单词不在 wm 中，下标操作会添加一个新条目
            auto &lines = wm[word]; // lines 是一个 shared_ptr 的引用
            if (!lines) // 第一次见到该单词时，该指针为空
                lines.reset(new set<line_no>); // 分配一个新的 set
            lines->insert(n); // 将此行号插入 set 中
        }
    }
}
```

**注意点**
* ⚠️ **智能指针操作**：`file`是`shared_ptr`，访问其指向对象的成员需使用`->`运算符，如`file->push_back(text)`。
* ⚠️ **引用与修改**：`auto &lines = wm[word];` 声明了一个引用，对`lines`的操作（如`reset`, `insert`）会直接修改`wm`中对应的`shared_ptr`和其指向的`set`。
* 💡 **行号计算**：行号`n`从0开始，对应`vector`的索引。
* 🔄 **set的去重功能**：如果同一单词在同一行出现多次，`lines->insert(n)`只会插入一次行号`n`，因为`set`的元素是唯一的。

---

<a id="id9"></a>
## ✅ 知识点9: QueryResult 类的定义

**理论**
* **核心主旨总结**：`QueryResult`类包含三个数据成员：查询的单词、指向输入文件`vector`的`shared_ptr`、指向包含行号的`set`的`shared_ptr`。它的主要功能是一个构造函数和一个用于打印的友元函数`print`。
* **构造函数的任务**：简单地将参数存储到对应的数据成员中。

**教材示例代码**
```cpp
class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f):
                sought(s), lines(p), file(f) { }
private:
    std::string sought; // 查询的单词
    std::shared_ptr<std::set<line_no>> lines; // 单词出现的行号集合
    std::shared_ptr<std::vector<std::string>> file; // 输入文件
};
```

**注意点**
* ⚠️ **友元声明**：`print`函数需要访问`QueryResult`的私有成员，因此被声明为友元。
* 🔄 **数据共享**：`lines`和`file`都是`shared_ptr`，指向`TextQuery`对象内部的数据，这体现了两个类之间的数据共享，并借助智能指针管理生命周期。

---

<a id="id10"></a>
## ✅ 知识点10: query 函数的实现

**理论**
* **核心主旨总结**：`query`函数接收一个`string`（要查找的单词），在`map(wm)`中查找对应的`set`。如果找到，就用该单词、文件指针和找到的`set`构造一个`QueryResult`返回。
* **未找到单词的处理**：如果单词不在`map`中，需要返回一个表示“未找到”的结果。这里定义一个**局部静态**的`shared_ptr`，指向一个空的`set<line_no>`。当查找失败时，返回一个指向这个空`set`的`shared_ptr`副本。
* **查找方法**：使用`map`的`find`方法而不是下标操作符`[]`，因为`find`不会在`map`中添加新条目，而`[]`会。

**教材示例代码**
```cpp
QueryResult
TextQuery::query(const string &sought) const
{
    // 如果没找到 sought，我们将返回一个指向此空 set 的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // 使用 find 而不是下标，以避免向 wm 中添加单词
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // 未找到
    else
        return QueryResult(sought, loc->second, file);
}
```

**注意点**
* ⚠️ **局部静态对象**：`static shared_ptr<set<line_no>> nodata(...)`。静态局部对象在函数第一次调用时初始化，并在程序结束时销毁。这里所有“未找到”的查询结果都共享同一个空的`set`，避免了为每次失败查询都创建新`set`的开销。
* ⚠️ **const成员函数**：`query`被声明为`const`，因为它不修改`TextQuery`对象的状态。
* 🔄 **find vs subscript**：`loc = wm.find(sought)`。如果找到，`loc`是一个迭代器，`loc->first`是`key`（单词），`loc->second`是`value`（对应的`shared_ptr<set>`）。

---

<a id="id11"></a>
## ✅ 知识点11: print 函数的实现

**理论**
* **核心主旨总结**：`print`函数负责将`QueryResult`对象的内容格式化输出到给定的流中。
* **输出内容**：
    1.  单词及其出现次数。
    2.  对于该单词出现的每一行，输出行号（调整为从1开始计数）和该行的文本内容。
* **实现细节**：
    * 使用`lines->size()`获取单词出现次数。
    * 使用`make_plural`函数（教材6.3.2节定义）智能地输出“time”或“times”。
    * 遍历`set`中的每个行号。
    * 行号`+1`以符合人类习惯（从1开始计数）。
    * 通过`file->begin() + num`获取迭代器，再解引用得到对应行的文本。

**教材示例代码**
```cpp
ostream &print(ostream & os, const QueryResult &qr)
{
    // 如果找到了单词，打印出现次数和所有出现位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;
    // 打印出现该单词的每一行
    for (auto num : *qr.lines) // 对 set 中的每个元素
        // 行号从0开始计数，为用户友好起见，显示时+1
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}
```

**注意点**
* ⚠️ **迭代器运算**：`qr.file->begin() + num` 利用了`vector`迭代器支持随机访问的特性，直接定位到第`num`个元素。等效于 `(*qr.file)[num]`。
* 💡 **未找到的处理**：当单词未找到时，`qr.lines`指向空`set`。`lines->size()`为0，for循环不会执行，因此函数能正确输出“occurs 0 times”且不打印任何行。
* 📋 **make_plural 函数**：这是一个辅助函数，用于处理英文单词的单复数形式。其实现大致为：`string make_plural(size_t ctr, const string &word, const string &ending) { return (ctr == 1) ? word : word + ending; }`

---

## 🔑 核心要点总结
1.  **设计驱动数据结构**：程序需求决定了需要使用`vector`存储文件行，`map`关联单词到`set`，`set`存储有序唯一的行号。
2.  **智能指针管理共享数据**：使用`shared_ptr`使`TextQuery`和`QueryResult`能够安全地共享底层数据（文件内容和行号集合），而无需担心内存泄漏或悬空指针。
3.  **面向对象封装**：将复杂功能封装到`TextQuery`（负责数据存储与查询）和`QueryResult`（负责表示结果）两个类中，提高了代码的模块化和可维护性。
4.  **关键函数协作**：`runQueries`协调用户交互，`TextQuery::query`执行查询并返回`QueryResult`，`print`负责格式化输出，三者清晰分工。
5.  **边界情况处理**：通过返回指向静态空`set`的`shared_ptr`，优雅地处理了查询单词不存在的情况。

## 📌 考试速记版
* **核心数据结构**：`TextQuery`内部：`shared_ptr<vector<string>> file`, `map<string, shared_ptr<set<line_no>>> wm`。
* **QueryResult内容**：查询单词`sought`，指向行号`set`的`shared_ptr`——`lines`，指向文件`vector`的`shared_ptr`——`file`。
* **未找到的返回值**：`query`函数返回指向静态空`set`的`shared_ptr`。
* **打印行号注意**：内部存储从0开始，输出给用户时需`+1`。
* **重要区别**：在`query`函数中用`map::find`，而**不是**下标运算符`[]`，以避免修改`const`对象和添加不必要的条目。
* **生命周期管理**：`TextQuery`和`QueryResult`通过`shared_ptr`共享数据，确保`QueryResult`对象有效期内，其引用的数据一直存在。

**记忆口诀**：查询程序三件套，`TextQuery`管存找，`QueryResult`装结果，`shared_ptr`保共享，`print`函数来报告。`vector`装行，`map`联词，`set`存号顺序好。`find`查找不添加，行号输出要加一。