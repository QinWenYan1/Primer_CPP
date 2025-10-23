# 📘 练习题笔记 7.16-7.19

> 来源说明：C++ Primer 第7章练习题 | 本节涵盖：访问控制、封装概念和类设计实践

---

## 📝 Exercise 7.16: 访问说明符约束

**原题：** What, if any, are the constraints on where and how often an access specifier may appear inside a class definition? What kinds of members should be defined after a public specifier? What kinds should be private?

### 你的答案：
> "最好一个类里面出现2次以下，一次给成员函数，一次给成员数据。给成员数据的public和private先出现，然后再是给成员函数的public和private
> 
> 放在public后面的应该是对外的接口函数，使用者应该通过接口来改动实例数据或状态
> 
> 放在private后面的应该是内部使用的函数，以及所有成员数据，这些只能在内部调用，不希望被使用者看到或者无意中使用到的，都放在private"

### ✅ 修正与完整答案：

**访问说明符约束：**
- ❌ **错误理解**：认为"最好出现2次以下"
- ✅ **正确理解**：访问说明符可以出现任意多次，没有限制。教材明确说"there are no restrictions on how often an access specifier may appear"

**成员分类原则：**
- ✅ **public成员**：类的接口部分
  - 构造函数
  - 获取和修改对象状态的成员函数
  - 其他对外服务函数
- ✅ **private成员**：类的实现细节
  - 所有数据成员（实现封装）
  - 内部辅助函数
  - 不希望用户直接访问的任何内容


---

## 📝 Exercise 7.17: class与struct区别

**原题：** What, if any, are the differences between using class or struct?

### 你的答案：
> "只有一个区别，那就是默认访问，class默认是private, struct默认是public"

### ✅ 完整答案：

**技术区别：**
- ✅ **唯一区别**：默认访问级别不同
  - `class`：第一个访问说明符前的成员默认为**private**
  - `struct`：第一个访问说明符前的成员默认为**public**


**选择原则：**
- 使用`struct`：所有成员都是public的简单数据容器
- 使用`class`：需要数据封装和行为控制的复杂类型

---

## 📝 Exercise 7.18: 封装概念

**原题：** What is encapsulation? Why is it useful?

### 你的答案：
> "封装就是将不必要的成员数据和接口不暴露在外给使用者无意使用到造成不必要的改动"

### ✅ 修正与完整答案：

**封装定义：**
- 通过访问控制机制隐藏类的实现细节
- 只暴露必要的接口给用户

**封装的好处：**
1. **防止意外破坏**：用户代码无法直接修改对象内部状态
2. **实现灵活性**：类的内部实现可以改变而不影响用户代码
3. **错误定位**：bug搜索范围局限于类实现代码
4. **维护便利**：只需检查类代码来评估更改影响

---

## 📝 Exercise 7.19: Person类设计

**原题：** Indicate which members of your Person class you would declare as public and which you would declare as private. Explain your choice.

### 你的答案：
> "所有的constructor以及get_name, get_address是public的意外其余的都是private, 因为public的这几个函数都是提供给类使用者的接口，他们必须通过这些函数来改动类的状态，而其余的都是不想使用者使用到的"

### ✅ 完整答案：

**当前代码问题分析：**
```cpp
struct Person {  // ❌ 使用struct，所有成员默认public
    // 所有成员当前都是public的！
    std::string name = "None";      // ❌ 应该private
    std::string address = "None";   // ❌ 应该private
};
```

**正确的访问控制设计：**

```cpp
class Person {  // ✅ 改为class，默认private
public:
    // ✅ PUBLIC: 构造和访问接口
    Person() = default; 
    Person(std::string name);
    Person(std::string name, std::string address);
    Person(std::istream &);
    
    // 获取信息的接口
    const std::string& get_name() const { return name; }
    const std::string& get_address() const { return address; } 

    // ✅ 需要声明友元函数
    friend std::istream &read(std::istream &in, Person &people);
    friend std::ostream &print(std::ostream &out, const Person &people);

private:
    // ✅ PRIVATE: 所有数据成员
    std::string name = "None";
    std::string address = "None";
};
```

**访问控制分类表：**

| 成员 | 访问级别 | 理由 |
|------|----------|------|
| 所有构造函数 | public | 用户需要创建对象 |
| get_name() | public | 获取信息的只读接口 |
| get_address() | public | 获取信息的只读接口 |
| name数据成员 | private | 防止直接修改，保持数据完整性 |
| address数据成员 | private | 防止直接修改，保持数据完整性 |
| read()函数 | friend | 需要访问私有数据来初始化 |
| print()函数 | friend | 需要访问私有数据来输出 |

**设计原则体现：**
- **信息隐藏**：数据成员完全隐藏在private区域
- **最小接口**：只提供必要的构造函数和访问函数
- **封装完整性**：通过友元机制在必要时打破封装，但保持控制


**封装好处记忆法：**
*"防破坏、易修改、好维护、快定位"*