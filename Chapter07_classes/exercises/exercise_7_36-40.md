# 📘 C++构造函数练习题详解

## Exercise 7.36
**原题：** The following initializer is in error. Identify and fix the problem.
```cpp
struct X {
    X(int i, int j): base(i), rem(base % j) { }
    int rem, base;
};
```

**答案：**
问题在于**成员初始化顺序**。在C++中，成员的初始化顺序由它们在类定义中的**声明顺序**决定，而不是构造函数初始化列表中的顺序。

在这个例子中：
- 成员声明顺序：`rem` 在前，`base` 在后
- 初始化列表顺序：`base(i)` 在前，`rem(base % j)` 在后

实际执行顺序：
1. 先初始化 `rem(base % j)` - 但此时 `base` 还未初始化，值是未定义的
2. 再初始化 `base(i)`

**修正方法1：调整成员声明顺序**
```cpp
struct X {
    int base, rem;  // base在前，rem在后
    X(int i, int j): base(i), rem(base % j) { }
};
```

**修正方法2：避免成员间的依赖**
```cpp
struct X {
    int rem, base;
    X(int i, int j): base(i), rem(i % j) { }  // 使用参数i而不是base
};
```

---

## Exercise 7.37
**原题：** Using the version of Sales_data from this section, determine which constructor is used to initialize each of the following variables and list the values of the data members in each object:
```cpp
class Sales_data {
public:
    Sales_data(std::string s = ""): bookNo(s) { }
    Sales_data(std::string s, unsigned cnt, double rev):
        bookNo(s), units_sold(cnt), revenue(rev*cnt) { }
    Sales_data(std::istream &is) { read(is, *this); }
};

Sales_data first_item(cin);
int main() {
    Sales_data next;
    Sales_data last("9-999-99999-9");
}
```

**答案：**

1. **`first_item(cin)`**
   - 使用的构造函数：`Sales_data(std::istream &is)`
   - 数据成员值：从标准输入流 `cin` 读取，具体值取决于输入内容
   - 注意：`first_item` 是全局变量，在 `main` 函数执行前初始化

2. **`next`**（在main函数内）
   - 使用的构造函数：`Sales_data(std::string s = "")`（默认构造函数）
   - 数据成员值：
     - `bookNo` = `""`（空字符串）
     - `units_sold` = `0`（未显式初始化，内置类型默认值）
     - `revenue` = `0.0`（未显式初始化，内置类型默认值）

3. **`last("9-999-99999-9")`**
   - 使用的构造函数：`Sales_data(std::string s = "")`
   - 数据成员值：
     - `bookNo` = `"9-999-99999-9"`
     - `units_sold` = `0`
     - `revenue` = `0.0`

---

## Exercise 7.38
**原题：** We might want to supply cin as a default argument to the constructor that takes an istream&. Write the constructor declaration that uses cin as a default argument.

**答案：**
```cpp
Sales_data(std::istream &is = std::cin) { read(is, *this); }
```

**说明：**
- 使用 `std::cin` 作为默认参数，这样当不提供参数时会从标准输入读取
- 注意：`std::cin` 是标准输入流对象，不是 `std::endl`（`endl` 是输出操纵器）

---

## Exercise 7.39
**原题：** Would it be legal for both the constructor that takes a string and the one that takes an istream& to have default arguments? If not, why not?

**答案：**
**不合法**，因为会造成**重载歧义**。

如果两个构造函数都有默认参数：
```cpp
class Sales_data {
public:
    Sales_data(std::string s = "");          // 默认构造函数版本1
    Sales_data(std::istream &is = std::cin); // 默认构造函数版本2
};
```

当这样使用时：
```cpp
Sales_data obj;  // 错误：歧义！
```

编译器无法确定应该调用哪个构造函数：
- 两个构造函数都可以不带参数调用
- 两个都匹配默认构造函数的调用
- 编译器无法在两者之间做出选择

**结论：** 一个类只能有一个默认构造函数。

---

## Exercise 7.40
**原题：** Choose one of the following abstractions (or an abstraction of your own choosing). Determine what data are needed in the class. Provide an appropriate set of constructors. Explain your decisions.
(a) Book  
(b) Date  
(c) Employee  
(d) Vehicle  
(e) Object  
(f) Tree  

**答案：** 选择 (c) Employee

```cpp
#include <string>

class Employee {
private:
    std::string name;
    int employeeId;
    double salary;
    int level;                   // 职级
    std::string occupationName;  // 职位名称
    std::string departmentName;  // 部门名称

public:
    // 1. 默认构造函数 - 所有成员使用合理默认值
    Employee() 
        : name(""), employeeId(0), salary(0.0), level(1), 
          occupationName(""), departmentName("") { }

    // 2. 主要构造函数 - 包含所有参数，带默认值
    Employee(const std::string& n, int id = 0, double sal = 0.0, 
             int lvl = 1, const std::string& occ = "", 
             const std::string& dept = "")
        : name(n), employeeId(id), salary(sal), level(lvl), 
          occupationName(occ), departmentName(dept) { }

    // 3. 简化构造函数 - 只有基本信息的员工
    Employee(const std::string& n, int id) 
        : name(n), employeeId(id), salary(0.0), level(1), 
          occupationName("Employee"), departmentName("General") { }

    // 4. 拷贝构造函数 - 用于创建员工的副本
    Employee(const Employee& other)
        : name(other.name), employeeId(other.employeeId), 
          salary(other.salary), level(other.level),
          occupationName(other.occupationName), 
          departmentName(other.departmentName) { }

    // 成员函数声明...
};

// 使用示例：
// Employee e1;                          // 默认构造
// Employee e2("John", 1001);           // 简化构造
// Employee e3("Alice", 1002, 50000.0, 3, "Manager", "IT"); // 完整构造
// Employee e4 = e3;                    // 拷贝构造
```

**设计决策解释：**

1. **成员变量选择**：
   - `name`：员工姓名（字符串）
   - `employeeId`：员工ID（整数，唯一标识）
   - `salary`：薪资（浮点数）
   - `level`：职级（整数，表示职位级别）
   - `occupationName`：职位名称
   - `departmentName`：部门名称

2. **构造函数设计**：
   - **默认构造函数**：提供合理的默认值，确保对象总是有效状态
   - **主要构造函数**：使用默认参数，灵活支持不同详细程度的初始化
   - **简化构造函数**：为常见用例（只有基本信息的员工）提供便利
   - **拷贝构造函数**：支持对象复制（编译器会自动生成，但显式写出更清晰）

3. **使用初始化列表**：所有构造函数都使用初始化列表，确保高效初始化

4. **默认值选择**：
   - 薪资默认为0.0，职级默认为1（最低级别）
   - 字符串默认为空，避免未定义行为

这样的设计提供了灵活性，同时保持了代码的简洁性和易用性。