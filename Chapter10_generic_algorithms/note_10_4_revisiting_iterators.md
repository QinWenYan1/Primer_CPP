# 📘 10.4 Revisiting Iterators (重新认识迭代器)

> 来源说明：《C++ Primer》 10.4 | 本节涵盖：C++标准库中除容器迭代器外的特殊迭代器类型及其使用，包括插入迭代器、流迭代器、反向迭代器、移动迭代器。

---

## 🧠 核心概念总览

* [*知识点1: 迭代器概述*](#id1)
* [*知识点2: 插入迭代器*](#id2)
* [*知识点3: 流迭代器操作总览*](#id12)
* [*知识点3: 流迭代器-输入流迭代器*](#id3)
* [*知识点4: 流迭代器-输出流迭代器*](#id4)
* [*知识点5: 流迭代器与算法*](#id5)
* [*知识点6: 流迭代器允许延迟求值*](#id6)
* [*知识点7: 流迭代器与类类型*](#id7)
* [*知识点8: 反向迭代器*](#id8)
* [*知识点9: 反向迭代器的要求与限制*](#id9)
* [*知识点10: 反向迭代器与普通迭代器的关系*](#id10)
* [*知识点11: 反向迭代器示例*](#id11)

---

<a id="id1"></a>
## ✅ 知识点1: 迭代器概述

**理论**
* 除了为每个容器定义的迭代器外，标准库还在`<iterator>`头文件中定义了几种其他迭代器：
    * **插入迭代器 (Insert iterators)**：这些迭代器绑定到一个**容器**，可用于向容器插入元素。
    * **流迭代器 (Stream iterators)**：这些迭代器绑定到**输入或输出流**，可用于遍历相关联的IO流
    * **反向迭代器 (Reverse iterators)**：这些迭代器向后移动，而不是向前，除了`forward_list`，库容器都有反向迭代器
    * **移动迭代器 (Move iterators)**：这些特殊用途的迭代器**移动**而不是复制它们的元素
* 他们共同支持的操作包括:

    * **插入迭代器**里，`it = t` 的真正作用是**把 `t` 插入到容器中**（等价于 `push_back / push_front / insert`）
    * 而 `*it`、`++it`、`it++` **只是为了满足迭代器接口，什么也不做**，都会原样返回 `it`


---
<a id="id2"></a>
## ✅ 知识点2: 插入迭代器

**理论**
* **插入器 (inserter)** 是一个**迭代器适配器 (iterator adaptor)**，它接受一个容器并生成一个能向指定容器添加元素的迭代器
* 通过插入迭代器赋值时，迭代器会调用容器操作在给定容器的指定位置添加一个元素。
* 有三种插入器，区别在于元素插入的位置：
    1. `back_inserter`：创建一个使用`push_back`的迭代器
    2. `front_inserter`：创建一个使用`push_front`的迭代器
    3. `inserter`：创建一个使用`insert`的迭代器
        * 此函数接受第二个参数，该参数必须是**给定容器中的一个迭代器**
        * 元素插入到给定迭代器所表示的**元素之前**
* 由`inserter`生成的迭代器，在成功使用时，会在最初由迭代器`iter`表示的元素之前插入元素,赋值`*it = val;`的行为类似于：
    ```cpp
    it = c.insert(it, val); // it指向新添加的元素
    ++it; // 递增it使其表示与之前相同的元素
    ```
* 由`front_inserter`生成的迭代器与由`inserter`生成的迭代器行为大不相同
    * 使用`front_inserter`时，元素**总是**插入到容器当时的第一个元素之前
    * 即使我们传递给`inserter`的位置最初表示第一个元素, 一旦我们在该元素之前插入一个元素，该元素就不再是容器的开头元素了
    * 调用`front_inserter(c)`会得到一个依次调用`push_front`的插入迭代器
        * 每个元素被插入时，都成为`c`中新的第一个元素
        * `front_inserter`产生的迭代器会反转它所插入的序列的顺序
        * `inserter`和`back_inserter`则不会

**教材示例代码**
```cpp
list<int> lst = {1,2,3,4};
list<int> lst2, lst3; // 空列表
// copy完成后，lst2包含 4 3 2 1
copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
// copy完成后，lst3包含 1 2 3 4
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
```

**注意点**
* ⚠️ `front_inserter`和`back_inserter`的使用依赖于容器是否支持相应的`push_front`或`push_back`操作
    * 只有容器有`push_front`时才能使用`front_inserter`
    * 只有容器有`push_back`时才能使用`back_inserter`
* ⚠️ `front_inserter`会反转插入序列的顺序
---
<a id="id12"></a>
## ✅ 知识点3: 流迭代器操作总览

**理论**
* 尽管`iostream`不是容器，但**流迭代器**将对应流当作序列，同样可以使用泛型算法读写


* `istream_iterator<T>`（输入迭代器）：

    **作用：从输入流“读数据”**

    * `istream_iterator<T> in(is);`
    👉 绑定到输入流 `is`，每次迭代都会**从流中读一个 `T`**

    * `istream_iterator<T> end;`
    👉 **流尾迭代器（EOF）**

    * `in1 == in2 / in1 != in2`
    👉 相等条件：

    * 都是 end，或
    * 绑定到同一个输入流

    * `*in`
    👉 返回**当前从流中读到的值**

    * `++in / in++`
    👉 **真正触发读取下一个值**（用 `>>` 运算符）

    📌 **重点一句话**：

    > `istream_iterator` 是“**边走边读**”，`++` 才会从流里再读一次


* `ostream_iterator<T>`（输出迭代器）：

    **作用：向输出流“写数据”**

    * `ostream_iterator<T> out(os);`
    👉 绑定到输出流 `os`

    * `ostream_iterator<T> out(os, d);`
    👉 每次输出后**自动追加分隔符 `d`**

    * `out = val`
    👉 **真正执行输出**：`os << val`

    * `*out`、`++out`、`out++`
    👉 **存在但什么都不做**（只为满足迭代器接口）

    📌 **重点一句话**：

    > `ostream_iterator` 是“**赋值即输出**”，不维护位置概念。


---
<a id="id3"></a>
## ✅ 知识点4: 流迭代器-输入流迭代器

**理论**

* `istream_iterator`读取一个输入流
    * 它使用`>>`来读取流，因此`istream_iterator`要读取的类型必须定义了输入运算符
* 创建一个`istream_iterator`时:
    * 一定要指定迭代器读写的**对象类型**
    * 可以将其绑定到一个流
    * 也可以默认初始化迭代器，这将创建一个可用作**尾后值** (off-the-end value) 的迭代器
* 可以使用`istream_iterator`将标准输入读入`vector`通过迭代器构造函数

**教材示例代码**
```cpp
istream_iterator<int> in_iter(cin);  // 从cin读取int
istream_iterator<int> eof; // int的尾后迭代器
while (in_iter != eof) // 读入数据到vector
    vec.push_back(*in_iter++);

//我们还可以写出另一种相同功能的代码

ifstream in("afile");
istream_iterator<string> str_it(in); // 从"afile"读取strings
```

---
<a id="id4"></a>
## ✅ 知识点4: 流迭代器-输出流迭代器

**理论**
* `ostream_iterator`必须绑定到一个特定的流
    * 没有空的或尾后的`ostream_iterator`
* 创建`ostream_iterator`时，可以（可选地）提供第二个参数，指定在每个元素后打印的C风格字符串（字符串字面值或以空字符结尾的数组的指针）
* **可以省略**解引用和递增操作，写成`out_iter = e;`
    * `*`和`++`运算符对`ostream_iterator`**没有**实际作用，省略它们对程序没有影响
    * 但更倾向于使用第一种写法，以保持与其他迭代器类型用法的一致性，并且代码行为对读者更清晰
* 相比于自己写循环，可以更简单地**调用`copy`来打印`vec`中**的元素：
    ```cpp
    copy(vec.begin(), vec.end(), out_iter);
    cout << endl;
    ```

**教材示例代码**
```cpp
ostream_iterator<int> out_iter(cout, " ");
for (auto e : vec)
    *out_iter++ = e; // 赋值操作将此元素写入cout
cout << endl;
```


---
<a id="id5"></a>
## ✅ 知识点5: 流迭代器与算法

**理论**
* 由于算法根据迭代器操作来工作，而流迭代器至少支持一些迭代器操作，因此我们可以将流迭代器与至少一些算法一起使用。

**教材示例代码**
```cpp
istream_iterator<int> in(cin), eof;
cout << accumulate(in, eof, 0) << endl;
```
* 此调用将生成从标准输入读取的值的总和。

---
<a id="id6"></a>
## ✅ 知识点6: 流迭代器允许延迟求值

**理论**
* 当我们将一个`istream_iterator`绑定到一个流时，并不能保证它会立即读取流。实现允许延迟读取 (delay reading) 流，直到我们使用该迭代器。可以保证的是，在我们第一次解引用迭代器之前，流已经被读取。
* 对于大多数程序，读取是立即执行还是延迟执行没有区别。但是，如果我们创建了一个`istream_iterator`但销毁前未使用它，或者我们正在同步来自两个不同对象的对同一流的读取，那么我们可能会非常关心读取何时发生。

---
<a id="id7"></a>
## ✅ 知识点7: 流迭代器与类类型

**理论**
* 我们可以为任何有输入运算符（`>>`）的类型创建`istream_iterator`。类似地，只要类型有输出运算符（`<<`），我们就可以定义`ostream_iterator`。
* 因为`Sales_item`同时具有输入和输出运算符，所以我们可以使用IO迭代器来重写书店程序。

**教材示例代码**
```cpp
istream_iterator<Sales_item> item_iter(cin), eof;
ostream_iterator<Sales_item> out_iter(cout, "\n");
// 将第一笔交易存入sum并读取下一条记录
Sales_item sum = *item_iter++;
while (item_iter != eof) {
    // 如果当前交易（存储在item_iter中）有相同的ISBN
    if (item_iter->isbn() == sum.isbn())
        sum += *item_iter++; // 将其加到sum并读取下一笔交易
    else {
        out_iter = sum; // 输出当前的sum
        sum = *item_iter++; // 读取下一笔交易
    }
}
out_iter = sum; // 记得打印最后一组记录
```
* 这个程序使用`item_iter`从`cin`读取`Sales_item`交易。它使用`out_iter`将结果总和写入`cout`，每个输出后跟一个换行符。

---
<a id="id8"></a>
## ✅ 知识点8: 反向迭代器

**理论**
* **反向迭代器 (reverse iterator)** 是一种反向遍历容器的迭代器，从最后一个元素向第一个元素移动。
* 反向迭代器颠倒了递增（和递减）的含义。递增（`++`）一个反向迭代器会将迭代器移动到前一个元素；递减（`--`）会将其移动到下一个元素。
* 除了`forward_list`，所有容器都有反向迭代器。通过调用`rbegin`、`rend`、`crbegin`和`crend`成员来获取反向迭代器。这些成员返回指向容器中最后一个元素和“首前”（即开头之前一个）元素的迭代器。与普通迭代器一样，有`const`和`nonconst`反向迭代器。

---
<a id="id9"></a>
## ✅ 知识点9: 反向迭代器的要求与限制

**理论**
* 只能从支持`--`以及`++`的迭代器定义反向迭代器。毕竟，反向迭代器的目的是让迭代器在序列中向后移动。
* 除了`forward_list`，标准容器上的迭代器都支持递减和递增。但是，流迭代器不支持，因为无法在流中向后移动。因此，无法从`forward_list`或流迭代器创建反向迭代器。

---
<a id="id10"></a>
## ✅ 知识点10: 反向迭代器与普通迭代器的关系

**理论**
* 当使用反向迭代器处理字符串（或其他序列）时，如果想将反向迭代器转换回普通迭代器以便正向处理，需要调用反向迭代器的`base()`成员，该成员返回其对应的普通迭代器。
* 反向迭代器和它通过`base()`得到的普通迭代器指向的是不同的元素（相邻位置）。这是为了确保无论是正向处理还是反向处理，元素的范围是相同的。
* 技术上来说，普通迭代器和反向迭代器之间的关系适应了**左闭合区间 (left-inclusive range)** 的特性。`[line.crbegin(), rcomma)`和`[rcomma.base(), line.cend())`指的是`line`中相同的元素。为了实现这一点，`rcomma`和`rcomma.base()`必须产生相邻的位置，而不是相同的位置，`crbegin()`和`cend()`也必须如此。
* 注意：反向迭代器旨在表示范围，且这些范围是不对称的，这导致一个重要后果：当我们从普通迭代器初始化或赋值一个反向迭代器时，得到的迭代器并不指向与原始迭代器相同的元素。

**教材示例代码**
```cpp
// 查找逗号分隔列表中的第一个元素
auto comma = find(line.cbegin(), line.cend(), ',');
cout << string(line.cbegin(), comma) << endl;

// 查找逗号分隔列表中的最后一个元素，使用反向迭代器
auto rcomma = find(line.crbegin(), line.crend(), ',');

// 错误：会以逆序生成单词
// cout << string(line.crbegin(), rcomma) << endl;

// 正确：获取一个正向迭代器并读取到行尾
cout << string(rcomma.base(), line.cend()) << endl;
```

---
<a id="id11"></a>
## ✅ 知识点11: 反向迭代器示例

**教材示例代码**
```cpp
// 示例1：反向打印vector
vector<int> vec = {0,1,2,3,4,5,6,7,8,9};
for (auto r_iter = vec.crbegin(); // 将r_iter绑定到最后一个元素
     r_iter != vec.crend(); // crend指向首前元素
     ++r_iter) // 递减迭代器一个元素
    cout << *r_iter << endl; // 打印 9,8,7,...0

// 示例2：使用反向迭代器进行降序排序
sort(vec.begin(), vec.end()); // 以“正常”顺序排序vec
sort(vec.rbegin(), vec.rend()); // 以降序排序，最小的元素在vec的末尾
```

---

## 🔑 核心要点总结
1.  **迭代器类型扩展**：除了容器迭代器，标准库还提供了插入迭代器、流迭代器、反向迭代器等特殊迭代器，极大地增强了泛型编程的能力。
2.  **插入迭代器的行为差异**：`back_inserter`使用`push_back`，`front_inserter`使用`push_front`（会反转顺序），`inserter`使用`insert`在指定位置前插入。
3.  **流迭代器连接算法与IO**：`istream_iterator`和`ostream_iterator`允许将输入/输出流视为元素序列，从而可以直接与泛型算法（如`copy`、`accumulate`）配合使用，简化代码。
4.  **反向迭代器的逻辑反转**：反向迭代器通过反转递增/递减操作的语义来实现从容器的尾部向首部遍历。它与普通迭代器的位置关系是相邻而非相同，转换需要使用`base()`成员。
5.  **使用限制**：创建反向迭代器要求底层迭代器支持递减操作，因此不能从`forward_list`迭代器或流迭代器创建反向迭代器。

## 📌 考试速记版
*   **插入迭代器 (Insert Iterators)**：`back_inserter`（尾插）、`front_inserter`（头插，会反序）、`inserter`（指定位置前插）。
*   **流迭代器 (Stream Iterators)**：`istream_iterator<T>`（绑定输入流，`>>`）、`ostream_iterator<T>`（绑定输出流，`<<`，可附加分隔符）。
*   **反向迭代器 (Reverse Iterators)**：`rbegin`/`rend`，递增即向后。与普通迭代器关系：`reverse_iterator.base()`指向相邻下一元素。
*   **重要限制**：`front_inserter`需容器有`push_front`；反向迭代器不能用于`forward_list`和流。
*   **常用模式**：用`copy`搭配流迭代器进行IO；用反向迭代器进行反向遍历或降序排序。

**口诀**：插流反向各有用，插入注意前后中，流连算法好轻松，反向递增逻辑反，转换base要记清。