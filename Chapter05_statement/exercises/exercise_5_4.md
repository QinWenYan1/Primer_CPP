# 📘 练习 5.4 解答

## 问题分析

### (a) `while (string::iterator iter != s.end()) { /* ... */ }`

**问题**：
1. 语法错误：在 `while` 条件中声明变量时，应该使用赋值语法而不是比较语法
2. 变量 `iter` 未正确初始化

**修正方案**：
```cpp
std::string::iterator iter = s.begin();
while (iter != s.end()) { /* ... */ }
```

**解释**：
- 在 `while` 条件中声明变量时，正确的语法是 `while (type var = value)`
- 但这里我们实际上需要的是一个迭代器与结束位置的比较，所以应该在循环外部定义并初始化迭代器

### (b) `while (bool status = find(word)) { /* ... */ } if (!status) { /* ... */ }`

**问题**：
1. 变量 `status` 的作用域仅限于 `while` 循环内部
2. 在 `if` 语句中尝试使用 `status` 时，它已经超出作用域

**修正方案**：
```cpp
bool status;
while (status = find(word)) { /* ... */ }
if (!status) { /* ... */ }
```

**解释**：
- 将 `status` 的定义移到 `while` 循环外部，使其在循环结束后仍然可用
- 注意这里使用的是赋值操作 `=` 而不是比较操作 `==`

## 完整修正代码

```cpp
// (a) 修正后的代码
std::string::iterator iter = s.begin();
while (iter != s.end()) {
    // 循环体
    ++iter;
}

// (b) 修正后的代码
bool status;
while (status = find(word)) {
    // 循环体
}
if (!status) {
    // 处理 status 为 false 的情况
}
```

## 关键知识点总结

1. **变量作用域**：在控制结构（如 `while`）中定义的变量只在该结构内部可见
2. **变量初始化**：在条件中声明变量时必须进行初始化
3. **赋值与比较**：注意区分赋值操作 `=` 和比较操作 `==`
4. **变量生命周期**：需要确保变量在其使用范围内始终有效

您的答案基本正确，只是需要注意在 (b) 部分中，修正后的代码应该使用赋值操作 `=` 而不是比较操作 `==`，因为我们需要将 `find(word)` 的结果赋值给 `status` 并检查其布尔值。