# 📊 练习批改与分析

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 8.11 | ⭐⭐⭐⭐ 4/5 | 基本正确，但遗漏了重要细节 |
| Exercise 8.12 | ⭐⭐⭐⭐⭐ 5/5 | 完美答案，概念理解深入 |

## 🎯 逐题详细评价

### Exercise 8.11 移动istringstream定义

**原题：** The program in this section defined its istringstream object inside the outer while loop. What changes would you need to make if record were defined outside that loop? Rewrite the program, moving the definition of record outside the while, and see whether you thought of all the changes that are needed.

**你的答案：**
```cpp
vector<PersonInfo> people; 
istringstream record; 
while (getline(cin, line)) {
    PersonInfo info; 
    record.str(line); 
    record >> info.name; 
    while (record >> word) 
        info.phones.push_back(word); 
    people.push_back(info); 
}
```

**批改结果：** ⭐⭐⭐⭐ 4/5
- **概念理解：** ✅ 理解了需要将istringstream移到循环外并使用str()方法
- **代码质量：** ⚠️ 基本正确，但缺少必要的状态重置
- **逻辑完整：** ⚠️ 遗漏了流状态清除的重要步骤
- **表达清晰：** ✅ 代码结构清晰

**正确答案：**
```cpp
vector<PersonInfo> people;
istringstream record;  // 定义在循环外
string line, word;

while (getline(cin, line)) {
    PersonInfo info;
    record.clear();    // 重要：清除流的错误状态
    record.str(line);  // 绑定到新字符串
    record >> info.name;
    while (record >> word)
        info.phones.push_back(word);
    people.push_back(info);
}
```

**知识点解析：**
- **流状态管理**：当istringstream读取到文件末尾或遇到错误时，会设置eofbit或failbit，需要调用clear()重置状态
- **字符串绑定**：str()方法用于将字符串绑定到stringstream，但不会自动清除之前的流状态
- **作用域考虑**：将record移到循环外避免了重复构造的开销，但需要手动管理状态

**改进建议：**
- 在每次循环迭代开始时调用`record.clear()`来重置流状态
- 添加必要的变量声明（line和word）
- 理解流状态标志的重要性

### Exercise 8.12 类内初始化器

**原题：** Why didn't we use in-class initializers in PersonInfo?

```cpp
struct PersonInfo {
    string name;
    vector<string> phones;
};
```

**你的答案：** 因为string对象，以及vector<string>有自己的默认构造函数，因此PersonInfo类在不提供构造函数的情况下，也就能根据成员的默认构造函数合成自己的默认构造函数

**批改结果：** ⭐⭐⭐⭐⭐ 5/5
- **概念理解：** ✅ 准确理解了默认构造函数合成机制
- **代码质量：** ✅ 概念解释清晰准确
- **逻辑完整：** ✅ 完整解释了不使用类内初始化的原因
- **表达清晰：** ✅ 表述专业且易于理解

**正确答案：**
你的答案完全正确！标准库类型`string`和`vector<string>`都有默认构造函数，它们会：
- `string`默认构造为空字符串
- `vector<string>`默认构造为空向量

因此`PersonInfo`可以通过合成的默认构造函数正确初始化所有成员。

**知识点解析：**
- **合成默认构造函数**：当类没有定义任何构造函数时，编译器会自动生成默认构造函数
- **成员初始化**：合成默认构造函数会调用成员的默认构造函数
- **类内初始化**：主要用于内置类型或需要特殊初始值的场景

