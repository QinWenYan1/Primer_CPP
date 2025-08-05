# Exercise 2.26 解答

## 题目
Which of the following are legal? For those that are illegal, explain why.

```cpp
(a) const int buf;
(b) int cnt = 0;
(c) const int sz = cnt;
(d) ++cnt; ++sz;
```

---

## 解答分析

### (a) `const int buf;`
**结果：非法 (Illegal)**

**原因：**
- `const` 对象必须在定义时初始化
- 因为 `const` 对象一旦创建后其值就不能再改变，所以必须在声明时提供初始值
- 编译器会报错：`error: uninitialized const 'buf'`

**正确写法：**
```cpp
const int buf = 0;  // 或其他合适的初始值
```

---

### (b) `int cnt = 0;`
**结果：合法 (Legal)**

**原因：**
- 这是一个普通的 `int` 变量定义并初始化为 0
- 非 `const` 变量可以在定义时初始化，也可以不初始化
- 这里选择初始化为 0 是完全合法的

---

### (c) `const int sz = cnt;`
**结果：合法 (Legal)**

**原因：**
- `const` 对象可以用任何表达式初始化，只要该表达式在初始化时有确定的值
- `cnt` 是一个已定义的变量，可以用来初始化 `const` 对象
- 初始化完成后，`sz` 的值就固定不变了
- 注意：虽然 `cnt` 可能会改变，但 `sz` 在初始化后就不会随 `cnt` 的变化而变化

---

### (d) `++cnt; ++sz;`
**结果：部分合法 (Partially Legal)**

**分析：**
- `++cnt;` **合法** - `cnt` 是普通的 `int` 变量，可以修改其值
- `++sz;` **非法** - `sz` 是 `const int`，不能修改其值

**具体说明：**
- 第一个表达式 `++cnt` 是合法的，因为 `cnt` 不是常量
- 第二个表达式 `++sz` 是非法的，因为 `sz` 是 `const` 对象，任何试图修改它的操作都会导致编译错误
- 编译器会报错：`error: increment of read-only variable 'sz'`

---

## 总结

| 选项 | 合法性 | 关键问题 |
|------|--------|----------|
| (a) | 非法 | `const` 对象未初始化 |
| (b) | 合法 | 普通变量正常初始化 |
| (c) | 合法 | `const` 对象正确初始化 |
| (d) | 部分合法 | 只能修改非 `const` 变量 |

**核心规则：**
1. `const` 对象必须初始化
2. `const` 对象初始化后不能修改
3. 可以用非 `const` 变量初始化 `const` 对象