# Exercise 5.13 解答分析

您对练习 5.13 的分析基本正确，但有一些细节需要补充和修正。让我为您提供更完整的解答：

## a. 代码段分析

**原始代码：**
```cpp
unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
char ch = next_text();
switch (ch) {
    case 'a': aCnt++;
    case 'e': eCnt++;
    default: iouCnt++;
}
```

**问题：** 确实缺少 `break` 语句，会导致"贯穿"（fall-through）行为。

**修正：**
```cpp
unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
char ch = next_text();
switch (ch) {
    case 'a': 
        aCnt++;
        break;
    case 'e': 
        eCnt++;
        break;
    default: 
        iouCnt++;
        break;
}
```

## b. 代码段分析

**原始代码：**
```cpp
unsigned index = some_value();
switch (index) {
    case 1:
        int ix = get_value();
        ivec[ ix ] = index;
        break;
    default:
        ix = ivec.size()-1;
        ivec[ ix ] = index;
}
```

**问题：** 您提到了越界问题，但主要问题是**变量作用域问题**。在 `case 1` 中定义的变量 `ix` 在 `default` 分支中不可见。

**修正：**
```cpp
unsigned index = some_value();
int ix; // 在 switch 外部定义变量
switch (index) {
    case 1:
        ix = get_value();
        ivec[ ix ] = index;
        break;
    default:
        ix = ivec.size()-1;
        ivec[ ix ] = index;
}
```

## c. 代码段分析

**原始代码：**
```cpp
unsigned evenCnt = 0, oddCnt = 0;
int digit = get_num() % 10;
switch (digit) {
    case 1, 3, 5, 7, 9:
        oddcnt++;
        break;
    case 2, 4, 6, 8, 10:
        evencnt++;
        break;
}
```

**问题：** 您分析得很准确。有两个主要问题：
1. C++ 的 `case` 标签不能使用逗号分隔多个值
2. `get_num() % 10` 的结果范围是 0-9，永远不会等于 10

**修正：**
```cpp
unsigned evenCnt = 0, oddCnt = 0;
int digit = get_num() % 10;
switch (digit) {
    case 1: case 3: case 5: case 7: case 9:
        oddCnt++; // 注意变量名大小写
        break;
    case 0: case 2: case 4: case 6: case 8:
        evenCnt++; // 注意变量名大小写
        break;
}
```

## d. 代码段分析

**原始代码：**
```cpp
unsigned ival=512, jval=1024, kval=4096;
unsigned bufsize;
unsigned swt = get_bufCnt();
switch(swt) {
    case ival:
        bufsize = ival * sizeof(int);
        break;
    case jval:
        bufsize = jval * sizeof(int);
        break;
    case kval:
        bufsize = kval * sizeof(int);
        break;
}
```

**问题：** 您提到了缺少 `default` 情况，但主要问题是 **`case` 标签必须是常量表达式**。`ival`, `jval`, `kval` 是变量，不能用作 `case` 标签。

**修正：**
```cpp
constexpr unsigned ival=512, jval=1024, kval=4096; // 使用 constexpr 使其成为常量表达式
unsigned bufsize;
unsigned swt = get_bufCnt();
switch(swt) {
    case ival:
        bufsize = ival * sizeof(int);
        break;
    case jval:
        bufsize = jval * sizeof(int);
        break;
    case kval:
        bufsize = kval * sizeof(int);
        break;
    default:
        // 处理其他情况
        break;
}
```

或者，如果这些值不是常量，应该使用 `if-else` 语句而不是 `switch`：

```cpp
unsigned ival=512, jval=1024, kval=4096;
unsigned bufsize;
unsigned swt = get_bufCnt();

if (swt == ival) {
    bufsize = ival * sizeof(int);
} else if (swt == jval) {
    bufsize = jval * sizeof(int);
} else if (swt == kval) {
    bufsize = kval * sizeof(int);
} else {
    // 处理其他情况
}
```

## 总结

您的分析基本正确，但需要注意：

1. **`case` 标签必须是常量表达式**：这是 C++ 语言的硬性规定
2. **变量作用域**：在 `switch` 语句中定义的变量有其特定的作用域规则
3. **`case` 语法**：多个 `case` 标签应该分别列出，不能用逗号分隔
4. **`default` 分支**：虽然不是强制要求，但包含 `default` 分支是一个好习惯

这些练习帮助您深入理解了 `switch` 语句的常见陷阱和正确用法。