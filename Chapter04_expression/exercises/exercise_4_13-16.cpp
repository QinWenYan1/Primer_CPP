#include <iostream>

using std::cout;
using std::cin; 
using std::endl;

/*
* Exercise 4.13: 
* What are the values of i and d after each assignment?
* int i; double d;
* (a) d = i = 3.5; answer: d = 3.0, i = 3
* (b) i = d = 3.5; answer: d = 3.5, i = 3
*/

/*
* Exercise 4.14: 
* Explain what happens in each of the if tests:
* if (42 = i) // ... answer: error, 42 不能当lvalue 
* if (i = 42) // ... answer: 42 赋值给 i, 然后对i判断条件为true
*/

/*
* Exercise 4.15: 
* The following assignment is illegal. Why? How would you
* correct it?
* double dval; int ival; int *pi;
* dval = ival = pi = 0; 
* answer: illegal, pi = 0 合法（空指针常量）；
* 问题出在 接着把 pi（类型 int*）赋给 ival（类型 int）这一环，指针不能赋给整型。
* 改写 : dval = ival = 0; pi = nullptr; 
*/

/*
* Exercise 4.16: 
* Although the following are legal, they probably do not
* behave as the programmer expects. Why? Rewrite the expressions as you
* think they should be.
* (a) if (p = getPtr() != 0) answer: 会先比较gePtr()的返回值和0， 结果在赋给p 后在判断条件 rewrite: if((p = getPtr()) != 0)
* (b) if (i = 1024) answer: 将1024赋值给i, 然后判断条件 rewrite: i == 1024
*/

int main(void){

    int i;
    double d; 
    d = i = 3.5; 
    cout << "Print outcome ..." << endl;
    cout << i << " " << d << endl;
    i = d = 3.5;
    cout << i << " " << d << endl;




}