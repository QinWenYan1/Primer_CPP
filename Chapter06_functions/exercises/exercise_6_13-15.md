### Exercise 6.13 - 类型差异分析

**修正后的回答：**
```cpp
void f(T)   // 传值：创建实参的副本，函数内修改不影响原始对象
void f(T&)  // 传引用：形参是实参的别名，函数内修改直接影响原始对象
```

**具体区别：**
- `f(T)`：适合小型、不需要修改的对象
- `f(T&)`：适合大型对象或需要修改实参的场景

### Exercise 6.14 - 引用参数应用场景

**你的回答很好，补充一些具体例子：**

**应该使用引用的情况：**
```cpp
// 1. 修改外部变量
void increment(int &x) { x++; }

// 2. 避免大型对象拷贝
void processLargeData(const vector<Data> &data) { /* 只读操作 */ }

// 3. 需要返回多个值
bool parseInput(const string &input, int &result, string &errorMsg);
```

**不应该使用引用的情况：**
```cpp
// 1. 内置类型的小型计算（传值更高效）
int factorial(int n) { return n <= 1 ? 1 : n * factorial(n-1); }

// 2. 需要独立副本的操作
vector<int> sortedCopy(vector<int> data) {  // 传值获得副本
    sort(data.begin(), data.end());
    return data;
}
```

### Exercise 6.15 - find_char参数设计分析

**你的分析基本正确，补充更详细的解释：**

```cpp
string::size_type find_char(const string &s, char c, string::size_type &occurs)
```

**参数设计原理：**

1. **`const string &s`**：
   - **为什么const引用**：避免字符串拷贝，同时保证不修改原字符串
   - **如果改为普通引用**：无法接受字面量(`"hello"`)、const字符串等，限制函数使用范围

2. **`char c`**：
   - **为什么传值**：char是基本类型，拷贝开销极小；c在函数内是临时值，不需要影响外部
   - **如果改为引用**：增加复杂性，没有实际收益

3. **`string::size_type &occurs`**：
   - **为什么普通引用**：需要修改外部变量来返回出现次数
   - **如果改为const引用**：编译错误，无法修改出现次数

**更深入的设计考虑：**
```cpp
// 错误设计：限制了调用方式
string::size_type bad_find_char(string &s, char c, const size_t &occurs);

// 正确设计：灵活且安全
string::size_type good_find_char(const string &s, char c, size_t &occurs);
```

## 📝 改进建议

1. **代码风格**：减少不必要的输出语句，专注于核心逻辑
2. **术语准确**：使用更专业的表述，如"形参/实参"而非"形式参/实参对象"
3. **示例具体化**：提供更贴近实际应用的例子

你的理解和代码实现都很不错，继续保持！🎯