#include <iostream>

/*
* Exercise 1.12:
* What does the following for loop do? What is the final value
* of sum?
*/

/*
* answer:
* 最终值为0
*/

/*
* Exercise 1.13:
* Rewrite the exercises from § 1.4.1 (p. 13) using for loops.
*/

/*
* Exercise 1.14:
* Compare and contrast the loops that used a for with those
* using a while. Are there advantages or disadvantages to using either form?
*/

/*
*Answer:
* for's adavantage：代码更紧凑、阅读方便，推荐用于计数循环。
* for's disadvantage: for 结构不如 while 灵活，某些复杂场景不适合。
* while's advantage：逻辑更灵活，适用于条件驱动型循环。
* while's disadvantage: while 更容易出错，尤其是在忘记更新循环变量时。
*/

int main(void){

    int sum = 0; // the sum

    for(int i = 0; i <= 10; i ++ ){

        sum += i; 

    }

    std::cout << " Sum of 1 to 10 inclusive is " << sum << std::endl; 

}
