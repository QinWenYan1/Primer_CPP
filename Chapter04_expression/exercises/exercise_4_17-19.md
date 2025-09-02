# 📘 Exercises 4.5 Increment and Decrement Operators

---

## ✅ Exercise 4.17

**题目：**
Explain the difference between prefix and postfix increment.

**答案：**

* **前置自增 (++i)**
  *接受左值 → 修改变量 → 返回修改后的变量本身（仍是左值）。*

  ```cpp
  int i = 0;
  int j = ++i;  // i=1, j=1
  ```
* **后置自增 (i++)**
  *接受左值 → 保存原始副本 → 修改变量 → 返回副本（右值）。*

  ```cpp
  int i = 0;
  int j = i++;  // i=1, j=0
  ```

⚠️ **注意：** 前置效率更高（不用保存副本），所以推荐使用前置。

---

## ✅ Exercise 4.18

**题目：**
What would happen if the while loop on page 148 that prints the elements from a vector used the prefix increment operator?

**原代码（教材后置++ 版本）：**

```cpp
auto pbeg = v.begin();
// print elements up to the first negative value
while (pbeg != v.end() && *pbeg >= 0)
    cout << *pbeg++ << endl;  // 输出当前值，再移动迭代器
```

**若改为前置++：**

```cpp
while (pbeg != v.end() && *pbeg >= 0)
    cout << *++pbeg << endl;  // 先移动，再解引用
```

**结果：**

* 第一个元素不会被输出（因为先 ++ 再解引用）。
* 当迭代器到达 `end()` 前一步时，`++pbeg` 会移到 `end()`，再解引用就会越界 → **未定义行为**。

---

## ✅ Exercise 4.19

**题目：**
Given that `ptr` points to an `int`, that `vec` is a `vector<int>`, and that `ival` is an `int`, explain the behavior of each of these expressions. Which, if any, are likely to be incorrect? Why? How might each be corrected?

### (a) `ptr != 0 && *ptr++`

* **解释：**

  * 首先检查 `ptr != 0`（短路保证先计算左边）。
  * 如果 `ptr != 0` 为真，则执行 `*ptr++`：解引用 `ptr`，再让 `ptr` 指向下一个元素。
* **合法，不是 UB**，因为 `&&` 保证了顺序。
* **更清晰写法：**

  ```cpp
  (ptr != 0) && (*ptr != 0);
  ```

---

### (b) `ival++ && ival`

* **解释：**

  * 左边 `ival++`：返回旧值副本（右值），并修改 `ival`。
  * 如果旧值为 0，则右边不计算。
  * 如果旧值非 0，则右边再取修改后的 `ival`。
* **合法，不是 UB**，因为 `&&` 保证了左边先算，右边后算。
* **但语义晦涩 → 推荐写成：**

  ```cpp
  (ival != 0) && (++ival != 0);
  ```

---

### (c) `vec[ival++] <= vec[ival]`

* **解释：**

  * 左边 `vec[ival++]` 修改了 `ival`，右边又在同一表达式读取了 `ival`。
  * 两边的求值顺序没有规定 → **未定义行为 (UB)**。
* **改正：**

  ```cpp
  vec[ival] <= vec[ival+1];  // 或者拆成两行
  ```

---

## 🔑 总结

* `&&` / `||` / `,` / `?:` 有明确求值顺序 → 修改 + 读取是安全的。
* 其他运算符没有顺序保证 → 修改 + 读取 = **UB**。
* 推荐写法应尽量**简洁清晰**，避免副作用和求值顺序的陷阱。

