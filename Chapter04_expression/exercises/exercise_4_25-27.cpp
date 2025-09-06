#include <iostream>
#include <bitset>

using std::cout;
using std::cin;
using std::endl; 
using std::bitset; 

/*
* Exercise 4.25:
* What is the value of ~'q' << 6 on a machine with 32-bit
* ints and 8 bit chars, that uses Latin-1 character set in which 'q' has the
* bit pattern 01110001?
* answer: ~ 'q' = 11111111 11111111 11111111 10001110
          ~ 'q' << 6 = 11111111 11111111 11100011 10000000
*/

/* 
* Exercise 4.26: 
* In our grading example in this section, what would happen if
* we used unsigned int as the type for quiz1?
* answer: 如果 unsigned int 的位数不足（例如在16位系统上），则代码 1U << 27 会产生未定义行为，因为移位位数超过了类型的位数
*/

/*
* Exercise 4.27: What is the result of each of these expressions?
* unsigned long ul1 = 3, ul2 = 7;
* (a) ul1 & ul2
* (b) ul1 | ul2
* (c) ul1 && ul2
* (d) ul1 || ul2
*/


int main(void){

    // exercise 25
    cout << "print the outcome of exercise 25 ..." << endl; 
    cout << bitset<8>('q') << endl; 
    cout << bitset<32>(~ 'q' << 6) << endl; 

    // exercise 27 
    unsigned long ul1 = 3, ul2 = 7;
    cout << "print outcome .... " << endl; 
    cout << (ul1 & ul2) << endl; //00000011 & 00000111 = 00000011 也就是3
    cout << (ul1 | ul2) << endl; //00000011 | 00000111 = 00000111 也就是7
    cout << (ul1 && ul2) << endl;// true 实际输出1
    cout << (ul1 || ul2) << endl;// true 实际输出1

}