#include <iostream>
#include <typeinfo>

/*
* Exercise 2.33: 
* Using the variable definitions from this section, determine
* what happens in each of these assignments:
*/

/*
* Exercise 2.34: 
* Write a program containing the variables and assignments
* from the previous exercise. Print the variables before and after the
* assignments to check whether your predictions in the previous exercise were
* correct. If not, study the examples until you can convince yourself you know
* what led you to the wrong conclusion.
*/
int main(void){
    int i = 0, &r = i;
    auto a = r; // a is int（不是 int&，引用被忽略）
    const int ci = i, &cr = ci;
    auto b = ci; // b is int（顶层 const 被忽略）
    auto c = cr; // c is int（引用 + 顶层 const 都被忽略）
    auto d = &i; // d is int*
    auto e = &ci; // e is const int*

    std::cout << "Type of a: " << typeid(a).name() << std::endl;
    std::cout << "Type of b: " << typeid(b).name() << std::endl;
    std::cout << "Type of c: " << typeid(c).name() << std::endl;
    std::cout << "Type of d: " << typeid(d).name() << std::endl;
    std::cout << "Type of e: " << typeid(e).name() << std::endl;

    // 赋值合法性
    a = 42;    
    b = 42; 
    c = 42;
    // d = 42; // ❌ 不合法：d 是 int*
    // e = 42; // ❌ 不合法：e 是 const int*

    // -------- 🆕 添加易错例子 --------
    int arr[3] = {1, 2, 3};
    auto f = arr; // f is int* （数组退化为指针）
    std::cout << "Type of f (auto f = arr): " << typeid(f).name() << std::endl;

    auto& h = cr; // h is const int&（auto 推导引用时保留 const）
    std::cout << "Type of h (auto& h = cr): " << typeid(h).name() << std::endl;

    auto* p = &ci; // p is const int*（显式 auto*，保留 const）
    std::cout << "Type of p (auto* p = &ci): " << typeid(p).name() << std::endl;


    return 0;
}
