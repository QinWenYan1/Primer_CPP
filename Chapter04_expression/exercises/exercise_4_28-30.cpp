#include <iostream>

using std::endl;
using std::cout;
using std::cin;

/*
* Exercise 4.28: 
* Write a program to print the size of each of the built-in types.
*/

/*
* Exercise 4.29: 
* Predict the output of the following code and explain your
* reasoning. Now run the program. Is the output what you expected? If not,
* figure out why
* int x[10]; int *p = x;
* cout << sizeof(x)/sizeof(*x) << endl;
* cout << sizeof(p)/sizeof(*p) << endl;
* answer: 
* 第一排将p指向数组的第一个元素，x衰变为指针
* 第二排相当于是将整个数组x的总大小除以单个元素的大小，得到数组元素个数， 
* 其中 *x的x会衰变为指针然后被解引用
* 第三排相当于是将单个数组的头元素的指针大小除以单个元素的大小，输出指针大小和int大小的比值
*/

/*
* Exercise 4.30: 
* Using Table 4.12 (p. 166), parenthesize the following
* expressions to match the default evaluation:
* (a) sizeof x + y
* (b) sizeof p->mem[i]
* (c) sizeof a < b
* (d) sizeof f()
*/

struct Foo {
    int mem[10] = {};
};

int f(void){}

int main(void){

    //exercise 28 
    cout << "Print out size of each built-in types in byte ..." << endl;
    cout << "char: " << sizeof (char) << endl; 
    cout << "bool: " << sizeof (bool) << endl;
    cout << "short: " << sizeof (short) << endl;
    cout << "int: " << sizeof (int) << endl;
    cout << "long: " << sizeof (long) << endl;
    cout << "float: " << sizeof (float) << endl;
    cout << "double: " << sizeof (double) << endl;
    cout << "void pointer: " << sizeof (void *) << endl;
    cout << "long long: " << sizeof (long long) << endl;
    cout << "long double: " << sizeof (long double) << endl;

    //exercise 29
    int x[10]; int *p = x;
    cout << sizeof(x)/sizeof(*x) << endl;
    cout << sizeof(p)/sizeof(*p) << endl;

    //exercise 30
    cout << "check the outcome ..." << endl;
    int x1 = 0, y = 0;
    int a = 10, b = 11; 
    Foo w, *p1 = &w;  
    cout << sizeof (x1 + y) << endl; //(sizeof x1) + y << endl; 因为sizeof优先于二元算术运算符
    cout << sizeof p1->mem[1] << endl; // sizeof (p->mem[i]), 成员运算符优先级高， 不用括号
    cout << sizeof (a < b) << endl; //(sizeof a) < b, sizeof 的优先级更高需要括号
    cout << sizeof f() << endl; // 不需要括号, sizeof (f())

}