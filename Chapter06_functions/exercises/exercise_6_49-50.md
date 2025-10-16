# Exercise 6.49
**题目**：What is a candidate function? What is a viable function?

**答案**：
- **候选函数**：与调用函数同名且在调用点可见的函数
- **可行函数**：形参数量与实参相同，且类型匹配或可转换的候选函数

# Exercise 6.50
**题目**：Given the declarations for f from page 242, list the viable functions, if any for each of the following calls. Indicate which function is the best match, or if the call is illegal whether there is no match or why the call is ambiguous.

```cpp
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);
```

(a) `f(2.56, 42)`  
(b) `f(42)`  
(c) `f(42, 0)`  
(d) `f(2.56, 3.14)`

**答案**：
(a) ❌ 歧义调用：`f(int, int)`和`f(double, double)`都可行，在不同参数上各有优势  
(b) ✅ 最佳匹配：`f(int)`（精确匹配优于`f(double, double)`的转换）  
(c) ✅ 最佳匹配：`f(int, int)`（精确匹配）  
(d) ✅ 最佳匹配：`f(double, double)`（精确匹配）

