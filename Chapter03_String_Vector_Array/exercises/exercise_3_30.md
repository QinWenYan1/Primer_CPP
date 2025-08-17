## Exercise 3.30

**题目**：找出下面代码的“索引错误”。

```cpp
constexpr size_t array_size = 10;
int ia[array_size];
for (size_t ix = 1; ix <= array_size; ++ix)
    ia[ix] = ix;
```

**错误 & 原因**

1. `ix` 从 **1** 开始 → 跳过了 `ia[0]`（未赋值）。
2. 循环条件 `ix <= array_size` → 当 `ix == array_size` 时会写 `ia[array_size]`，**越界**（最后合法索引是 `array_size-1`）。

**修正**（任选其一写法）：

```cpp
for (size_t ix = 0; ix != array_size; ++ix)  // 推荐这种半开区间风格
    ia[ix] = ix;
```

或

```cpp
for (size_t ix = 0; ix < array_size; ++ix)
    ia[ix] = ix;
```

