## Exercise 6.34

Exercise 6.34: What would happen if the stopping condition in factorial
were:
`if (val != 0)`

original:

```cpp
// calculate val!, which is 1 * 2 * 3 . . . * val
int factorial(int val)
{
    if (val > 1)
        return factorial(val-1) * val;
    return 1; 
}
``` 

## Exercise 6.34 分析

**原始代码：**
```cpp
int factorial(int val)
{
    if (val > 1)
        return factorial(val-1) * val;
    return 1; 
}
```

**修改后的停止条件：**
```cpp
int factorial(int val)
{
    if (val != 0)          // 修改后的条件
        return factorial(val-1) * val;
    return 1; 
}
```

## 🔍 问题分析

### 对于**非负输入**：
- **val = 0**: `0 != 0` 为 false，直接返回 1 ✅ (0! = 1)
- **val = 1**: `1 != 0` 为 true，递归调用 `factorial(0)`，返回 1 ✅ (1! = 1)
- **val = 5**: 正常计算，结果正确 ✅

### 对于**负输入**：
- **val = -1**: `-1 != 0` 为 true，递归调用 `factorial(-2)`
- **val = -2**: `-2 != 0` 为 true，递归调用 `factorial(-3)`
- **val = -3**: `-3 != 0` 为 true，递归调用 `factorial(-4)`
- **...无限递归...**

## ⚠️ 关键问题

**无限递归**：当输入负数时，条件 `val != 0` 永远为 true，因为：
- 负数永远不等于 0
- 每次递归 `val-1` 让数值越来越小（-1, -2, -3...）
- 永远无法达到终止条件

## 🎯 结论

**原始条件 `val > 1` 更好，因为：**
1. 对非负输入结果相同且正确
2. 对负输入会直接返回 1（虽然数学上不正确，但至少不会崩溃）
3. 避免了潜在的无限递归和栈溢出

**修改后的条件 `val != 0` 的问题：**
- 对负输入导致无限递归 → 栈溢出 → 程序崩溃

**你的回答基本正确，但需要强调负输入导致的无限递归风险！**

## Exercise 6.35

**你的答案分析：**
基本正确，但可以更详细。

**标准答案：**
使用`val--`会先传递当前值，然后再递减，这会导致：
1. 传递的是未递减的值，导致无限递归
2. 即使能终止，结果也是错误的

而`val-1`直接传递递减后的值，是正确的递归方式。

