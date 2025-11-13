**Exercise 7.33:** What would happen if we gave Screen a size member defined as follows? Fix any problems you identify.

```cpp
pos Screen::size() const{
    return height * width;
}
```

## 问题分析

假设 `Screen` 类的定义类似于：

```cpp
class Screen {
public:
    typedef std::string::size_type pos;  // pos 是 Screen 类的成员类型
    // 或者：using pos = std::string::size_type;
    
    pos size() const;  // 声明
    
private:
    pos height = 0, width = 0;
};
```

**问题：**
在类外定义成员函数时：
```cpp
pos Screen::size() const{    // 错误！
    return height * width;
}
```

- 返回类型 `pos` 出现在函数名 `Screen::size` 之前
- 此时编译器还不知道 `pos` 是 `Screen` 类的成员类型
- 编译器会在外层作用域中查找 `pos` 类型，如果找不到就会报编译错误

## 修正方案

### 方案1：使用作用域限定符（你的答案）
```cpp
Screen::pos Screen::size() const{
    return height * width;
}
```

### 方案2：使用尾置返回类型（C++11）
```cpp
auto Screen::size() const -> pos {
    return height * width;
}
```
