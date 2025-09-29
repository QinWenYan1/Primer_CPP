Exercise 6.24: Explain the behavior of the following function. If there are problems in the code, explain what they are and how you might fix them. 
```cpp
void print(const int ia[10]) { 

    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl; 

}
```
## 📌 逐点分析

1. **函数声明解析**

   ```cpp
   void print(const int ia[10]);
   ```

   * 这里的 `ia[10]` **会退化为 `const int*`**，维度信息 `10` 完全被丢弃。
   * 所以函数实际上接收的只是一个指针，无法检查传入数组的长度。

2. **代码潜在问题**

   ```cpp
   for (size_t i = 0; i != 10; ++i)
       cout << ia[i] << endl;
   ```

   * 因为函数不能保证传进来的数组长度确实是 10，如果传入一个小于 10 的数组，就会**越界访问（UB）**。

3. **修正方式**

   * 最安全的做法是把数组大小也作为参数传入，或者传递首尾指针：

     ```cpp
     void print(const int* ia, size_t size) {
         for (size_t i = 0; i != size; ++i)
             cout << ia[i] << endl;
     }
     ```
   * 或用引用数组形参保留维度信息，强制编译期检查：

     ```cpp
     void print(const int (&ia)[10]) { /* ... */ }
     ```

---

## ✅ 改进后的标准回答

> **解析**：`ia[10]` 在形参中会退化为指针，编译器不会检查传入数组的大小是否为 10。
> **问题**：使用固定的 `10` 作为循环上界存在潜在越界风险，如果实参数组长度不足 10 会导致未定义行为。
> **改进**：显式传递数组大小，或使用 `const int (&ia)[10]` 保留维度信息以在编译期强制检查。

---

✅ 这样回答既指出了“维度信息无效”的根本原因，又给出安全的修正方案，比单纯说“可能 overflow”更完整、专业。

