# 📘 第13章 练习题评价（续）

## 📋 总体概览

| 题目 | 得分 | 评价摘要 |
|------|------|----------|
| 13.6 | ⭐⭐⭐ | 基本理解概念，但表达不够准确和完整 |
| 13.7 | ⭐⭐⭐⭐ | 理解正确，表达清晰，但可以更详细 |

## 🎯 逐题详细评价

### Exercise 13.6: 拷贝赋值运算符
**原题：** What is a copy-assignment operator? When is this operator used? What does the synthesized copy-assignment operator do? When is it synthesized?

**你的答案：**
```
在类中存在某种构造函数使使用operator=来申明的并且传入的参数也是和当前类相同的引用那么这个就是copy-assignment operator

copy-assignment operator就是让rvalue按照期望的方式进行复制进入到lvalue

如果writer不定义自己的复制操作符号的时候， 就会自动合成
```

**批改结果：** ⭐⭐⭐ (3/5)
- **概念理解：** 基本理解拷贝赋值运算符的概念，但表达不够准确
- **代码质量：** 描述性语言，概念理解有偏差
- **逻辑完整：** 回答不够全面，缺少关键细节
- **表达清晰：** 表达有歧义，术语使用不准确

**正确答案：**

#### 1. **什么是拷贝赋值运算符？**
拷贝赋值运算符是一个名为`operator=`的成员函数，它接受一个与类相同类型的参数（通常是`const`引用），并返回指向左侧运算对象的引用。

```cpp
class Foo {
public:
    Foo& operator=(const Foo&); // 拷贝赋值运算符
};
```

#### 2. **什么时候使用这个运算符？**
当使用赋值操作符`=`将一个类对象赋值给另一个同类型的对象时：
```cpp
Foo a, b;
a = b; // 调用 a.operator=(b)，即拷贝赋值运算符
```

#### 3. **合成的拷贝赋值运算符做什么？**
如果类没有定义自己的拷贝赋值运算符，编译器会合成一个。合成的拷贝赋值运算符：
- 将右侧对象的每个非静态成员赋值给左侧对象的对应成员
- 对于数组成员，赋值每个元素
- 对于类类型成员，使用该成员的拷贝赋值运算符
- 对于内置类型成员，直接赋值
- 返回指向左侧对象的引用

#### 4. **什么时候合成？**
当类没有定义自己的拷贝赋值运算符时，编译器会自动合成一个。但是，在某些情况下（如类有`const`成员或引用成员），合成的拷贝赋值运算符会被定义为删除的（`deleted`）。


---

### Exercise 13.7: 赋值StrBlob和StrBlobPtr时会发生什么？
**原题：** What happens when we assign one `StrBlob` to another? What about `StrBlobPtr`s?

**你的答案：**
```
StrBlob 中包含一个shared_ptr, 那么shared_ptr类型的指针会被复制到lvalue并增加counter by 1 

StrBlobPtr里面是一个weak_ptr, 操作符直接将这个weak_ptr复制给lvalue
```

**批改结果：** ⭐⭐⭐⭐ (4/5)
- **概念理解：** 基本正确，理解了智能指针的赋值语义
- **代码质量：** 描述准确，但可以更详细
- **逻辑完整：** 涵盖了主要行为，但缺少一些细节
- **表达清晰：** 表达清晰，但术语可以更准确

**正确答案：**

#### **赋值`StrBlob`时：**
1. 调用`StrBlob`的拷贝赋值运算符（编译器合成的）
2. `StrBlob`包含一个`shared_ptr<vector<string>>`
3. 赋值操作会调用`shared_ptr`的拷贝赋值运算符
4. 左侧`shared_ptr`会释放原来管理的对象（如果引用计数变为0）
5. 右侧`shared_ptr`的引用计数增加1
6. 两个`StrBlob`对象现在共享同一个`vector<string>`

#### **赋值`StrBlobPtr`时：**
1. 调用`StrBlobPtr`的拷贝赋值运算符（编译器合成的）
2. `StrBlobPtr`包含一个`weak_ptr<vector<string>>`
3. 赋值操作会调用`weak_ptr`的拷贝赋值运算符
4. 左侧`weak_ptr`会放弃对原来对象的弱引用
5. 右侧`weak_ptr`的弱引用被拷贝到左侧
6. **重要**：`weak_ptr`的赋值**不会增加**`shared_ptr`的引用计数
7. 两个`StrBlobPtr`对象现在共享对同一个`vector<string>`的弱引用

---