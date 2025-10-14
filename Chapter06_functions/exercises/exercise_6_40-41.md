# 📘 Exercise 分析与解答

## Exercise 6.40

**题目：** Which, if either, of the following declarations are errors? Why?
```cpp
(a) int ff(int a, int b = 0, int c = 0);
(b) char *init(int ht = 24, int wd, char bckgrnd);
```

### 你的答案：
> a.正确， b. 错误，既然给前面两个形参默认参数， 那么最后一个也应该给， 根据规则， 默认参数的右边不允许出现不带默认参数的形参

### 我的分析：

**✅ 你的判断完全正确！**

**(a) `int ff(int a, int b = 0, int c = 0);`**
- **正确** ✅
- 符合默认参数规则：一旦某个参数有默认值，其后的所有参数都必须有默认值
- 这里`b`和`c`都有默认值，且`a`在最前面没有默认值，这是合法的

**(b) `char *init(int ht = 24, int wd, char bckgrnd);`**
- **错误** ❌
- 违反了默认参数的核心规则
- `ht`有默认值，但紧随其后的`wd`没有默认值
- 正确的做法应该是：
  ```cpp
  char *init(int ht = 24, int wd = 80, char bckgrnd = ' ');
  ```

---

## Exercise 6.41

**题目：** Which, if any, of the following calls are illegal? Why? Which, if any, are legal but unlikely to match the programmer's intent? Why?

```cpp
char *init(int ht, int wd = 80, char bckgrnd = ' ');
```
(a) `init();` 
(b) `init(24,10);`
(c) `init(14, '*');`

### 你的答案：
> a. 非法, 没有默认参数的形参没有初始化  
> b. 合法，  
> c. 合法， 但是不符合作者的意图， 因为初始化给的char只会用于初始化第二个形参数

### 我的分析：

**你的判断基本正确，但(c)的描述需要更精确**

**(a) `init();`**
- **非法** ❌ - **你的判断正确**
- 原因：第一个参数`ht`没有默认值，必须提供
- 必需参数不能省略

**(b) `init(24,10);`**
- **合法** ✅ - **你的判断正确**
- 相当于：`init(24, 10, ' ')`
- `ht=24`, `wd=10`, `bckgrnd`使用默认值`' '`

**(c) `init(14, '*');`**
- **合法但可能不符合意图** ⚠️ - **方向正确但描述需改进**

**更精确的分析：**
- **合法**：语法上正确，因为`'*'`可以**隐式转换**为`int`类型（ASCII值42）
- **不符合意图**：看起来程序员可能想设置`bckgrnd = '*'`，但实际上设置的是`wd = 42`
- **正确调用方式**：如果要设置背景字符，应该调用`init(14, 80, '*')`

