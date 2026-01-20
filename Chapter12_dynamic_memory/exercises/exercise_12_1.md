# 📊 练习批改与分析

### Exercise 12.1 对象元素数量分析

**原题：** 
How many elements do b1 and b2 have at the end of this code?

```
class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // element access
    std::string& front();
    std::string& back();
private:
    std::shared_ptr<std::vector<std::string>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

StrBlob b1;
{
    StrBlob b2 = {"a", "an", "the"};
    b1 = b2;
    b2.push_back("about");
}
```

**你的答案：**
根据StrBolb类的定义我们可以知道，他们的成员是一个shared_ptr指向一个vector<string>的内存，由于=操作这些并没有被单独重载， 因此b1,b2是直接共享的一块内存， 并且shared_ptr的count为2， 现在vector中有三个元素， 同时b2又push进入一个元素， 就一共有了4个元素

然而当我们退出一个作用域的时候， b2作为local variable直接销毁， shared_ptr的count减少至1, 换句话说b1接管了那块内存

最后b1一共有4个元素， 然而b2什么也没有，0个

**批改：** ⭐⭐⭐⭐ (4/5) 优秀答案，核心概念理解正确，有轻微表述问题

**详细分析：**
- ✅ **概念理解准确**：你正确理解了`shared_ptr`的共享机制和引用计数原理
- ✅ **逻辑分析正确**：准确分析了赋值操作后的共享状态以及作用域结束后的对象生命周期
- ⚠️ **表述不够精确**：类名拼写错误（StrBolb → StrBlob），且对b2的最终状态描述可以更严谨
- ⚠️ **分析过程可完善**：没有明确指出默认构造的b1初始状态，以及赋值操作的具体影响

**正确答案分析：**

1. **初始状态**：
   - `StrBlob b1;` - 调用默认构造函数，创建一个空的`vector<string>`
   - `StrBlob b2 = {"a", "an", "the"};` - 使用初始化列表构造函数，创建包含3个元素的`vector`

2. **赋值操作**：
   - `b1 = b2;` - 使用合成拷贝赋值操作符，使得b1和b2的`shared_ptr`指向同一个`vector`
   - b1原来的空`vector`由于引用计数归零而被销毁
   - 现在共享的`vector`有3个元素，引用计数为2

3. **添加元素**：
   - `b2.push_back("about");` - 向共享的`vector`添加第4个元素
   - 此时共享`vector`包含4个元素：`"a"`, `"an"`, `"the"`, `"about"`

4. **作用域结束**：
   - b2被销毁，`shared_ptr`引用计数减为1
   - b1仍然持有对`vector`的引用
   - 因此`vector`不会被销毁

**最终结果：**
- b1有4个元素（`size()`返回4）
- b2已经不存在（超出作用域被销毁），谈论"b2有多少个元素"没有意义

---