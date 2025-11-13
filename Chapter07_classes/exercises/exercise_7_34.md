## Exercise 7.34  
**题目**（Primer C++ 原书节选，第 285 页）  
What would happen if we put the typedef of pos in the Screen class on page 285 as the last line in the class?

```cpp
int height; // defines a name subsequently used inside Screen
class Screen {
public:
    void dummy_fcn(pos height) {
        cursor = width * height; 
    }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    typedef std::string::size_type pos;   // 放在最后
};
```

**Answer**  
编译器在扫描类成员声明时采用“两步走”策略：  
1. 先处理所有**成员声明**（返回类型、数据成员、形参列表）；  
2. 再处理**成员函数体**。

在第一步中，编译器只认识**已经出现过的名字**。  
因为 `typedef std::string::size_type pos;` 位于**所有用到 pos 的声明之后**，当编译器看到

```cpp
pos cursor = 0;
pos height = 0, width = 0;
void dummy_fcn(pos height);
```

时，**类内还没有任何名为 pos 的声明**，于是它继续到**外层作用域**查找，也未找到；最终给出  
**“unknown type name ‘pos’”** 的编译错误。


---

## Exercise 7.35  
**题目**  
Explain the following code, indicating which definition of `Type` or `initVal` is used for each use of those names. Say how you would fix any errors.

```cpp
typedef string Type;
Type initVal();

class Exercise {
public:
    typedef double Type;      // 重新定义外层类型
    Type setVal(Type);        // 返回类型与参数列表均使用类内 Type
    Type initVal();           // 同样使用类内 Type
private:
    int val;
};

Type Exercise::setVal(Type parm) {   // 返回类型落在全局，参数类型落在类内
    val = parm + initVal();
    return val;
}
```

**Answer**  
1. **类内名字查找**  
   - 在类体 `{}` 内部，**typedef double Type;** 把外层的 **string** 版本**隐藏**。  
   - 因此  
     – `setVal` 的**返回类型**、**参数类型**  
     – `initVal` 的返回类型  
     都使用 **double**（类内 Type）。

Exercise 7.35 订正版  
（只改“类外定义名字查找”部分，其余保持原样）

------------------------------------------------
2. **类外定义名字查找**  
   编译器按**从左到右**的普通顺序解析声明：

   - 当它看到  
     ```cpp
     Type Exercise::setVal(Type parm)
     ```  
     的**返回类型** `Type` 时，**尚未遇到** `Exercise::`，**完全不知道**接下来要进入类作用域；  
     因此它只在**当前作用域、外层作用域、全局作用域**里查找，找到外层的  
     ```cpp
     typedef string Type;
     ```  
     于是把返回类型确定为 **string**。

   - 解析完 `Exercise::setVal` 之后，**qualified name** 出现，编译器才把**参数列表**和**函数体**放进类作用域进行第二次查找；  
     此时参数里的 `Type` 找到类内  
     ```cpp
     typedef double Type;
     ```  
     被当作 **double**。

   结果编译器实际生成的签名是  
   ```cpp
   string Exercise::setVal(double parm);
   ```  
   与类内声明的  
   ```cpp
   double setVal(double);
   ```  
   **返回类型不匹配**，因此报 **“return type mismatch”** 错误（标准 ill-formed）。



3. **修复方案**  
   最干净的做法：**永远不要在内层作用域重新定义外层类型名**。  
   给类内类型另起名字：

```cpp
class Exercise {
public:
    typedef double value_type;          // 新名字，避免冲突
    value_type setVal(value_type);
    value_type initVal();
private:
    int val;
};

// 类外定义现在完全匹配
Exercise::value_type Exercise::setVal(value_type parm) {
    val = parm + initVal();
    return val;
}
```

这样既符合 C++ 名字查找规则，也彻底消除潜在错误。