#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*
* Exercise 4.4: 
* Parenthesize the following expression to show how it is
* evaluated. Test your answer by compiling the expression (without
* parentheses) and printing its result.
*/

/*
* Exercise 4.5: 
* Determine the result of the following expressions.
*/

/*
* Exercise 4.6: 
* Write an expression to determine whether an int value is
* even or odd.
*/

/*
* Exercise 4.7: 
* What does overflow mean? Show three expressions that will
* overflow.
*/

/*
* answer: 指变量大小超过了变量类型允许的表示范围
*/


int main(void){

    //exercise 4.4
    int outcome = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2; 
    // order: 12/3=4 -> 4*4=16 -> 5*15=75 -> 24%4=0 -> 16+75=91 -> 91+0=91
    cout << outcome << endl;

    //exercise 4.5
    cout << -30 * 3 + 21 / 5 << endl; // -86
    cout << -30 + 3 * 21 / 5 << endl; // -18
    cout << 30 / 3 * 21 % 5 << endl; // 0
    cout << -30 / 3 * 21 % 4 << endl; // -2

    //exercise 4.6 
    int var = 4; 
    if ( var % 2 == 0 ){

        cout << "the variable " << var << " is even ...." << endl; 

    }else { cout << "the variable " << var << " is odd ...." << endl; }

    //exercise 4.7
    // 例 1: 有符号 int 溢出
    int x = INT_MAX;   // 假设 32 位，INT_MAX = 2147483647
    int y = x + 1;     // 溢出 → UB（常见表现为变成负数）

    // 例 2: 有符号 short 溢出
    short s = 32767;   // 假设 short 为 16 位
    s = s + 1;         // 溢出 → UB（常见表现为 -32768）

    // 例 3: 无符号 unsigned int 溢出
    unsigned int u = UINT_MAX; // 假设 32 位，最大值 4294967295
    u = u + 1;                 // wrap around → 0

    cout << y << endl;
    cout << s << endl; 
    cout << u << endl;
    
}