## Exercise 6.39: 
Explain the effect of the second declaration in each one of
the following sets of declarations. Indicate which, if any, are illegal.
(a) 
```cpp
int calc(int, int);
int calc(const int, const int);
```
(b) 
```cpp
int get();
double get();
```
(c) 
```cpp
int *reset(int *);
double *reset(double *);
```

## ✅ 正确的地方：
- **(b)** 判断完全正确，返回类型不同不能构成重载
- **(c)** 判断正确，参数类型不同可以重载

## ❌ 需要修正的地方：

### **(a) 的问题：**
你的判断"会报错"不完全准确。

**正确理解：**
```cpp
int calc(int, int);
int calc(const int, const int);  // 合法但无意义
```
- 这是**合法的声明**，不会报错
- 但由于顶层const被忽略，这两个声明实际上指向**同一个函数**
- 编译器会接受这个声明，但第二个const会被忽略

### 改进后的答案：

**(a)** 第二个声明是合法的，但由于顶层const在函数参数中被忽略，这两个声明实际上表示同一个函数。不会产生重载效果。

**(b)** 第二个声明是非法的，因为仅返回类型不同不能构成函数重载。

**(c)** 第二个声明是合法的重载，因为参数类型不同（int* vs double*），这确实允许reset函数处理更多类型的指针参数。

## 💡 额外建议：

在回答时可以考虑：
- 明确区分"编译错误" vs "合法但无意义"
- 说明每个case的具体规则依据
- 用更专业的术语："顶层const被忽略"、"函数签名不包括返回类型"

你的理解基本正确，主要是(a)的情况需要更精确的描述！