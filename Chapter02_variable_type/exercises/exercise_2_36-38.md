

### ✅ **Exercise 2.36**

```cpp
int a = 3, b = 4;
decltype(a) c = a;     // c 的类型是 int
decltype((b)) d = a;   // d 的类型是 int&，因为 (b) 是一个左值表达式
++c;                   // c = 4
++d;                   // a = 4，因为 d 是 a 的引用
```

**类型总结：**

* `c`: `int`
* `d`: `int&`

**值总结（程序结束后）：**

* `a = 4`
* `b = 4`
* `c = 4`
* `d = a`（值为 4）

---

### ✅ **Exercise 2.37**

```cpp
int a = 3, b = 4;
decltype(a) c = a;          // c 是 int
decltype(a = b) d = a;      // a = b 是左值表达式，decltype 是 int&
```

注意：

* `a = b` 是一个表达式，结果是 `a` 本身，因此是左值，类型是 `int&`
* 所以 `d` 是 `int&`

**类型总结：**

* `c`: `int`
* `d`: `int&`

**值总结（程序结束后）：**

* `a = 3`
* `b = 4`
* `c = 3`
* `d = a`（值为 3）

---

### ✅ **Exercise 2.38**

> Describe the differences in type deduction between `decltype` and `auto`.

#### 📌 区别总结：

```text
1. decltype 推导的类型依赖于表达式的形式（是否是左值、是否加括号等）；
2. auto 会忽略 top-level const 和引用；
3. decltype 保留顶层 const、引用信息；
4. decltype 可以推导出引用类型，auto 通常不会。
```

#### 📎 示例 1：推导相同类型

```cpp
int i = 42;
auto a = i;         // int
decltype(i) b = i;  // int
```

#### 📎 示例 2：推导不同类型

```cpp
int i = 42;
const int &r = i;

auto x = r;         // int，忽略 top-level const 和引用
decltype(r) y = i;  // const int&，保留引用信息
```

---

