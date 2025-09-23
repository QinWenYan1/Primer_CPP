#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

/*
* Exercise 6.11: 
* Write and test your own version of reset that takes a reference.
*
* Exercise 6.12: 
* Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) 
* to use references instead of pointers to swap the value of two ints. Which
* version do you think would be easier to use and why?
* 
* Answer: 
* 引用vs指针版本的对比分析：
* 引用版本更易用：语法更简洁，无需取地址和解引用操作
* 引用更安全：不存在空引用问题，必须绑定到有效对象
* 引用更直观：操作看起来像是在操作原始变量
*/ 

// 重制实参至0
// return type: void
// parameter type: int&
void reset(int & num){

    cout << "Reseting input number: " << num
         << " ..." << endl; 

    num = 0 ; 

    cout << "Reset successful ..." << endl; 

}

// 用于交换实参对象的值，并且打印下来
// return type: void
// parameter type: int&, int&
void swap(int &first, int &second){

    cout << "The value of two objects are: "
         << first << " , " << second << endl; 
    cout <<"Swapping ..." << endl; 

    int temp = first; 
    first = second; 
    second = temp; 

    cout << "The value of two objects are: "
         << first << " , " << second << endl; 
}

int main(void){

    int v1 = 110, v2 = 1145, v3 = 14; 
    reset(v3);
    swap(v1, v2); 

    cout << "Print the outcome ..." << "\n"
         << "v3: " << v3 << "\n"
         << "v1: " << v1 << "\n"
         << "v2: " << v2 << "\n" << endl; 

}