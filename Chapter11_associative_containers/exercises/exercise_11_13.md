## 📊 练习批改与分析

### Exercise 11.13 创建pair的三种方法

**原题：** There are at least three ways to create the pairs in the program for the previous exercise. Write three versions of that program, creating the pairs in each way. Explain which form you think is easiest to write and understand, and why.

**原程序：**
```cpp
string word; 
int count; 
vector<pair<string, int>> vofP; 

while( cin >> word ){
    if (!(cin >> count))  count = 0; 
    vofP.push_back({word, count}); 
}
```

**你的答案：**

第一种：
```cpp
string word; 
int count; 
vector<pair<string, int>> vofP; 

while( cin >> word ){
    if (!(cin >> count))  count = 0; 
    vofP.push_back({word, count}); 
}
```

第二种：
```cpp
string word; 
int count; 
vector<pair<string, int>> vofP; 

while( cin >> word ){
    if (!(cin >> count))  count = 0; 
    vofP.push_back(pair<string, int>(word, count)); 
}
```

第三种：
```cpp
string word; 
int count; 
vector<pair<string, int>> vofP; 

while( cin >> word ){
    if (!(cin >> count))  count = 0; 
    vofP.push_back(make_pair{word, count}); 
}
```

**哪一种最简单去使用？**
显而易见，第一种其实是最容易的，没有多余的代码，而且容易阅读。

**批改：** ⭐⭐⭐ (3/5) 良好答案，主要思路正确，存在重要细节问题

**详细分析：**
- ✅ **正确识别了三种基本方法**：你识别出了创建pair的三种主要方式，理解了题目的要求。
- ✅ **前两种方法完全正确**：第一种（使用花括号初始化）和第二种（显式构造函数调用）语法正确，能够正常工作。
- ⚠️ **第三种方法有语法错误**：`make_pair{word, count}` 是不正确的语法。`make_pair`是一个函数模板，应该使用圆括号而不是花括号来调用。
- ✅ **正确判断了哪种方法最简单**：你指出第一种方法最简单，这个判断是正确的，符合C++最佳实践。

**正确答案：**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main() {
    string word;
    int count;
    vector<pair<string, int>> vofP;
    
    // 版本1：使用花括号初始化（列表初始化）
    while(cin >> word) {
        if (!(cin >> count)) count = 0;
        vofP.push_back({word, count});  // 列表初始化
    }
    
    // 清空向量以重新使用
    vofP.clear();
    cin.clear();
    
    // 版本2：显式构造pair对象
    while(cin >> word) {
        if (!(cin >> count)) count = 0;
        vofP.push_back(pair<string, int>(word, count));  // 显式构造
    }
    
    vofP.clear();
    cin.clear();
    
    // 版本3：使用make_pair函数（正确语法）
    while(cin >> word) {
        if (!(cin >> count)) count = 0;
        vofP.push_back(make_pair(word, count));  // 使用make_pair函数
    }
    
    return 0;
}
