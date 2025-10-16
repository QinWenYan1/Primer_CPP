# Exercise 6.52
**题目**：Given the following declarations,
```cpp
void manip(int, int);
double dobj;
```
what is the rank (§ 6.6.1, p. 245) of each conversion in the following calls?
(a) `manip('a', 'z');`
(b) `manip(55.4, dobj);`

**答案**：
(a) ✅ **正确** - promotion (rank 3)，将char提升到int
(b) ✅ **正确** - arithmetic conversion (rank 4)，将double转换为int

# Exercise 6.53
**题目**：Explain the effect of the second declaration in each one of the following sets of declarations. Indicate which, if any, are illegal.
(a) 
```cpp
int calc(int&, int&);
int calc(const int&, const int&);
```
(b) 
```cpp
int calc(char*, char*);
int calc(const char*, const char*);
```
(c) 
```cpp
int calc(char*, char*);
int calc(char* const, char* const);
```

**答案**：
(a) ✅ **正确** - 使用low-level const进行重载，合法，可以接受更广泛的参数范围
(b) ✅ **正确** - 与(a)相同原理，合法
(c) ✅ **正确** - 非法，top-level const差异不能构成重载，属于重复声明

**补充说明**：你的答案完全正确！对于(c)的情况，`char* const`中的const是顶层const（指针本身是const），而函数重载只考虑底层const（指向的对象是const），所以这两个声明被视为相同的函数签名。