# 📘 第12章 练习题评价

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| Exercise 12.21 | 4/5 ⭐⭐⭐⭐ | 判断正确但分析不够深入 |
| Exercise 12.22 | 2/5 ⭐⭐ | 基本理解有偏差，实现不完整 |

## 🎯 逐题详细评价

### Exercise 12.21 代码可读性比较

**原题：** We could have written StrBlobPtr's deref member as follows:
```cpp
//old version 
std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr]; // (*p) is the vector to which this object points
}

//new version 
std::string& deref() const { 
    return (*check(curr, "dereference past end"))[curr]; 
}
```

**你的答案：**
```
当然是老版本的更好一点，因为更readable，更好维护
```

**批改结果：** ⭐⭐⭐⭐ 4/5
- **概念理解：** ✅ 正确判断旧版本更易读
- **代码质量：** ⚠️ 分析可以更深入
- **逻辑完整：** ✅ 结论合理
- **表达清晰：** ✅ 表达明确

**详细分析：**
- ✅ **判断正确**：旧版本确实更易读、更易维护
- ✅ **关注可维护性**：注意到代码维护的重要性
- ⚠️ **分析不够深入**：没有详细解释为什么旧版本更好
- ⚠️ **缺少对比分析**：没有具体比较两个版本的差异

**正确答案分析：**
```cpp
// 旧版本（更好）：
// 1. 使用中间变量p，使代码更清晰
// 2. 错误检查和业务逻辑分离
// 3. 便于调试（可以单独检查p的值）
// 4. 代码行数多但可读性更强

// 新版本（更简洁但可读性差）：
// 1. 单行代码完成所有操作，更紧凑
// 2. 可读性较差，特别是对初学者
// 3. 调试困难（不能单独检查check的返回值）
// 4. 不符合"单一职责原则"
```

---

### Exercise 12.22 ConstStrBlobPtr实现

**原题：** What changes would need to be made to StrBlobPtr to create a class that can be used with a const StrBlob? Define a class named ConstStrBlobPtr that can point to a const StrBlob.

**你的答案：**
```cpp
为了让其可以绑定const的StrBlob对象，我们需要一个小改动在构造函数里面:
    StrBlobPtr(const StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) { }
```

**批改结果：** ⭐⭐ 2/5
- **概念理解：** ❌ 理解有偏差，不只是构造函数需要修改
- **代码质量：** ⚠️ 提供的代码不完整
- **逻辑完整：** ❌ 解决方案不完整
- **表达清晰：** ✅ 表达清晰

**问题分析：**
1. **概念理解错误**：ConstStrBlobPtr不仅需要修改构造函数，还需要修改所有成员函数以正确处理const对象
2. **未定义新类**：题目要求定义新类`ConstStrBlobPtr`，而不是修改现有的`StrBlobPtr`
3. **访问权限问题**：const StrBlob的data成员是private的，需要友元声明

**正确答案：**
```cpp
#ifndef CONST_STRBLOBPTR_H
#define CONST_STRBLOBPTR_H

#include <string>
#include <memory>
#include <vector>
#include "StrBlob.h"

class ConstStrBlobPtr {
public:
    ConstStrBlobPtr() : curr(0) { }
    // 关键：接受const StrBlob&
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) 
        : wptr(a.data), curr(sz) { }
    
    // 返回const引用，因为不能修改const StrBlob的内容
    const std::string& deref() const;
    
    // 前缀递增
    ConstStrBlobPtr& incr();
    
private:
    // 检查函数，返回const shared_ptr
    std::shared_ptr<const std::vector<std::string>>
    check(std::size_t, const std::string&) const;
    
    // 存储weak_ptr，指向const vector
    std::weak_ptr<const std::vector<std::string>> wptr;
    std::size_t curr;
};

// 实现check函数
std::shared_ptr<const std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound ConstStrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

// 实现deref，返回const引用
const std::string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

// 实现incr
ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

#endif
```

**还需要修改StrBlob类（在StrBlob.h中添加）：**
```cpp
class StrBlob {
    // ... 原有代码 ...
    
    // 添加const版本的begin和end
    ConstStrBlobPtr begin() const { return ConstStrBlobPtr(*this); }
    ConstStrBlobPtr end() const { 
        return ConstStrBlobPtr(*this, data->size()); 
    }
    
    // 声明ConstStrBlobPtr为友元
    friend class ConstStrBlobPtr;
    
    // ... 原有代码 ...
};
```
