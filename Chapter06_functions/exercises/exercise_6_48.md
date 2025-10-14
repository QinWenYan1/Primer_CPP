# Exercise 6.48 分析与解答

## 📋 原题目
**Exercise 6.48:** Explain what this loop does and whether it is a good use of assert:

```cpp
string s;
while (cin >> s && s != sought) { } // empty body
assert(cin);
```
## 回答
**循环作用**：不断读取输入，直到找到目标字符串或输入结束。

**assert使用评价**：不合理。输入失败是正常运行时情况，不是程序逻辑错误。assert在发布版本会被禁用，且应检查"绝不应该发生"的情况，而非外部输入状态。应改用显式错误处理。