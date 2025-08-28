### 4.8

**Q:** Explain when operands are evaluated in the logical AND, logical OR, and equality operators.
**A:**

* `&&`：**先算左侧**；只有当左侧为 `true` 时才计算右侧（短路）。
* `||`：**先算左侧**；只有当左侧为 `false` 时才计算右侧（短路）。
* `==` / `!=`：两侧**都要计算**；**求值顺序未规定**（没有短路，左右顺序不保证）。

---

### 4.9

**Q:** Explain the behavior of:

```cpp
const char *cp = "Hello World";
if (cp && *cp)  /* ... */
```

**A:**

* 先判断 `cp` 是否为非空指针。若 `cp == nullptr`，右侧不求值（短路），整体为 `false`。
* 若 `cp` 非空，再判断 `*cp`（首字符）。非 `'\0'` 为 `true`；若字符串为空（首字符 `'\0'`），为 `false`。
* 对于 `"Hello World"`：`cp` 非空、`*cp == 'H'` 非零 → 条件为 `true`。

---