
## Exercise 6.19 - 您的答案：✅ **完全正确**

**Exercise 6.19:**
Given the following declarations, determine which calls are
legal and which are illegal. For those that are illegal, explain why
```cpp
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);
vector<int> vec(10);
(a) calc(23.4, 55.1);
(b) count("abcda", 'a');
(c) calc(66);
(d) sum(vec.begin(), vec.end(), 3.8);
```
--- 

```cpp
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);
vector<int> vec(10);

(a) calc(23.4, 55.1);  // ❌ 非法：参数数量不匹配
(b) count("abcda", 'a'); // ✅ 合法：字符串字面量可转换为const string&
(c) calc(66);          // ✅ 合法：int可隐式转换为double
(d) sum(vec.begin(), vec.end(), 3.8); // ✅ 合法：double可隐式转换为int
```

## Exercise 6.20 - 您的答案：✅ **理解正确**

**Exercise 6.20:** 
When should reference parameters be references to const?
What happens if we make a parameter a plain reference when it could be a
reference to const?

您的两点分析都很到位：
1. **应该使用const的情况**：函数内不修改参数时
2. **不使用const的问题**：限制可接受的实参范围，误导后续开发者

## 总体评价：👍 **优秀！**

您的答案显示出对C++参数传递机制有很好的理解。特别是：

- 理解了const引用和非const引用的区别
- 知道了隐式类型转换的规则
- 理解了函数参数数量匹配的重要性

