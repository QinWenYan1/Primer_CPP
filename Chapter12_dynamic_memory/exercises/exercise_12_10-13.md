## 📊 练习批改与分析

### Exercise 12.10 shared_ptr的正确使用

**原题：** Explain whether the following call to the process function defined on page 464 is correct. If not, how would you correct the call?

```cpp
// ptr is created and initialized when process is called
void process(shared_ptr<int> ptr)
{
    // use ptr
} // ptr goes out of scope and is destroyed
```

```cpp
shared_ptr<int> p(new int(42));
process(shared_ptr<int>(p));
```

**你的答案：**
```
有问题，当我们初始化了一个临时变量shared_ptr并传入进入到process的时候这里其实重新创立了一个shared_ptr变量，也就是ptr来参与到控制内存中，可是当process执行完后，local变量ptr销毁导致引用计数为0，直接将这一块共同管理的内存销毁，那么外面的p指针就成为了dangling pointer了，为了解决这个问题，我们需要修改为:

    shared_ptr<int> p(new int(42))
    process(p);
直接传入p即可，因为内存的销毁不会由于process里的ptr变量销毁而销毁
```

**批改：** ⭐⭐⭐ 3/5 结论正确但分析不准确

**详细分析：**
- ✅ **结论正确**：建议改为`process(p)`是正确的
- ⚠️ **分析不准确**：原代码实际上不会导致悬垂指针，但分析逻辑有误
- ❌ **引用计数理解错误**：`ptr`销毁后引用计数不会变为0，因为`p`仍然存在

**正确答案：**

### 原代码分析：
```cpp
shared_ptr<int> p(new int(42));  // 引用计数 = 1
process(shared_ptr<int>(p));     // 创建临时shared_ptr，引用计数 = 2
                                  // 进入process，ptr是参数的副本，引用计数 = 3
                                  // 离开process，ptr销毁，引用计数 = 2
                                  // 临时对象销毁，引用计数 = 1
```

**原调用`process(shared_ptr<int>(p))`实际上是安全的**，因为：
1. 创建临时`shared_ptr`对象是从`p`**拷贝构造**的，它们共享同一个控制块
2. 进入函数时，参数`ptr`又是临时对象的拷贝，引用计数再次增加
3. 函数结束时，`ptr`销毁，引用计数减少
4. 临时对象销毁，引用计数回到1（`p`仍然持有）
5. 不会释放内存，`p`不是悬垂指针

**但为什么建议改为`process(p)`？**
1. **更高效**：避免创建不必要的临时对象
2. **更清晰**：代码意图更明确
3. **更安全**：减少潜在的错误可能


---

### Exercise 12.11 危险的shared_ptr构造

**原题：** What would happen if we called process as follows?
```cpp
process(shared_ptr<int>(p.get()));
```

**你的答案：**
```
还是和上面同样的道理，当我们传入一个新的shared_ptr local 变量进去的时候，process里面就会将这个p所指的内存销毁导致dangling pointer
```

**批改：** ⭐⭐ 2/5 结论基本正确但分析不够准确和详细

**详细分析：**
- ✅ **结论基本正确**：指出了这会创建悬垂指针
- ⚠️ **分析不准确**：没有解释为什么这与之前的调用不同
- ❌ **未提及关键问题**：没有提到这会创建独立的控制块导致双重释放

**正确答案：**

### 危险调用分析：
```cpp
process(shared_ptr<int>(p.get()));  // 非常危险！
```

**发生了什么：**
1. `p.get()`返回原始指针（`int*`）
2. 使用这个原始指针构造一个新的`shared_ptr`
3. 这个新的`shared_ptr`与`p`**不共享控制块**，它有自己的引用计数（初始为1）
4. 函数结束时，这个临时`shared_ptr`销毁，引用计数变为0，**释放内存**
5. `p`现在变成了**悬垂指针**（指向已释放的内存）
6. 当`p`最终销毁时，会尝试再次释放同一块内存，导致**双重释放**（未定义行为，通常程序崩溃）

---

## 📊 练习批改与分析

### Exercise 12.12 process调用的合法性分析

**原题：** Using the declarations of p and sp explain each of the following calls to process. If the call is legal, explain what it does. If the call is illegal, explain why:
```cpp
auto p = new int();
auto sp = make_shared<int>();
```
(a) `process(sp);`
(b) `process(new int());`
(c) `process(p);`
(d) `process(shared_ptr<int>(p));`

**你的答案：**
```
(a). legal的， 将传入的shared_ptr参数传入后，处理并销毁， 但是sp并未销毁
(b). 错误， 需要显示申明转换， 因为shared_ptr的构造函数为explicit
(c). 同样的道理也是错误的，需要显示申明
(d). 错误，这一次传入并没有问题，但是传入的shared_ptr参数的counter为1，process结束后counter为0， 将内存释放了， 导致dangling pointer
```

**批改：** ⭐⭐⭐ 3/5 部分正确，但存在一些错误

**详细分析：**
- ✅ (a) **完全正确**：`process(sp)`是合法的，参数通过拷贝构造传递
- ✅ (b) **正确**：`process(new int())`非法，因为`shared_ptr`构造函数是explicit
- ⚠️ (c) **表述不准确**：`process(p)`确实非法，原因同(b)，但"需要显示申明"的说法不严谨
- ❌ (d) **分析错误**：这个调用是合法的，但会导致悬垂指针，不过引用计数分析有误

**正确答案：**

### (a) `process(sp);`
- **合法**：`sp`是`shared_ptr`，传递给`process`时会拷贝构造一个新的`shared_ptr`
- **引用计数变化**：调用前`sp.use_count() == 1`，调用时创建临时对象计数+1，函数内`ptr`拷贝计数+1，函数返回时`ptr`销毁计数-1，临时对象销毁计数-1，最终`sp.use_count() == 1`
- **结果**：`sp`仍然有效管理内存

### (b) `process(new int());`
- **非法**：编译错误。`shared_ptr`的构造函数是`explicit`的，不能从`int*`隐式转换
- **修正**：需要显式构造`shared_ptr`：`process(shared_ptr<int>(new int()))`
- **注意**：即使修正，这种写法也不安全（如果process抛出异常可能导致内存泄漏），应使用`make_shared`

### (c) `process(p);`
- **非法**：编译错误。原因同(b)，不能从原始指针隐式转换为`shared_ptr`
- **注意**：`p`是原始指针，而`process`需要`shared_ptr`，需要显式转换

### (d) `process(shared_ptr<int>(p));`
- **语法合法但语义危险**：从原始指针显式构造临时`shared_ptr`
- **问题**：创建了新的控制块（与(a)不同，不是从已有`shared_ptr`拷贝）
- **后果**：函数结束后，临时`shared_ptr`销毁，引用计数为0，释放内存，使`p`成为悬垂指针
- **双重释放风险**：如果之后`delete p`，会导致双重释放


---

### Exercise 12.13 危险的get()和delete操作

**原题：** What happens if we execute the following code?
```cpp
auto sp = make_shared<int>();
auto p = sp.get();
delete p;
```

**你的答案：**
```
直接导致sp成为dangling pointer
```

**批改：** ⭐⭐⭐⭐ 4/5 正确，但可以更详细

**详细分析：**
- ✅ **结论正确**：`sp`确实变成了悬垂指针
- ⚠️ **可以更详细**：没有解释双重释放的问题
- ⚠️ **未提到引用计数**：`sp`的引用计数仍然为1，但指向的内存已被释放

**正确答案：**

执行这段代码会导致严重问题：

1. **内存被提前释放**：`sp.get()`返回一个不拥有所有权的原始指针，`delete p`手动释放了`shared_ptr`管理的内存
2. **`sp`成为悬垂指针**：`sp`仍然指向已释放的内存，任何通过`sp`的访问都是未定义行为
3. **双重释放风险**：当`sp`离开作用域时，它的析构函数会尝试再次释放同一块内存，导致双重释放（程序通常崩溃）
4. **引用计数不一致**：控制块认为还有1个引用（`sp`），但实际上内存已被释放

---