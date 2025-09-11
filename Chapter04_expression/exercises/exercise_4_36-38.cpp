#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string; 

/*
* Exercise 4.36: 
* Assuming i is an int and d is a double write the
* expression i *= d so that it does integral, rather than floating-point,
* multiplication.
*/

/*
* Exercise 4.37: 
* Rewrite each of the following old-style casts to use a named cast:
* int i;              double d; 
* const string *ps;   char *pc; 
* void *pv;
* (a) pv = (void*)ps;
* (b) i = int(*pc);
* (c) pv = &d;
* (d) pc = (char*) pv;
*/

/*
* Exercise 4.38: 
* Explain the following expression:
* double slope = static_cast<double>(j/i);
* Answer: j/i 得到一个int的结果，小数部分截断， 
* 然后在讲int转换为double值，添加小数.0得到double结果
*/

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
    // Exercise 4.36
    int i = 5;
    double d = 2.5;
    i *= static_cast<int>(d); // 整数乘法：i = 5 * 2 = 10
    cout << i << endl; // 输出 10

    // Exercise 4.37
    const string *ps = nullptr;
    char *pc = nullptr;
    void *pv;
    int i_val;
    double d_val;

    // (a) pv = (void*)ps;
    pv = static_cast<void*>(const_cast<string*>(ps));

    // (b) i = int(*pc);
    i_val = static_cast<int>(*pc); // 注意：pc 应指向有效内存，否则未定义行为

    // (c) pv = &d;
    pv = static_cast<void*>(&d_val);

    // (d) pc = (char*) pv;
    pc = static_cast<char*>(pv);

    // Exercise 4.38
    int j = 5, i_div = 2;
    double slope = static_cast<double>(j / i_div); // j/i_div = 2, 然后转换为 2.0
    cout << slope << endl; // 输出 2.0

    return 0;
}