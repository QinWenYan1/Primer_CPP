# 3.11

（题意：`const string s = "Keep out!"; for (auto &c : s) /* ... */`）
**合法**。`c` 的类型是 **`const char&`**；因为 `s` 是 `const string`，通过引用迭代到的元素也为常量引用，因此循环体内不能修改 `c`。
